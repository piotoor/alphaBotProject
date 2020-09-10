#!/bin/sh

cppzmqMasterLocation="/cygdrive/c/cppzmq-master"

if [ "$1" != "" ]; then
    cppzmqMasterLocation=$1
fi

g++ -c ./alphaBotCommunicator.cpp -I $cppzmqMasterLocation  -lzmq  --std=c++17
ar rvs alphaBotCommunicator.a alphaBotCommunicator.o
g++  ./alphaBotCommunicator_test.cpp alphaBotCommunicator.a -I $cppzmqMasterLocation  -lzmq  --std=c++17