message("Build program with subcommand and options")

project (pgm_opts)

# Set the source file list explicitly
set (SRCS
    main.cpp
    )

# Include headers
include_directories(${Boost_INCLUDE_DIRS},
    SYSTEM /usr/local/include)

#Create the executable
add_executable(subcmd1 positional_opts.cpp OptionPrinter.cpp CustomOptionDescription.cpp)
add_executable(subcmd2  main.cpp cmd.cpp app.cpp lscmd.cpp chmodcmd.cpp)

# program linked libraries
target_link_libraries(subcmd1
    Boost::program_options
    Boost::regex
    Boost::filesystem)

target_link_libraries(subcmd2
    Boost::program_options
    Boost::regex
    Boost::filesystem
    Boost::unit_test_framework)


