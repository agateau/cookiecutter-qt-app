# Dependencies

The generated app *requires* the following dependencies to build:

- Qt, the latest LTS version (as long as it remains available)
- [Extra CMake Modules][ecm], to help with some of the packaging tasks
- [Catch2][catch2], to write unit-tests

And can use the following optional dependencies:

- [ds_store][], macOS only: Python module to customize the layout of the Finder window for the generated DMG archive.

## QWidget usage

The app uses QWidget, so it does not include Qt Quick Controls 2. The reasons behind this are the following:

- At the time I am writing this, Qt Quick Controls 2 is still not (in my opinion) a good enough replacement for QWidgets.
- If you want to build a Qt Quick Controls 2 app, the provided template should still be largely usable. It would need some adjustments, but you would probably need QWidgets support anyway, if you need to show any standard dialogs, like the file dialogs.

[ecm]: https://api.kde.org/ecm/
[catch2]: https://github.com/catchorg/Catch2/
[ds_store]: https://pypi.org/project/ds_store/
