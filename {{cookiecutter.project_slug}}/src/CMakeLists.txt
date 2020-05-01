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

# Generate a .qrc file to hold generated .qm files.
# Takes .ts files as optional parameters
function(CREATE_TRANSLATIONS_QRC TRANSLATIONS_QRC)
    set(TS_FILES=${ARGN})

    file(WRITE ${TRANSLATIONS_QRC} "<RCC>\n  <qresource prefix='/translations'>\n")
    foreach(ts_file ${TS_FILES})
        get_filename_component(name_we ${ts_file} NAME_WE)
        file(APPEND ${TRANSLATIONS_QRC} "    <file>${name_we}.qm</file>\n")
    endforeach()
    file(APPEND ${TRANSLATIONS_QRC} "  </qresource>\n</RCC>\n")
endfunction()

# Create a target to build a source file containing all the translations.
# Takes .ts files as optional parameters
function(CREATE_TRANSLATIONS_BUILD_TARGET RES_SRCS_VARNAME)
    set(TS_FILES=${ARGN})

    # Add targets to build .ts files into .qm files
    qt5_add_translation(QM_FILES ${TS_FILES})
    add_custom_target(build_qm DEPENDS ${QM_FILES})

    set(TRANSLATIONS_QRC ${CMAKE_CURRENT_BINARY_DIR}/translations.qrc)
    create_translations_qrc(${TRANSLATIONS_QRC} ${TS_FILES})

    set(RES_SRCS ${CMAKE_CURRENT_BINARY_DIR}/qrc_translations.cpp)

    # Build the translations qrc. Declare the command ourselves instead of using
    # CMake rcc automation so that we can tell CMake it depends on the "build_qm"
    # target
    add_custom_command(OUTPUT ${RES_SRCS}
        COMMAND Qt5::rcc -o ${RES_SRCS} --name translations ${TRANSLATIONS_QRC}
        DEPENDS build_qm
    )

    set(${RES_SRCS_VARNAME} "${RES_SRCS}" PARENT_SCOPE)
endfunction()

# Sources
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/BuildConfig.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/BuildConfig.h
)

set(APPLIB_SRCS
    MainWindow.cpp
    MainWindow.ui
    SettingsDialog.cpp
    SettingsDialog.ui
)

qt5_add_resources(APPLIB_RESOURCES_SRCS app.qrc)

# Translations
set(TS_FILES
    translations/app_fr.ts
    translations/app_es.ts
)
create_translations_build_target(TRANSLATIONS_RESOURCES_SRCS ${TS_FILES})

# Add an "lupdate" target. Use this target to update the .ts files from the
# latest source files.
add_custom_target(lupdate
    COMMAND Qt5::lupdate ${APPLIB_SRCS} -ts ${TS_FILES} -no-obsolete
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# App library
add_library(${APPLIB_NAME} STATIC
    ${APPLIB_SRCS}
    ${APPLIB_RESOURCES_SRCS}
    ${TRANSLATIONS_RESOURCES_SRCS}
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
