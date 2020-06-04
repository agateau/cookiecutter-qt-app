# cookiecutter-qt-app

## What is this?

This is a [cookiecutter][] to build Qt applications, based on my own preferences.

[cookiecutter]: https://github.com/audreyr/cookiecutter

The goal of this cookiecutter is to make it easier to create real-world, stand-alone applications, installable on Linux, macOS and Windows.

Real-world appications means that out of the box you get:

- Support for translations
- Creation of packages/installers for all platforms (WIP, see below)
- Desktop shortcuts
- Unit-testing, using [Catch2][]
- Code formatting, using clang-format (TODO)

[Catch2]: https://github.com/catchorg/Catch2

### Packaging support

Right now the cookiecutter supports:

- Linux .deb packages
- Linux .rpm packages
- Windows installers
- macOS dmg

But the goal is to add:

- Linux AppImage
- Linux Snaps
- Linux FlatPak

## Getting started

Install cookiecutter:

```
pip install cookiecutter
```

Create your app:

```
cookiecutter https://github.com/agateau/cookiecutter-qt-app
```

Your app skeleton is ready, time to build it:

```
cd your_app_name
mkdir build
cd build
cmake ..
make
```

Run the tests:

```
make check
```

You are all set, time to turn this skeleton into a real app.

## Creating packages

To generate a package (or an installer, depending on your OS), build the `package` target:

```
make package
```

This will generate a package or installer for your app.

You can also generate a source archive using the `package_source` target.

## Continuous Integration support

The created app comes with a `ci` directory containing scripts to help you setup continuous integration. You can learn more about it in [docs/ci.md](docs/ci.md).

### CI for the cookiecutter itself

This cookiecutter has a CI setup itself. It works by first running `cookiecutter` to produce the app, then running the scripts from the produced app to build it. This way the app CI scripts are tested in a setup closer to the real use case.

## Documentation

- Dependencies: [docs/dependencies.md](docs/dependencies.md).
- CI: [docs/ci.md](docs/ci.md).

