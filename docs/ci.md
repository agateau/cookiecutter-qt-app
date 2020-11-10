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

Second: components you depend on should not change behind your back. This way if the CI reports a breakage you know it's because of a change in your code, not because a library you depend on has been updated between the previous build and the current one and is now causing a failure.

This means depending on specific versions of components has much as possible. Rolling-release systems are certainly interesting on an individual machine, but I want stability on my build servers. On Linux systems, this is easy to achieve using a stable distribution such as Debian stable, Ubuntu LTS, Red Hat or CentOS. On macOS or Windows, it is unfortunately more complicated: the base OS does not provide a package system, and the third-party package systems do not let you specify the versions of the components you want to install (at least as far as I know, I would love to be proven wrong on this!)

## Included scripts

The `ci` directory contains the following scripts:

### `ci/build-app`

This is the main script. It expose the different build steps as command-line arguments. To get the supported build steps run the script with `--help`. You should get an output like this:

```
Usage: build-app [OPTION ...] [steps...]

Provides all the steps to build the application. This script is called by the
CI to build the application, but you can run it on your local machine as well.

Options:
  -h, --help          display this usage message and exit

Steps:
  install-dependencies
  build
  tests
  install
  binary-packages
  source-package
```

If you want to execute the `install-dependencies` step, call `build-app install-dependencies`. You can have the script execute multiple steps in one call by adding all the steps to execute as arguments. Having separate build steps like this instead of one giant "build" step makes it possible to expose all the steps in your CI. This makes CI progress easier to track.

Note: the script is not called `build` to avoid hours of wasted time wondering why your script is ignored because you added `build` to your root `.gitignore` file (been there, done that :))

### `ci/lib/$OS-dependencies.sh`

For each supported OS, there is a `ci/lib/$OS-dependencies.sh` file, which must define an `install_dependencies()` shell function. The job of this function is to install all the required build dependencies. Dependencies must be installed in the `$INSTALL_DIR` directory.

Sometimes installing a dependency in the `$INSTALL_DIR` directory is not enough for the build system to make use of it. Some dependencies require adding a new directory to `$PATH` or defining a new environment variable. To handle this, there is the `$INSTALL_DIR/env.sh` file. This file is sourced by the `build` and `tests` steps. The `install_dependencies()` function can make use of the `prepend_path()` and `add_env_var()` functions defined in `ci/lib/common.sh` to add entries to `env.sh`.

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

- MSVC 2017. The reason for picking MSVC instead of MinGW is that Qt MSVC packages are much smaller than MinGW ones, making builds faster in situations where the CI must install Qt for each build.
- git
- NSIS 3.x
