# Boost C++ Libraries
find_package(Threads REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/dep/boost_1_64_0/)

# Apple
if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)
