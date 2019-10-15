message("Build asio test")

# Set the source file list explicitly
set (ASIO_SRC_TIMER
    timer.cpp
    )

set (ASIO_SRC_TCPCLT
    tcpclt.cpp
    )

set (ASIO_SRC_LIBSSH2
    ssh_clt_base.cpp
    ssh_clt.cpp
    asio_ssh2.cpp
)

# Build the target


# Build test program
add_executable(timer_test ${ASIO_SRC_TIMER})
add_executable(tcpclient_test ${ASIO_SRC_TCPCLT})
add_executable(asio_ssh2_test ${ASIO_SRC_LIBSSH2})

# Test program linked libraries
target_link_libraries(timer_test PUBLIC
    Boost::filesystem
    Boost::date_time
    Boost::regex
    )

target_link_libraries(tcpclient_test PUBLIC
    Boost::filesystem
    Boost::date_time
    Boost::regex
    )

target_link_libraries(asio_ssh2_test PUBLIC
    Boost::filesystem
    Boost::date_time
    Boost::regex
    Libssh2::libssh2
    ncurses
    )