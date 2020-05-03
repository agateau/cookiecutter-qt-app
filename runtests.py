#!/usr/bin/env python3
"""
Test the cookiecutter
"""
import argparse
import os
import platform
import shlex
import sys

from tempfile import TemporaryDirectory
from subprocess import run, CalledProcessError

CUTTER_DIR = os.path.abspath(os.path.dirname(__file__))

CMAKE_CMD = ["cmake"]

CTEST_CMD = ["ctest", "--verbose"]

TARGETS = ["lupdate", "build", "test", "install"]


def get_test_cmd():
    cmd = CTEST_CMD
    if platform.system() == "Linux" and "DISPLAY" not in os.environ:
        cmd = ["xvfb-run"] + cmd
    return cmd


def check_run(cmd, **kwargs):
    kwargs = dict(kwargs)
    kwargs["check"] = True
    cmd_str = " ".join(shlex.quote(x) for x in cmd)
    print(f"# Running '{cmd_str}'")
    try:
        return run(cmd, **kwargs)
    except CalledProcessError:
        print(f"# Command '{cmd_str}' failed")
        sys.exit(1)


def main():
    target_names = ", ".join(TARGETS)

    parser = argparse.ArgumentParser()
    parser.description = __doc__

    parser.add_argument("-s", "--shell", action="store_true",
                        help="Run a shell at the end")

    parser.add_argument("-D", dest="cmake", action="append",
                        help="Additional cmake cache entry")

    parser.add_argument("-v", "--verbose", action="store_true",
                        help="Verbose output")

    parser.add_argument("targets", nargs="*",
                        help="Targets to run. Must be a subset of:"
                        f" {target_names}. Defaults to all targets.")

    args = parser.parse_args()
    if args.targets:
        targets = []
        for name in args.targets:
            if name in TARGETS:
                targets.append(name)
            else:
                print(f"Invalid target {name}")
                return 1
    else:
        targets = TARGETS

    cmake_config_args = []

    if args.cmake:
        cmake_config_args.extend([f"-D{x}" for x in args.cmake])

    cmake_build_args = ["--build", "."]
    if args.verbose:
        cmake_build_args.append("-v")

    target_dict = {
        "lupdate": CMAKE_CMD + cmake_build_args + ["--target", "lupdate"],
        "build": CMAKE_CMD + cmake_build_args,
        "test": get_test_cmd(),
        "install": CMAKE_CMD + cmake_build_args + ["--target", "install"],
    }

    with TemporaryDirectory(prefix="cookiecutter-qt-app-") as temp_dir:
        try:
            os.chdir(temp_dir)
            check_run(["python3", "-m", "cookiecutter", CUTTER_DIR,
                       "--no-input"])
            prefix = os.path.join(temp_dir, "install")
            build_dir = os.path.join("qt-app", "build")
            os.mkdir(build_dir)
            os.chdir(build_dir)
            check_run(CMAKE_CMD + cmake_config_args
                      + [f"-DCMAKE_INSTALL_PREFIX={prefix}", ".."])
            for target in targets:
                check_run(target_dict[target])
        finally:
            if args.shell:
                check_run([os.environ["SHELL"]])

    return 0


if __name__ == "__main__":
    sys.exit(main())
# vi: ts=4 sw=4 et
