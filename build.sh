#!/bin/bash
echo "Building with flags" $flags
gcc src/{orbitc.c,qblib.c,qblibio.c} -lm -std=c99 -D_POSIX_SOURCE $flags -Wall -Werror -pedantic -Og -g -o orbitc
