# Changelog

## 0.2.0 - 2020-05-22

### Added

- Generate basic macOS dmg
- Generate basic Windows installer
- Added documentation for CI setup and dependencies

### Fixed

- Define a nicer "human name" by default
- Make sure main window uses "human name"
- Renamed ci/build to ci/build-app and detect_python to init_python_cmd
- Split install-dependencies into one file per OS

### Internals

- Added a way to run ci/build-app faster by skipping dependency installations

## 0.1.0 - 2020-05-12

First "release"
