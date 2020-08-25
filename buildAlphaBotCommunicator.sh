#!/bin/sh

g++ -c ./alphaBotCommunicator.cpp -I /cygdrive/c/cppzmq-master  -lzmq  --std=c++17
ar rvs alphaBotCommunicator.a alphaBotCommunicator.o
g++  ./alphaBotCommunicator_test.cpp alphaBotCommunicator.a -I /cygdrive/c/cppzmq-master  -lzmq  --std=c++17