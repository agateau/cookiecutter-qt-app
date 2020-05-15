echo_title() {
    echo "========================================="
    echo $*
    echo "========================================="
}

detect_os() {
    local out
    out=$(uname)

    case "$out" in
    Linux)
        OS="linux"
        ;;
    Darwin)
        OS="macos"
        ;;
    MINGW*)
        OS="windows"
        ;;
    *)
        echo "Unknown OS. uname printed '$out'"
        exit 1
        ;;
    esac
}

is_linux() {
    [ "$OS" = "linux" ]
}

is_macos() {
    [ "$OS" = "macos" ]
}

is_windows() {
    [ "$OS" = "windows" ]
}

has_command() {
    command -v "$1" > /dev/null 2>&1
}

die() {
    echo "$*" >&2
    exit 1
}

init_python_cmd() {
    echo_title "Looking for a Python 3 + pip installation"
    for interpreter in python3 python ; do
        if $interpreter -m pip --version 2> /dev/null ; then
            echo "Found $interpreter"
            export PYTHON_CMD=$interpreter
            return
        fi
    done
    die "Can't find a valid Python 3 installation."
}

init_run_as_root() {
    RUN_AS_ROOT=""
    if is_windows ; then
        return
    fi
    if [ $(id -u) = "0" ] ; then
        # Already root
        return
    fi
    if has_command sudo ; then
        RUN_AS_ROOT=sudo
    else
        RUN_AS_ROOT="su -c"
    fi
}

detect_os
init_python_cmd
init_run_as_root

if is_macos ; then
    NPROC=$(sysctl -n hw.ncpu)
else
    NPROC=$(nproc)
fi
