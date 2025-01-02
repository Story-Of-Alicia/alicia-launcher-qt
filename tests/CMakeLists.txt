include(CTest)

add_executable(test_launcher)

find_package(OpenSSL 3 REQUIRED SSL Crypto)

target_sources(test_launcher PRIVATE
        ${CMAKE_SOURCE_DIR}/tests/launcher_test.cpp)
target_link_libraries(test_launcher PRIVATE OpenSSL::SSL OpenSSL::Crypto)

add_test(NAME TestLauncher COMMAND test_launcher)