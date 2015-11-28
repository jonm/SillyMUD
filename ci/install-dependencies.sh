#!/usr/bin/env sh

git clone https://github.com/Snaipe/Criterion.git && \
cd Criterion && \
git fetch origin master:master && \
git checkout master && \
mkdir build && \
cd build && \
cmake .. && \
cmake --build . && \
sudo make install

