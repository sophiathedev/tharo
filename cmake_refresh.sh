#!/bin/sh

sh -c '/usr/bin/cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=/usr/bin/make -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ -G "Unix Makefiles" -S /home/sophia/Desktop/tharo -B /home/sophia/Desktop/tharo/cmake-build-debug'
