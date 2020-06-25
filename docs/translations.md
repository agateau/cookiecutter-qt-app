# Translation handling

## Why is there an English translation?

There are two reasons for having an English translation.

The first one is that it is required for plural handling. When a translated string must handle plural, the call to `tr()` looks like this: `tr("%n message(s) saved", "", n)` (see [Qt documentation on this topic](qt-plural-handling)). In this case the user interface should not use the source string ("%n message(s) saved"), but rather a real translation, provided by the "en" translation file.

The second reason is for the corner case of an OS with multiple prefered languages, where English is not the last one. Let's assume your OS is configured to load English first, then French. Let's also assume your application ships a French translation but no English translations. Qt iterates on the prefered languages and loads the first translation file it finds. Without an "en.ts" file, it skips the English language, and load the French translation instead.

[qt-plural-handling]: https://doc.qt.io/qt-5/i18n-source-translation.html#handling-plurals
