# Contributing to VerySillyMUD

While VerySillyMUD is a hobby project, it is still important to keep all the
i's dotted and t's crossed. Pull requests (PRs) are definitely welcome, but
before we can merge them, we need contributors to sign the
[Contributor License
Agreement](https://www.clahub.com/agreements/jonm/SillyMUD) (CLA). This
agreement is nearly identical to the CLA the [Apache Software
Foundation](https://www.apache.org/) uses, and primarily ensures that
we can incorporate your contributions into the project and continue
distributing it--which, after all, we assume was the intent in your
making a pull request anyway! The agreement can be signed online after
you authenticate with your GitHub account.

The rest of this file describes general expectations for
contributions, offered in a spirit of saving everyone a bunch of hassle.

## Documentation

There is some documentation collected in the `doc/` directory,
although it is of unknown accuracy at this point. Please update any
appropriate documentation as part of your PR. Feel free to convert
documentation to Markdown.

## Testing and Refactoring

There is a basic unit testing framework in place using the
[Criterion](https://github.com/Snaipe/Criterion/) library. Please take
advantage of it in order to refactor _safely_ and to document any
behavioral changes you have made. Please ensure all tests pass on your
PR, even when compiling with `-Wall -Wextra -Werror`. Continuous
integration is provided by [Travis
CI](https://travis-ci.org/jonm/SillyMUD).

## Code Standards

The code is of varying quality, having been assembled by a number of
authors over the years, so please help us clean it up gradually. The
basics are:
* on supported platforms, MUST NOT generate compiler warnings; you
can check this when you build via
`CFLAGS="-Wall -Wextra -Werror" ./configure"`.
* SHOULD use two spaces for indents, no tabs
* open braces SHOULD be at the end of the prior line, not on a line by
themselves

Existing code has been formatted with:

`gindent -bap -bli0 -l79 -ncs -npcs -lc79 -br -brf -brs -nut -i2
-nce -npsl`

Consider using this to keep your additions stylistically agreeable.


## Pull Requests

As inspired by the [contribution
guidelines](https://github.com/Comcast/sirius/blob/master/CONTRIBUTING.md)
from the [Sirius](https://github.com/Comcast/sirius) project, PRs
should:
* be from a forked project with a relevant branch name
* be narrowly focused with no more than 3 or 4 logical commits
* when possible, address only one issue
* refer to any related issues by issue number

## Commit messages

The
[PhoneGap](https://github.com/phonegap/phonegap/wiki/Git-Commit-Message-Format)
project has a good set of guidelines we also use:

* First line should be maximum 50 characters long
* It should summarise the change and use imperative present tense
* The rest of the commit message should come after a blank line
* We encourage you to use Markdown syntax in the rest of the commit
message
* Preferably keep to an 72 character limit on lines in the rest of the
message.

If a commit is related to a particular issue, put the issue number
after a hash (#) somewhere in the detail. You can put the issue number
in the first line summary, but only if you can also fit in a useful
summary of what was changed in the commit.

Here's an example commit message:

```
No more autorent charges

Although by default the codebase compiles with `-DNEW_RENT`, which
sets the normal rent price to 0 gold/day, as indicated by `offer`,
players were getting charged more than zero coins when they rejoined
the game. This addresses issue #17.
```



