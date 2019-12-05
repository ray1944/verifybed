message("Build random test program")

# Set the source file list explicitly
set (RANDOM_SRC
    random.cpp
    )

# Build the target


# Build test program
add_executable(random_test ${RANDOM_SRC})

# Test program linked libraries
target_link_libraries(random_test PUBLIC
    
    )

