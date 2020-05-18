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

## Continuous Integration support

The created app comes with a `ci` directory containing scripts to help you setup continuous integration. You can learn more about it in [doc/ci.md][].

## CI for the cookiecutter itself

This cookiecutter has a CI setup itself. It works by first running `cookiecutter` to produce the app, then running the scripts from the produced app to build it. This way the app CI scripts are tested in a setup closer to the real use case.

## Installers support

Right now the template supports:

- Linux .deb packages
- Linux .rpm packages
- Windows installers

But the goal is to add:

- macOS dmg
- Linux AppImage
- Linux Snaps
- Linux FlatPak
