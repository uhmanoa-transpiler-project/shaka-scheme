project(shaka_scheme_tests)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Adding macro to ease the creation to tests.
# - Just provide the TEST_NAME without the .cpp suffix,
#   and make sure that the CMakeLists file is in the same directory.
macro(macro_shaka_scheme_test TEST_NAME)
    message("Test: ${TEST_NAME}")
    add_executable(${TEST_NAME}
            ${TEST_NAME}.cpp)
    target_link_libraries(${TEST_NAME} Threads::Threads)
    target_link_libraries(${TEST_NAME} gmock gtest gmock_main)
    target_link_libraries(${TEST_NAME} ${SHAKA_SCHEME_LIBRARY_NAME})
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tst)
endmacro(macro_shaka_scheme_test)

add_subdirectory(shaka_scheme)

macro_shaka_scheme_test(integ-HelloWorld)

