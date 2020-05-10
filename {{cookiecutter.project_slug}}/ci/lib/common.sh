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

detect_python() {
    if is_windows ; then
        export PYTHON_CMD=python
    else
        export PYTHON_CMD=python3
    fi
}

detect_os
detect_python

if is_macos ; then
    NPROC=$(sysctl -n hw.ncpu)
else
    NPROC=$(nproc)
fi
