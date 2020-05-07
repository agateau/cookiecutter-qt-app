# cookiecutter-qt-app

This is a [cookiecutter][] to build Qt applications, based on my own preferences.

[cookiecutter]: https://github.com/audreyr/cookiecutter

The goal of this cutter is to make it easy to create real-world stand-alone applications, installable on Linux, macOS and Windows.

By real-world I mean that out of the box you get:

- Support for translations
- Installers for all platforms (WIP, see below)
- Desktop shortcuts

As a developer you also get:

- Unit-testing, using [Catch2][]
- Code formatting, using clang-format

[Catch2]: https://github.com/catchorg/Catch2

## CI support

The created app comes with a `ci` directory which contains two scripts:

### `ci/install-dependencies <deps_dir>`

Installs the required build dependencies in `<deps_dir>` and create a file called `<deps_dir>/env.sh`, which can be sourced to setup a working build environment.

### `ci/build`

Builds the app and all the relevant targets (tests, packaging...). It assumes the environment has been correctly setup, by sourcing the `<deps_dir>/env.sh` first

### No predefined configuration for existing CI products

There is no out-of-the-box integration for specific CI products like Travis, AppVeyor or GitHub actions, because I believe it is up to you to set up the CI system you want to use. Doing so should be simple since you only need to call the two CI scripts.

### CI for the cookiecutter itself

This cookiecutter has a CI setup itself. It works by first running `cookiecutter` to produce the app, then running the scripts from the produced app to build it. This way the app CI scripts are tested in a setup closer to the real use case.

## Installers support

Right now the template supports:

- Linux .deb packages
- Linux .rpm packages

But the goal is to add:

- Linux AppImage
- Linux Snaps
- Linux FlatPak
- Windows installers
- macOS dmg
