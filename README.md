# VerySillyMUD
A refactoring exercise based on SillyMUD, a derivative of DikuMUD.

[![Build Status](https://travis-ci.org/jonm/SillyMUD.svg?branch=master)](https://travis-ci.org/jonm/SillyMUD)

# Prerequisites

## Mac OS

You'll need to install the `criterion` C unit testing library:
https://github.com/Snaipe/Criterion/

```
$ brew install snaipe/soft/criterion
```

*NOTE*: At least one version of Criterion I installed forgot to install
one of the header files, `assert_base.h`. When I cloned the source, I was
able to just copy that file into the appropriate place.

You'll also need the GNU autotools:

```
$ brew install autoconf
$ brew install automake
```

## Windows (WSL)

Install `criterion` unit testing library:
```
$ wget https://github.com/Snaipe/Criterion/releases/download/v2.3.3/criterion-v2.3.3-linux-x86_64.tar.bz2
$ tar jxvf criterion-v2.3.3-linux-x86_64.tar.bz2
$ echo `pwd`/criterion-v2.3.3/lib > criterion.conf
$ sudo mv criterion.conf /etc/ld.so.conf.d
$ sudo ldconfig
```

Then install GNU autotools:
```
$ sudo apt-get install autoconf automake
```

You will then need to add `CFLAGS` and `LDFLAGS` telling `configure`
where to find the library, as in:
```
./configure CFLAGS="-I"`pwd`/criterion-v2.3.3/include \
  LDFLAGS=-L`pwd`/criterion-v2.3.3/lib
```

# Building

First you will have to initialize the build system via:
```
$ autoreconf --install
```

Then you can just:
```$ ./configure && make```

You can run the tests via:

```$ make check```

And then you can install the game via:

```$ make install```

Note that there are lots of options available for `configure`; try
either `configure --help` or see `INSTALL`. In particular, you may
want to consider adding `-Wall -Wextra -Werror` to `CFLAGS`, as this
is the way the CI build runs.

# Running the game

The major note is that the first player to log in will become an
"Implementor" level god; after the first log in, that player will need
to have an entry in the [`security`](lib/security/) directory. By default on most systems
this is `/usr/local/var/sillymud/security`. See the [`README`](lib/security/README) file in
that directory for more details.

Documentation for running the game are found in [`running.doc`](doc/running.doc).
