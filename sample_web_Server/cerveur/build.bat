@echo off
set CC=gcc
set CFLAGS=-Iinclude
set SOURCES=src\HTTP_Server.c src\Response.c src\Routes.c src\main.c
set OUTPUT=server.exe

%CC% %CFLAGS% %SOURCES% -o %OUTPUT%
echo Build completed.
