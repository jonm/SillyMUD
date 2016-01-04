#!/bin/sh

VERSION=`git describe --match 'v*' | sed -e 's/^v//'`

set -e

make dist
tar zxvf sillymud-$VERSION.tar.gz
(cd sillymud-$VERSION; CFLAGS="-std=gnu99" ./configure && make)


