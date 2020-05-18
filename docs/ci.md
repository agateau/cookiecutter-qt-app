# Continuous Integration

## TL;DR

To install dependencies and build your app run:

```shell
ci/install-dependencies deps
. deps/env.sh
ci/build-app
```

## Continuous Integration philosophy

When it comes to continuous integration I have a few strong opinions.

First: it's a good idea to keep your CI configuration independent from the particular CI product you use. This makes it easier to test your CI scripts on your local machine and makes it less painful to switch from one CI product to another or to use multiple CI products in parallel.

For this reason there is no out-of-the-box integration for specific CI products like Travis, AppVeyor or GitHub actions.

Second: components you depend on should not change behind your back. This way if the CI reports a breakage you know it's because of a change in your code, not because a library you depend on has been updated between the last build and the current one and is now causing a failure.

This means depending on specific versions of components has much as possible. Rolling-release systems are certainly interesting on an individual machine, but I want stability on my build servers. On Linux systems, this is easy to achieve using a stable distribution such as Debian stable, Ubuntu LTS, Red Hat or CentOS. On macOS or Windows, it is unfortunately more complicated: the base OS does not provide a package system, and the third-party package systems do not let you specify the versions of the components you want to install (at least as far as I know, I would love to be proven wrong on this!)

## Included scripts

The `ci` directory contains the following scripts:

### `ci/install-dependencies <deps_dir>`

Installs the required build dependencies in `<deps_dir>` and creates a file called `<deps_dir>/env.sh`, which can be sourced to setup a working build environment.

### `ci/build-app`

Builds the app and all the relevant targets (tests, packaging...). It assumes the environment has been correctly setup, by sourcing the `<deps_dir>/env.sh` first.

Note: the script is not called `build` to avoid hours of wasted time wondering why your script is ignored because you added `build` to your root `.gitignore` file (been there, done that :))

### Caching

If your CI product supports caching, it's a good idea to cache the state of your build machines after running `ci/install-dependencies` to speed-up builds.

## Build machine requirements

The build scripts assume the following are installed:

On all OS:

- Python 3.x

On macOS:

- clang
- git
- make

On Windows:

- MSVC 2017
- git
- NSIS 3.x
