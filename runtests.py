#!/usr/bin/env python3
"""
Test the cookiecutter
"""
import argparse
import os
import platform
import shlex
import shutil
import sys

from subprocess import run, CalledProcessError

CUTTER_DIR = os.path.abspath(os.path.dirname(__file__))

COOKIECUTTER_CMD = [sys.executable, "-m", "cookiecutter"]

CMAKE_CMD = ["cmake"]

CTEST_CMD = ["ctest", "--verbose", "--build-config", "Debug"]

TARGETS = ["lupdate", "build", "test", "install"]


def wrap_ui_cmd(cmd):
    if platform.system() == "Linux" and "DISPLAY" not in os.environ:
        return ["xvfb-run"] + cmd
    else:
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
        raise


def main():
    target_names = ", ".join(TARGETS)

    parser = argparse.ArgumentParser()
    parser.description = __doc__

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
        "test": wrap_ui_cmd(CTEST_CMD),
        "install": CMAKE_CMD + cmake_build_args + ["--target", "install"],
    }

    work_dir = os.path.join(os.getcwd(), "_work")
    if os.path.exists(work_dir):
        shutil.rmtree(work_dir)
    os.mkdir(work_dir)
    os.chdir(work_dir)

    try:
        check_run(COOKIECUTTER_CMD + [CUTTER_DIR, "--no-input"])
        prefix = os.path.join(work_dir, "install")
        build_dir = os.path.join("qt-app", "build")
        os.mkdir(build_dir)
        os.chdir(build_dir)
        check_run(CMAKE_CMD + cmake_config_args
                  + [f"-DCMAKE_INSTALL_PREFIX={prefix}", ".."])
        for target in targets:
            check_run(target_dict[target])
    except CalledProcessError:
        # Avoid printing the stack trace
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
# vi: ts=4 sw=4 et
