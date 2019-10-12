#project name
PROJECT(testbed)
message("Start to generated makefile ...")

#set minimum cmake version
cmake_minimum_required(VERSION 3.7.0)

# Set platform macro based on OS:
message("Platform: " ${CMAKE_SYSTEM})

###################################################################
# Global Configration
###################################################################

# Set the C++ standard to 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

###################################################################
# Set version info
###################################################################

set(TESTBED_MAJOR_VERSION 0)
set(TESTBED_MINOR_VERSION 01)

###################################################################
# Find reqiured libraries (openssl, libgit2, boost)
###################################################################
find_package(Boost 1.55 COMPONENTS 
                            date_time
                            exception
                            log
                            regex
                            program_options 
                            filesystem
                        REQUIRED
                        )

# Set global include directories
include_directories(
                    ${Boost_INCLUDE_DIRS}
                    )

###################################################################
# Add sub projects
###################################################################
add_subdirectory(hello)
