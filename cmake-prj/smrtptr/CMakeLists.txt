message("Build smart pointer test program")

# Set the source file list explicitly
set (SMRTPTR_SRC
    main.cpp
    )

# Build the target


# Build test program
add_executable(smrtptr_test ${SMRTPTR_SRC})

# Test program linked libraries
target_link_libraries(smrtptr_test PUBLIC
    
    )

