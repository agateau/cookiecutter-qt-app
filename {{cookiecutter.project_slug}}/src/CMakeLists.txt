function(JOIN VALUES GLUE OUTPUT)
    string(REPLACE ";" "${GLUE}" _TMP_STR "${VALUES}")
    set(${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

function(GET_INVERSE_ORGANIZATION_NAME ORGANIZATION_NAME OUTPUT)
    string(REPLACE "." ";" ORG_LIST ${ORGANIZATION_NAME})
    list(REVERSE ORG_LIST)
    JOIN("${ORG_LIST}" "." TMP)
    set(${OUTPUT} "${TMP}" PARENT_SCOPE)
endfunction()

# Sources
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Config.h)

set(APPLIB_SRCS
    MainWindow.cpp
    SettingsDialog.cpp
    SettingsDialog.ui
)

qt5_add_resources(APPLIB_RESOURCES app.qrc)

# Translations
# NOTE: Add an entry to translations.qrc as well!
set(TS_FILES
    translations/app_fr.ts
)

# To update .ts (also builds .qm files)
# Use "-locations none" so that .ts files do not change every time lines move
# in source files: that results in noisy diffs
qt5_create_translation(_TRANSLATION_UPDATE
    ${APPLIB_SRCS}
    ${TS_FILES}
    OPTIONS -locations none
)
add_custom_target(lupdate DEPENDS ${_TRANSLATION_UPDATE})

set(TRANSLATIONS_QRC translations.qrc)
configure_file(${TRANSLATIONS_QRC} ${TRANSLATIONS_QRC} COPYONLY)
qt5_add_resources(TRANSLATIONS_RESOURCES ${CMAKE_CURRENT_BINARY_DIR}/${TRANSLATIONS_QRC})

# Building
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# App library
add_library(${APPLIB_NAME} STATIC
    ${APPLIB_SRCS}
    ${APPLIB_RESOURCES}
    ${TRANSLATIONS_RESOURCES}
)
target_include_directories(${APPLIB_NAME} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${APPLIB_NAME}
    Qt5::Core
    Qt5::Widgets
)

# App executable
add_executable(${APP_NAME} MACOSX_BUNDLE main.cpp)

set_target_properties(${APP_NAME} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/packaging/macos/Info.plist.in
)

target_link_libraries(${APP_NAME}
    ${PROJECT_NAME}lib
)

# Install
install(
    TARGETS ${APP_NAME}
    DESTINATION bin
)

GET_INVERSE_ORGANIZATION_NAME(${ORGANIZATION_NAME} INVERSE_ORGANIZATION_NAME)

install(FILES icons/${APP_NAME}.desktop
    DESTINATION share/applications
    RENAME ${INVERSE_ORGANIZATION_NAME}.${APP_NAME}.desktop
)

install(FILES icons/appicon.svg
    DESTINATION share/icons/hicolor/scalable/apps
    RENAME ${APP_NAME}.svg
)
