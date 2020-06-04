# Tests

## Running tests

You can run the `tests` executable but it's simpler to use the `check` build target, to build and run the tests in one go.

## Code organization

The cookiecutter generates an app which is made of two parts:

- a static library containing most of the code
- an executable which links the static library with a `main.cpp` file

The unit-tests are generated as another executable which also links to the app static library.

The advantage of this approach is that the build system does not need to compile the tested code twice: once for the app and a second time for the tests.

## The example tests

The [example test file][example] is basic, but demonstrates how to use [Catch2][] and how to write tests exercising the user-interface.

[example]: ../{{cookiecutter.project_slug}}/tests/ExampleTest.cpp
[Catch2]: https://github.com/catchorg/Catch2

## Headless support

To run UI tests on headless Linux machines, a common setup in a CI environment, the [ci/build-app][build-app] script runs the tests with `xvfb-run` and a [small helper script][xvfb-helper-script] to start a window manager. If we don't start a window manager, new windows do not get focused when created, making some tests fail.


[xvfb-helper-script]: ../{{cookiecutter.project_slug}}/ci/headless-test-helper
[build-app]: ../{{cookiecutter.project_slug}}/ci/build-app