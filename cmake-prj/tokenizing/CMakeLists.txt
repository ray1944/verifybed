message("Tokenizing a string ways")

project (tokenizing)

# Set the source file list explicitly
set (SRCS
    main.cpp
    )

# Include headers
include_directories(${Boost_INCLUDE_DIRS},
    SYSTEM /usr/local/include)

#Create the executable
add_executable(tokenizing main.cpp)

# program linked libraries
target_link_libraries(tokenizing
    Boost::filesystem)

