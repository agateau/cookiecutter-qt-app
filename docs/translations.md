# Translation handling

Translations are handled by Qt [internationalization system][qti18n]. The .ts files are kept in the `src/translations` directory.

[qti18n]: https://doc.qt.io/qt-5/internationalization.html

## Adding a new language

To add a new language:

1. Go to the `src/translations` directory and run `lupdate -ts <your_app_name>_<language>.ts`. Where `language` is the [BCP47 language tag][bcp47] for the language to support.

2. Add the new .ts file to the `TS_FILES` variable in `src/CMakeLists.txt`.

3. Run `make lupdate`. This will fill the new .ts file with the messages to translate.

[bcp47]: https://en.wikipedia.org/wiki/IETF_language_tag

## Updating translations

To update translations:

1. Run `make lupdate` to add the new messages to all the .ts files.

2. Translate, or ask translators to translate, the .ts files using [Qt Linguist][qtlinguist].

[qtlinguist]: https://doc.qt.io/qt-5/qtlinguist-index.html

3. Run `make` to turn the .ts files into .qm files.

4. Run `make install` to install the .qm files so that your application can find them.

## Translations loading

Translations are installed in the `translations` sub-directory of the data directory.

They are loaded at startup by the `loadTranslations()` function in `main.cpp`.

## CMake implementation details

Qt provides two CMake functions to handle .ts files:

- `qt5_add_translation`: Define custom commands to turn .ts files into .qm files.
- `qt5_create_translation`: Define custom commands to update .ts files from the source files.

This cookiecutter uses `qt5_add_translation` but does not use `qt5_create_translation`. Instead, as explained in the "Updating translations" section, there is an `lupdate` build target to update .ts files from the source files. This target is defined in `cmake/translations.cmake`.

The reason for not using `qt5_create_translation` is that when you use it, `lupdate` is automatically run every time the source files are more recent than the .ts files. This might sound like a good idea, but it turns out to be annoying because commits get polluted by .ts file updates. With an explicit, manual `lupdate` target, you can control when you update .ts files. Typically when you are about to release a new version, you would run `make lupdate`, commit the updated .ts files and notify translators they can now update their translations.

## Why is there an English translation?

There are two reasons for having an English translation.

The first one is that it is required for plural handling. When a translated string must handle plural, the call to `tr()` looks like this: `tr("%n message(s) saved", "", n)` (see [Qt documentation on this topic](qt-plural-handling)). In this case the user interface should not use the source string ("%n message(s) saved"), but rather a real translation, provided by the "en" translation file.

The second reason is for the corner case of an OS with multiple preferred languages, where English is not the last one:

Let's assume your application is started on an OS configured to load English first, then French.
At startup, Qt iterates on the preferred languages and loads the first translation file it finds.
If your application ships a French translation file but no English translation file, then Qt is going to skip the English language, and load the French translation instead, even if the user prefers English over French.

[qt-plural-handling]: https://doc.qt.io/qt-5/i18n-source-translation.html#handling-plurals
