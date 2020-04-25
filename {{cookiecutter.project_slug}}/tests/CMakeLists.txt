add_executable(tests
    tests.cpp
    ExampleTest.cpp
)

target_link_libraries(tests
    ${APPLIB_NAME}
    Qt5::Test
    Catch2::Catch2
)

add_test(NAME tests COMMAND tests)
