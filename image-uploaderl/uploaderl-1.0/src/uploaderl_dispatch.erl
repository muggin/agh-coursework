%%%-------------------------------------------------------------------
%%% @author Wojciech Kryściński
%%% @copyright (C) 2015, PWiR, Informatyka, AGH
%%% @doc
%%%
%%% @end
%%% Created : 15. Jan 2015 21:59
%%%-------------------------------------------------------------------
-module(uploaderl_dispatch).
-author("Wojciech Kryściński").

-behaviour(gen_fsm).

%% API
-export([start_link/0,
        complete/3,
        dispatching/2,
        listening/2]).

%% gen_fsm callbacks
-export([init/1,
  handle_event/3,
  handle_sync_event/4,
  handle_info/3,
  terminate/3,
  code_change/4]).

-define(SERVER, ?MODULE).
-define(POOL, uploaderl).

-record(data, {links=[], refs=[]}).

%%%===================================================================
%%% API
%%%===================================================================
complete(Pid, Ref, Response) ->
  gen_fsm:send_all_state_event(Pid, {complete, Ref, Response}).

%%--------------------------------------------------------------------
%% @doc
%% Creates a gen_fsm process which calls Module:init/1 to
%% initialize. To ensure a synchronized start-up procedure, this
%% function does not return until Module:init/1 has returned.
%%
%% @end
%%--------------------------------------------------------------------
-spec(start_link() -> {ok, pid()} | ignore | {error, Reason :: term()}).
start_link() ->
  gen_fsm:start_link(?MODULE, [], []).

%%%===================================================================
%%% gen_fsm callbacks
%%%===================================================================

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Whenever a gen_fsm is started using gen_fsm:start/[3,4] or
%% gen_fsm:start_link/[3,4], this function is called by the new
%% process to initialize.
%%
%% @end
%%--------------------------------------------------------------------
%-spec(init(Args :: term()) ->
%%   {ok, StateName :: atom(), StateData :: #state{}} |
%%   {ok, StateName :: atom(), StateData :: #state{}, timeout() | hibernate} |
%%   {stop, Reason :: term()} | ignore).
init([]) ->
  {ok, Dir} = application:get_env(directory),
  {ok, MaxSimUploads} = application:get_env(max_sim_uploads),
  {ok, APIKey} = application:get_env(api_key),
  {ok, APIEndpoint} = application:get_env(api_endpoint),
  ppool:start_pool(?POOL, MaxSimUploads, {uploaderl_worker, start_link, [APIKey, APIEndpoint]}),
  self() ! {start, Dir},
  {ok, dispatching, #data{links=[], refs=[]}}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% There should be one instance of this function for each possible
%% state name. Whenever a gen_fsm receives an event sent using
%% gen_fsm:send_event/2, the instance of this function with the same
%% name as the current state name StateName is called to handle
%% the event. It is also called if a timeout occurs.
%%
%% @end
%%--------------------------------------------------------------------
%% -spec(dispatching(Event :: term(), State :: #state{}) ->
%%   {next_state, NextStateName :: atom(), NextState :: #state{}} |
%%   {next_state, NextStateName :: atom(), NextState :: #state{},
%%     timeout() | hibernate} |
%%   {stop, Reason :: term(), NewState :: #state{}}).
dispatching({continue, File, Continuation}, Data=#data{refs=Refs}) ->
  NewRef = make_ref(),
  ppool:async_queue(?POOL, [self(), NewRef, File]),
  gen_fsm:send_event(self(), Continuation()),
  {next_state, dispatching, Data#data{refs=[NewRef|Refs]}};

dispatching(done, Data) ->
  listening(done, Data).

listening(done, #data{links=Links, refs=[]}) ->
  [io:format("~p -> ~p~n", [File, Response]) || {File, Response} <- Links],
  {stop, normal, done};

listening(done, Data) ->
  {next_state, listening, Data}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Whenever a gen_fsm receives an event sent using
%% gen_fsm:send_all_state_event/2, this function is called to handle
%% the event.
%%
%% @end
%%--------------------------------------------------------------------
%% -spec(handle_event(Event :: term(), StateName :: atom(),
%%     StateData :: #state{}) ->
%%   {next_state, NextStateName :: atom(), NewStateData :: #state{}} |
%%   {next_state, NextStateName :: atom(), NewStateData :: #state{},
%%     timeout() | hibernate} |
%%   {stop, Reason :: term(), NewStateData :: #state{}}).
handle_event({complete, Ref, Response}, State, Data=#data{links=Links, refs=Refs}) ->
  NewData=Data#data{links=[Response|Links], refs=Refs--[Ref]},
  case State of
    dispatching ->
      {next_state, dispatching, NewData};
    listening ->
      listening(done, NewData)
  end.



%%--------------------------------------------------------------------
%% @private
%% @doc
%% Whenever a gen_fsm receives an event sent using
%% gen_fsm:sync_send_all_state_event/[2,3], this function is called
%% to handle the event.
%%
%% @end
%%--------------------------------------------------------------------
%% -spec(handle_sync_event(Event :: term(), From :: {pid(), Tag :: term()},
%%     StateName :: atom(), StateData :: term()) ->
%%   {reply, Reply :: term(), NextStateName :: atom(), NewStateData :: term()} |
%%   {reply, Reply :: term(), NextStateName :: atom(), NewStateData :: term(),
%%     timeout() | hibernate} |
%%   {next_state, NextStateName :: atom(), NewStateData :: term()} |
%%   {next_state, NextStateName :: atom(), NewStateData :: term(),
%%     timeout() | hibernate} |
%%   {stop, Reason :: term(), Reply :: term(), NewStateData :: term()} |
%%   {stop, Reason :: term(), NewStateData :: term()}).
handle_sync_event(Event, _From, State, Data) ->
  io:format("Unexpected event: ~p~n", [Event]),
  {next_state, State, Data}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% This function is called by a gen_fsm when it receives any
%% message other than a synchronous or asynchronous event
%% (or a system message).
%%
%% @end
%%--------------------------------------------------------------------
%% -spec(handle_info(Info :: term(), StateName :: atom(),
%%     StateData :: term()) ->
%%   {next_state, NextStateName :: atom(), NewStateData :: term()} |
%%   {next_state, NextStateName :: atom(), NewStateData :: term(),
%%     timeout() | hibernate} |
%%   {stop, Reason :: normal | term(), NewStateData :: term()}).
handle_info({start, Dir}, State, Data) ->
  gen_fsm:send_event(self(), uploaderl_lib:find_images(Dir)),
  {next_state, State, Data}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% This function is called by a gen_fsm when it is about to
%% terminate. It should be the opposite of Module:init/1 and do any
%% necessary cleaning up. When it returns, the gen_fsm terminates with
%% Reason. The return value is ignored.
%%
%% @end
%%--------------------------------------------------------------------
-spec(terminate(Reason :: normal | shutdown | {shutdown, term()}
| term(), StateName :: atom(), StateData :: term()) -> term()).
terminate(_Reason, _StateName, _State) ->
  init:stop().

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Convert process state when code is changed
%%
%% @end
%%--------------------------------------------------------------------
%% -spec(code_change(OldVsn :: term() | {down, term()}, StateName :: atom(),
%%     StateData :: #state{}, Extra :: term()) ->
%%   {ok, NextStateName :: atom(), NewStateData :: #state{}}).
code_change(_OldVsn, StateName, State, _Extra) ->
  {ok, StateName, State}.

%%%===================================================================
%%% Internal functions
%%%===================================================================
