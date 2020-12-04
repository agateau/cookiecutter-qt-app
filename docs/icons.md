# Icons

## Application icon

The application icon, meaning the image used to represent the application in the OS and used as the icon for its main window, is stored in `src/appicon`. It is bundled into the application. You can access it from the code using the resource path `:/appicon/sc-apps-{APP_NAME}.svg`.

## Theme icons

For a better integration with Linux desktops, icons used to represent actions should be loaded using `QIcon::fromTheme(name)`. Unfortunately, Windows and macOS have no notion of icon themes, so you have to provide your own icons for them. To do so, copy the required icons to the `src/icons` directory and add them to `src/app.qrc`. The generated code in `main.cpp` takes care of ensuring `QIcon::fromTheme(name)` will load icons from this directory on Windows and macOS, without having to manually declare a fallback icon.
