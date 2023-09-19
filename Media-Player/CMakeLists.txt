cmake_minimum_required(VERSION 3.20)
project(MediaPlayer)

set(CMAKE_CXX_STANDARD 20)

add_executable(MediaPlayer main.cpp MediaPlayer.h PlayerFactory.h)
