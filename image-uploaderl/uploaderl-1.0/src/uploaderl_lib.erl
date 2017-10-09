%%%-------------------------------------------------------------------
%%% @author Wojciech Kryściński
%%% @copyright (C) 2015, PWiR, Informatyka, AGH
%%% @doc
%%%
%%% @end
%%% Created : 15. Jan 2015 22:23
%%%-------------------------------------------------------------------
-module(uploaderl_lib).
-author("Wojciech Kryściński").

-include_lib("kernel/include/file.hrl").

%% API
-export([find_images/1]).

find_images(Directory) ->
  find_images(Directory, queue:new()).

%% Private functions
find_images(Name, Queue) ->
  {ok, F = #file_info{}} = file:read_file_info(Name),
  case F#file_info.type of
    directory -> handle_directory(Name, Queue);
    regular -> handle_regular_file(Name, Queue);
    _Other -> dequeue_and_run(Queue)
  end.

%% Opens directories and enqueues files in there
handle_directory(Dir, Queue) ->
  case file:list_dir(Dir) of
    {ok, []} ->
      dequeue_and_run(Queue);
    {ok, Files} ->
      dequeue_and_run(enqueue_many(Dir, Files, Queue))
  end.

%% Checks if the file finishes in .jpg
handle_regular_file(Name, Queue) ->
  case filename:extension(Name) of
    ".jpg" ->
      {continue, Name, fun() -> dequeue_and_run(Queue) end};
    _NonErl ->
      dequeue_and_run(Queue)
  end.

%% Pops an item from the queue and runs it.
dequeue_and_run(Queue) ->
  case queue:out(Queue) of
    {empty, _} -> done;
    {{value, File}, NewQueue} -> find_images(File, NewQueue)
  end.

%% Adds a bunch of items to the queue.
enqueue_many(Path, Files, Queue) ->
  F = fun(File, Q) -> queue:in(filename:join(Path,File), Q) end,
  lists:foldl(F, Queue, Files).