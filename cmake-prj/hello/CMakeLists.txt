message("Build hello library")

# Set the source file list explicitly
set (HELLO_SRC
    main.cpp
    )

# Build the target


# Build test program
add_executable(hello_test ${HELLO_SRC})

# Test program linked libraries
target_link_libraries(hello_test PUBLIC
    Boost::filesystem
    Boost::date_time
    Boost::regex
    )

