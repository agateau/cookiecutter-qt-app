include(translations)

add_subdirectory(icons)

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
add_translations_build_target(TRANSLATIONS_RESOURCES_SRCS ${TS_FILES})
add_lupdate_target(SOURCES ${APPLIB_SRCS} TS_FILES ${TS_FILES} OPTIONS -no-obsolete)

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

install(FILES packaging/linux/${APP_NAME}.desktop
    DESTINATION share/applications
    RENAME ${INVERSE_ORGANIZATION_NAME}.${APP_NAME}.desktop
)
