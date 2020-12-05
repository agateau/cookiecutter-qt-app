# cookiecutter-qt-app

![main](https://github.com/agateau/cookiecutter-qt-app/workflows/main/badge.svg)

## What is this?

[Cookiecutter][cookiecutter] is a command-line tool to create projects from project templates. This repository contains a template to build a Qt application.

[cookiecutter]: https://github.com/audreyr/cookiecutter

The application created with this template is not a simple "Hello World", the goal is to produce a useful base for a "real world" application.

By "real world" I mean the application comes with:

- Translation support
- Installing data files, and code to find them on the disk
- Desktop shortcuts
- Unit-testing, using [Catch2][]
- Packages/installers for Linux, macOS and Windows (WIP, see below)
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

Create your app by running:

```
cookiecutter https://github.com/agateau/cookiecutter-qt-app
```

and answering the questions.

Your app skeleton is now ready, time to build it:

```
cd your_app_name
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/where/to/install ..
make
make install
```

Look in `/where/to/install`. Your app should be there, ready to be started. Give it a try!

Your app source code comes with some unit-tests. You can run them with:

```
make check
```

You are all set, time to turn this skeleton into a real app!

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

- Dependencies: [docs/dependencies.md](docs/dependencies.md)
- CI: [docs/ci.md](docs/ci.md)
- Unit-tests: [docs/tests.md](docs/tests.md)
- Icons: [docs/icons.md](docs/icons.md)
- Translations: [docs/translations.md](docs/translations.md)
