import os

from pathlib import Path

PROJECT_DIRECTORY = Path(os.path.curdir)

SELECTED_LICENSE = "{{ cookiecutter.license }}"

# Must be kept in sync with the "license" field from cookiecutter.json
EXT_FOR_LICENSE = {
    "GPL v3": ".GPL",
    "MIT": ".MIT",
    "BSD 3-Clause": ".BSD",
    "Apache License 2.0": ".Apache-2.0",
}


def main():
    wanted_ext = EXT_FOR_LICENSE.get(SELECTED_LICENSE)
    for path in PROJECT_DIRECTORY.glob("LICENSE.*"):
        if path.suffix == wanted_ext:
            path.rename("LICENSE")
        else:
            path.unlink()


if __name__ == "__main__":
    main()
