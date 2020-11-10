ICOUTILS_VERSION=0.32.3
ICOUTILS_URL="https://downloads.sourceforge.net/project/unix-utils/icoutils/icoutils-$ICOUTILS_VERSION-x86_64.zip"
ICOUTILS_SHA1=c8fb976eaceb63bffc3943e4e632f825b5abb5ac

install_icoutils() {
    install_prebuilt_archive $ICOUTILS_URL $ICOUTILS_SHA1 $INSTALL_DIR/icoutils.zip $INSTALL_DIR
    local icotool_exe=$INSTALL_DIR/icoutils-$ICOUTILS_VERSION-x86_64/bin/icotool.exe
    if [ ! -x "$icotool_exe" ] ; then
        die "Can't find icotool.exe: $icotool_exe"
    fi
    prepend_path $(dirname $icotool_exe)
}

install_dependencies() {
    install_icoutils
    install_qt
    install_cmake
    install_ecm
}
