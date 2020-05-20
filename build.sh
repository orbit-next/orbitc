#!/bin/bash

# WARNING: this file is known to be a mess and just barely works
CC='gcc'
rm -rf build
mkdir build
if [ -n "$flags" ]; then echo "Building with flags" $flags; fi
echo 'Building runtime library...'
(cd lib && find -type f -name '*.c') | sed 's/^\.\/\(.*\)\.c$/\1/' | xargs -I {} $CC lib/{}.c -lm -std=c99 -D_POSIX_SOURCE $flags -Wall -Werror -pedantic -Og -g -c -o build/{}.o
if [ $? -ne 0 ]; then
    echo 'Runtime library build failed'
    exit
fi
find build -type f -name '*.o' | xargs ar rcs build/libqb.a 
echo 'Building executables...'
(cd src && find -maxdepth 1 -type f -name '*.c') | sed 's/^\.\/\(.*\)\.c$/\1/' | xargs -I {} $CC src/{}.c -lm -Lbuild -lqb -std=c99 -D_POSIX_SOURCE $flags -Wall -Werror -pedantic -Og -g -o {}
if [ $? -ne 0 ]; then
    echo 'Executable build failed'
    exit
fi
echo 'Completed'
