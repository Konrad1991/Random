#!/bin/bash

gcc MersenneTwister.c -o mersenne_twister
./mersenne_twister
../bin/Rscript test.R
