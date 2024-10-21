include(CTest)

add_executable(test_launcher)

target_sources(test_launcher PRIVATE
        ${CMAKE_SOURCE_DIR}/tests/launcher_test.cpp)
target_link_libraries(test_launcher PRIVATE ssl crypto)

add_test(NAME TestLauncher COMMAND test_launcher)