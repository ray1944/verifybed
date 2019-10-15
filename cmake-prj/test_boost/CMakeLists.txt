message("Build program with testing boost")

project (testboost)

# Set the source file list explicitly
set (SRCS
    main.cpp
    )

# Include headers
include_directories(${Boost_INCLUDE_DIRS},
    SYSTEM /usr/local/include)

#Create the executable
add_executable(test_boost main.cpp)

# program linked libraries
target_link_libraries(test_boost
    Boost::filesystem
    Boost::date_time)

