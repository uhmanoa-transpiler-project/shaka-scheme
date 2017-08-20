# Google Test / Google Mock
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories(${CMAKE_SOURCE_DIR}/dep/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/dep/googletest/googlemock/include)

link_directories(${CMAKE_SOURCE_DIR}/dep/googletest/build/googlemock)
link_directories(${CMAKE_SOURCE_DIR}/dep/googletest/build/googlemock/gtest)

set(gtest "${CMAKE_SOURCE_DIR}}/dep/googletest/build/googlemock/gtest/libgtest.a")
set(gtest_main "${CMAKE_SOURCE_DIR}}/dep/googletest/build/googlemock/gtest/libgtest.a")
set(gmock "${CMAKE_SOURCE_DIR}/dep/googletest/build/googlemock/libgmock.a")
set(gmock_main "${CMAKE_SOURCE_DIR}/dep/googletest/build/googlemock/libgmock_main.a")

# Required for MacOSX systems in order to build successfully with clang++
# sets compiler flags to use the c++11 standard and libc++ as the C++ Standard Library Version
# I don't know what -DGTEST_USE_OWN_TR1_TUPLE does
if (APPLE)
    add_definitions(-std=c++11 -stdlib=libc++ -DGTEST_USE_OWN_TR1_TUPLE)
endif (APPLE)

