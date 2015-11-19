# VerySillyMUD
A refactoring exercise based on SillyMUD, a derivative of DikuMUD.

# Prerequisites

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


