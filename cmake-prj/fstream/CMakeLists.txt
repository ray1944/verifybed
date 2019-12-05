message("Build fstream library")

# Set the source file list explicitly
set (fstream_SRC
    main.cpp
    )

# Build the target


# Build test program
add_executable(fstream_test ${fstream_SRC})

# Test program linked libraries
target_link_libraries(fstream_test PUBLIC
    Boost::filesystem
    Boost::date_time
    Boost::regex
    )

