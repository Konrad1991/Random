#!/bin/bash

gcc MersenneTwister.c -o mersenne_twister
./mersenne_twister
echo "\n"
../bin/Rscript test.R
