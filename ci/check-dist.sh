#!/bin/sh

VERSION=`git describe`

set -e

make dist
tar zxvf sillymud-$VERSION.tar.gz
(cd sillymud-$VERSION; CFLAGS="-std=gnu99" ./configure && make)


