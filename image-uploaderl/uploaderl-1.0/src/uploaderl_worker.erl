%%%-------------------------------------------------------------------
%%% @author Wojciech Kryściński
%%% @copyright (C) 2015, PWiR, Informatyka, AGH
%%% @doc
%%%
%%% @end
%%% Created : 15. Jan 2015 20:21
%%%-------------------------------------------------------------------
-module(uploaderl_worker).
-author("Wojciech Kryściński").

-behaviour(gen_server).

%% API
-export([start_link/5]).

%% gen_server callbacks
-export([init/1,
  handle_call/3,
  handle_cast/2,
  handle_info/2,
  terminate/2,
  code_change/3]).

-export([upload_image/1]).

-define(SERVER, ?MODULE).

-record(state, {apikey, endpoint, dispatcher, ref, file}).

%%%===================================================================
%%% API
%%%===================================================================
-spec(upload_image(ImagePath :: string()) ->
{Response :: term() | error, Reason :: term()}).
upload_image(ImagePath) ->
  gen_server:call(uploader_worker, {upload_image, ImagePath}).

%%--------------------------------------------------------------------
%% @doc
%% Starts the server
%%
%% @end
%%--------------------------------------------------------------------
%% -spec(start_link() ->
%%   {ok, Pid :: pid()} | ignore | {error, Reason :: term()}).
start_link(APIKey, APIEndpoint, DispatcherPid, Ref, FileName) ->
  gen_server:start_link(?MODULE, [APIKey, APIEndpoint, DispatcherPid, Ref, FileName], []).

%%%===================================================================
%%% gen_server callbacks
%%%===================================================================

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Initializes the server
%%
%% @spec init(Args) -> {ok, State} |
%%                     {ok, State, Timeout} |
%%                     ignore |
%%                     {stop, Reason}
%% @end
%% %%--------------------------------------------------------------------
%% -spec(init(Args :: term()) ->
%%   {ok, State :: #state{}} | {ok, State :: #state{}, timeout() | hibernate} |
%%   {stop, Reason :: term()} | ignore).
init([APIKey, APIEndpoint, DispatcherPid, Ref, FileName]) ->
  self() ! start,
  {ok, #state{apikey=APIKey, endpoint=APIEndpoint, dispatcher=DispatcherPid, ref=Ref, file=FileName}}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Handling call messages
%%
%% @end
%%--------------------------------------------------------------------
%% -spec(handle_call(Request :: term(), From :: {pid(), Tag :: term()},
%%     State :: #state{}) ->
%%   {reply, Reply :: term(), NewState :: #state{}} |
%%   {reply, Reply :: term(), NewState :: #state{}, timeout() | hibernate} |
%%   {noreply, NewState :: #state{}} |
%%   {noreply, NewState :: #state{}, timeout() | hibernate} |
%%   {stop, Reason :: term(), Reply :: term(), NewState :: #state{}} |
%%   {stop, Reason :: term(), NewState :: #state{}}).

handle_call({upload_image, _ImagePath},  _From, State) ->
  {noreply, State}.


%%--------------------------------------------------------------------
%% @private
%% @doc
%% Handling cast messages
%%
%% @end
%%--------------------------------------------------------------------
%% -spec(handle_cast(Request :: term(), State :: #state{}) ->
%%   {noreply, NewState :: #state{}} |
%%   {noreply, NewState :: #state{}, timeout() | hibernate} |
%%   {stop, Reason :: term(), NewState :: #state{}}).
handle_cast(_Request, State) ->
  {noreply, State}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Handling all non call/cast messages
%%
%% @spec handle_info(Info, State) -> {noreply, State} |
%%                                   {noreply, State, Timeout} |
%%                                   {stop, Reason, State}
%% @end
%%--------------------------------------------------------------------
-spec(handle_info(Info :: timeout() | term(), State :: #state{}) ->
  {noreply, NewState :: #state{}} |
  {noreply, NewState :: #state{}, timeout() | hibernate} |
  {stop, Reason :: term(), NewState :: #state{}}).
handle_info(start, S=#state{}) ->
  Method = post,
  Url = S#state.endpoint, % "https://api.imgur.com/3/upload"
  Headers = [{"Authorization", "Client-ID " ++ S#state.apikey}], % ca1c42ef1d2fb95
  ContentType = "image/jpg",
  {ok, Binary} = file:read_file(S#state.file),
  Body = base64:encode(Binary),
  HttpOptions = [{ssl, [{verify, 0}]}],
  {ok, {_A, _B, C}} = httpc:request(Method, {Url, Headers, ContentType, Body}, HttpOptions, []),
  uploaderl_dispatch:complete(S#state.dispatcher, S#state.ref, {S#state.file, C}),
  {stop, normal, S}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% This function is called by a gen_server when it is about to
%% terminate. It should be the opposite of Module:init/1 and do any
%% necessary cleaning up. When it returns, the gen_server terminates
%% with Reason. The return value is ignored.
%%
%% @spec terminate(Reason, State) -> void()
%% @end
%%--------------------------------------------------------------------
-spec(terminate(Reason :: (normal | shutdown | {shutdown, term()} | term()),
    State :: #state{}) -> term()).
terminate(_Reason, _State) ->
  ok.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Convert process state when code is changed
%%
%% @spec code_change(OldVsn, State, Extra) -> {ok, NewState}
%% @end
%%--------------------------------------------------------------------
-spec(code_change(OldVsn :: term() | {down, term()}, State :: #state{},
    Extra :: term()) ->
  {ok, NewState :: #state{}} | {error, Reason :: term()}).
code_change(_OldVsn, State, _Extra) ->
  {ok, State}.

%%%===================================================================
%%% Internal functions
%%%===================================================================
