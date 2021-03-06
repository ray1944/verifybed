PROJECT(myproject)
message("Start to generated makefile ...")

#set minimum cmake version
cmake_minimum_required(VERSION 3.14.0)

message("Platform: " ${CMAKE_SYSTEM})

###################################################################
# Global Configration
###################################################################

# Set the C++ standard to 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# set(FETCHCONTENT_SOURCE_DIR_BOOST /Users/ray1944/workspace/aldon/src/boost_1_70_0)
# add_subdirectory(boost-cmake)

###################################################################
# Find reqiured libraries (openssl, libgit2, boost)
###################################################################
find_package(Libssh2 REQUIRED CONFIG)
find_package(Boost 1.55 COMPONENTS 
    date_time
    exception
    log
    regex
    program_options 
    system
    filesystem
    unit_test_framework
    REQUIRED
    )

# Set global include directories
include_directories(
    ${Boost_INCLUDE_DIRS}
    )

##################################
# build test directory tree travels
##################################
add_subdirectory(traveldir)

###################################################
# build program options with boost program_options
###################################################
add_subdirectory(pgm_opts)
add_subdirectory(test_boost)
add_subdirectory(tokenizing)
add_subdirectory(variant)
add_subdirectory(asio)
add_subdirectory(hello)
add_subdirectory(fstream)
add_subdirectory(random)
add_subdirectory(smrtptr)
