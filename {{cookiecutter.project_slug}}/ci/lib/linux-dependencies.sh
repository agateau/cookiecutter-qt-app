main() {
    echo_title "Installing Linux packages"
    if has_command apt-get ; then
        $RUN_AS_ROOT apt-get update
        # file is needed by dpkg to generate shlib dependencies
        $RUN_AS_ROOT apt-get install -y --no-install-recommends \
            clang-format \
            dpkg-dev \
            extra-cmake-modules \
            file \
            g++ \
            git \
            make \
            python3 \
            python3-pip \
            python3-setuptools \
            qtbase5-dev \
            qttools5-dev \
            rpm \
            xvfb
    else
        die "Sorry, I don't know how to install the required packages on your distribution."
    fi

    install_cmake
}
