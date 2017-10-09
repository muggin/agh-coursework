%%%-------------------------------------------------------------------
%%% @author Wojciech Kryściński
%%% @copyright (C) 2015, PWiR, Informatyka, AGH
%%% @doc
%%%
%%% @end
%%% Created : 15. Jan 2015 22:05
%%%-------------------------------------------------------------------
-module(uploaderl).
-author("Wojciech Kryściński").

-behaviour(application).

%% Application callbacks
-export([start/2,
  stop/1]).

%%%===================================================================
%%% Application callbacks
%%%===================================================================

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Funkcja jest wywoływana przy każdym starcie aplikacji przy użyciu
%% application:start/[1,2] i powinna startować proces tej aplikacji.
%%
%% This function is called whenever an application is started using
%% application:start/[1,2], and should start the processes of the
%% application. If the application is structured according to the OTP
%% design principles as a supervision tree, this means starting the
%% top supervisor of the tree.
%%
%% @end
%%--------------------------------------------------------------------
-spec(start(StartType :: normal, StartArgs :: term()) ->
  {ok, pid()} | {error, Reason :: term()}).

start(normal, _StartArgs) ->
  case uploaderl_sup:start_link() of
    {ok, Pid} ->
      {ok, Pid};
    Error ->
      Error
  end.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Funkcja jest wywoływana przy zatrzymywaniu aplikacji.
%% Powinna być przeciwieństwem Module:start/2 oraz jest
%% odpowiedzialna za sprzątanie po aplikacji.
%%
%% @end
%%--------------------------------------------------------------------
-spec(stop(State :: term()) -> term()).
stop(_State) ->
  ok.
