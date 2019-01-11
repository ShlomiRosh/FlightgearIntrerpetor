cmake_minimum_required(VERSION 3.9)
project(SemesterProject1Try2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(SemesterProject1Try2 main.cpp Expression.h Expressions.cpp Expressions.h ShuntingYardD.cpp ShuntingYardD.h Interpreter.cpp Interpreter.h Maps.cpp Maps.h Boolean.cpp Boolean.h Command.h Commands.cpp Commands.h VarCommand.cpp ConnectCommand.cpp OpenDateServerCommand.cpp ReadBufferServer.cpp)