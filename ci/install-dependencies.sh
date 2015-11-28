#!/usr/bin/env sh

export CC=gcc
git clone https://github.com/Snaipe/Criterion.git && \
cd Criterion && \
git fetch origin master:master && \
git checkout master && \
cp LICENSE debian.copyright && \
mkdir build && \
cd build && \
cmake .. && \
cmake --build . && \
ls -F


