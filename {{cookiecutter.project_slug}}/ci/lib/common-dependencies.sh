# Functions shared between the $OS-dependencies.sh files

AQTINSTALL_VERSION=0.9.0
AQTINSTALL_ARCHIVES="qtbase qtimageformats qtsvg qttranslations qttools"

QT_ARCH_WINDOWS=win64_msvc2017_64
QT_ARCH_MACOS=clang_64
QT_VERSION=5.12.8

ECM_VERSION=5.69.0

CMAKE_VERSION=3.17.\*

install_qt() {
    echo_title "Installing Qt"
    local qt_install_dir=$INSTALL_DIR/qt
    local aqt_args
    if is_windows ; then
        aqt_args="windows desktop $QT_ARCH_WINDOWS"
    fi
    if is_macos ; then
        aqt_args="mac desktop"
    fi
    $PYTHON_CMD -m pip install aqtinstall==$AQTINSTALL_VERSION
    $PYTHON_CMD -m aqt install --outputdir $qt_install_dir $QT_VERSION $aqt_args --archives $AQTINSTALL_ARCHIVES
    if is_windows ; then
        # Add Qt bin dir to $PATH so that tests can find Qt dlls
        prepend_path $(find $qt_install_dir -type d -a -name bin)
    fi
    # Add Qt plugins dir to $QT_PLUGIN_PATH because the official Qt installer
    # patches QtCore dll so that it finds its plugins, but aqt does not.
    # Not being able to find plugins causes tests to not run on macOS and
    # Windows because they can't find the matching platform plugin.
    add_env_var QT_PLUGIN_PATH $(find $qt_install_dir -type d -a -name plugins)
    add_env_var Qt5_DIR $(find $qt_install_dir -path '*/lib/cmake')
}

install_cmake() {
    echo_title "Installing CMake"
    $PYTHON_CMD -m pip install cmake==$CMAKE_VERSION
}

install_ecm() {
    echo_title "Installing ECM"
    git clone --depth 1 https://anongit.kde.org/extra-cmake-modules.git -b v$ECM_VERSION
    (
        cd extra-cmake-modules
        mkdir build
        cd build
        cmake \
            -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
            -DBUILD_HTML_DOCS=OFF \
            -DBUILD_MAN_DOCS=OFF \
            -DBUILD_QTHELP_DOCS=OFF \
            -DBUILD_TESTING=OFF \
            ..
        cmake --build .
        cmake --build . --target install
    )
}

install_prebuilt_archive() {
    local url=$1
    local sha1=$2
    local download_file=$3
    local unpack_dir=$4

    echo "Downloading '$url'"
    curl --location --continue-at - --output "$download_file" "$url"

    echo "Checking integrity"
    echo "$sha1 $download_file" | sha1sum --check

    echo "Unpacking"
    (
        cd "$unpack_dir"
        case "$download_file" in
            *.zip)
                unzip -q "$download_file"
                ;;
            *.tar.gz|*.tar.bz2|*.tar.xz)
                tar xf "$download_file"
                ;;
            *)
                die "Don't know how to unpack $download_file"
                ;;
        esac
    )
}
