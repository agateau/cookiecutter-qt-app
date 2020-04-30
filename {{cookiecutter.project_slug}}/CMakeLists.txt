cmake_minimum_required(VERSION 3.10)
project({{ cookiecutter.project_slug }}
    VERSION {{ cookiecutter.version }}
    DESCRIPTION "Opinionated Qt-based application template"
)

set(AUTHOR_NAME "{{ cookiecutter.full_name }}")
set(AUTHOR_EMAIL "{{ cookiecutter.email }}")
set(ORGANIZATION_NAME "{{ cookiecutter.organization_name }}")

set(APP_HUMAN_NAME "{{ cookiecutter.project_name }}")
set(APP_URL "{{ cookiecutter.project_url }}")

set(APP_NAME ${PROJECT_NAME})
set(APPLIB_NAME ${PROJECT_NAME}lib)

# Dependencies
find_package(Qt5 CONFIG REQUIRED Core Widgets Test LinguistTools)
find_package(Catch2 CONFIG REQUIRED)

# Build flags
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
    add_compile_options(-Wall -Woverloaded-virtual)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# Source dirs
add_subdirectory(src)
add_subdirectory(tests)

enable_testing()

# Packaging
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT "${AUTHOR_NAME} <${AUTHOR_EMAIL}>")

set(CPACK_GENERATOR "DEB;RPM")
set(CPACK_SOURCE_GENERATOR "TBZ2")

## DEB config
set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${APP_URL})
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

## RPM config
set(CPACK_RPM_FILE_NAME "RPM-DEFAULT")
set(CPACK_RPM_PACKAGE_URL ${APP_URL})

## Source config
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES "/build/;/.git/;/__pycache__/;~$")
include(CPack)
