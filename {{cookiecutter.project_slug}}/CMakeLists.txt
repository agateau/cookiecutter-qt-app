cmake_minimum_required(VERSION 3.17)
project({{ cookiecutter.project_slug }}
    VERSION {{ cookiecutter.version }}
    DESCRIPTION "Opinionated Qt-based application template"
    HOMEPAGE_URL "{{ cookiecutter.project_url }}"
)
include(CTest)

set(AUTHOR_NAME "{{ cookiecutter.full_name }}")
set(AUTHOR_EMAIL "{{ cookiecutter.email }}")
set(ORGANIZATION_NAME "{{ cookiecutter.organization_name }}")
set(INVERSE_ORGANIZATION_NAME "{{ cookiecutter.organization_name.split('.')|reverse|join('.') }}")

set(APP_HUMAN_NAME "{{ cookiecutter.project_name }}")

set(APP_NAME ${PROJECT_NAME})
set(APPLIB_NAME ${PROJECT_NAME}lib)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Dependencies
find_package(Qt5 CONFIG REQUIRED Core Widgets Test LinguistTools)
find_package(ECM REQUIRED NO_MODULE)
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

# Build flags
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
    add_compile_options(-Wall -Woverloaded-virtual)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# Source dirs
add_subdirectory(third-party)
add_subdirectory(src)
if (BUILD_TESTING)
    enable_testing() # must come *before* adding tests directory
    add_subdirectory(tests)
endif()
add_subdirectory(packaging)
