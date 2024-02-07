@echo off

set LIB_PATH_ORGIN=D:/Yeni_Kilasor/Kurulmus_Dosyalar/Programlar/PATH/C++_Compiler
set LIB_1=%LIB_PATH_ORGIN%/i686-w64-mingw32/lib
set LIB_2=%LIB_PATH_ORGIN%/lib

set NAME=libcrc
set LIB_ARGS=
set INCLUDE=-I ./include
set DEF_FILE=--output-def,./def/%NAME%.def
set LIB_FILE=--out-implib,./lib/%NAME%.a

g++ -c ./src/*.cpp %INCLUDE%
g++ -shared -o ./bin/%NAME%.dll *.o -Wl,%DEF_FILE%,%LIB_FILE% %LIB_ARGS%

del *.o