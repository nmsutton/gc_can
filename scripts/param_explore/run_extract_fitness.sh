#!/bin/bash
# run the extract_fitness program

export make_clean="rm extract_fitness"
export make="g++ -Wall -g -std=c++11 extract_fitness.cpp -o extract_fitness"
export run=" && ./extract_fitness"

command=$make_clean
eval $command
command=$make$run
eval $command