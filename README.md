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
- Organizing third-party code using submodules

[Catch2]: https://github.com/catchorg/Catch2

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
