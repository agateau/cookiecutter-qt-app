FROM ubuntu:18.04

RUN apt-get update \
    && apt-get install -y -qq --no-install-recommends \
        clang-format \
        cmake \
        dpkg-dev \
        file \
        g++ \
        git \
        make \
        ninja-build \
        python3 \
        qt5-default \
        qtbase5-dev \
        qttools5-dev \
        rpm \
        xvfb

ENTRYPOINT ["/bin/bash"]
