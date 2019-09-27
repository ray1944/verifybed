message("Build common library")

project (traveltree)

# Set the source file list explicitly
set (SRCS
    main.cpp
    )

# Include headers
include_directories(${Boost_INCLUDE_DIRS},
 SYSTEM /usr/local/include)

#Create the executable
add_executable(${PROJECT_NAME} ${SRCS})

# program linked libraries
target_link_libraries(${PROJECT_NAME}  
    Boost::program_options
    Boost::regex
    Boost::filesystem)


