#!/bin/bash
#./premake4_linux64 --no-bullet3 --no-demos --no-extras gmake
rm -r gmake
./premake4_linux64 --no-bullet3 --no-demos --no-extras --no-test --file=premake4_no_suffix.lua gmake
cd gmake
CFLAGS=-fPIC CXXFLAGS=-fPIC make -j 2 config=release64