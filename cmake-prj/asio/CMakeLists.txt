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

set (ASIO_SRC_GETPW
    pwd.cpp
)

set (ASIO_ECHO_SERVER_SRC
    tcp_echo_server.cpp
)

set (ASIO_ECHO_CLT_SRC
    tcp_echo_client.cpp
)

set (ASIO_THRD_SRC
    thread_test.cpp
    )

set (ASIO_ASYNC_SRV_SRC
    async_srv1.cpp
    )

# Build the target


# Build test program
add_executable(timer_test ${ASIO_SRC_TIMER})
add_executable(tcpclient_test ${ASIO_SRC_TCPCLT})
add_executable(asio_ssh2_test ${ASIO_SRC_LIBSSH2})
add_executable(getpwd ${ASIO_SRC_GETPW})
add_executable(tcp_echo_srv_test ${ASIO_ECHO_SERVER_SRC})
add_executable(tcp_echo_clt_test ${ASIO_ECHO_CLT_SRC})
add_executable(thread_test ${ASIO_THRD_SRC})
add_executable(async_tcp_srv ${ASIO_ASYNC_SRV_SRC})
add_executable(async_tcp_srv1 async_tcp_srv_test.cpp)

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
    )

target_link_libraries(getpwd PUBLIC
    ncurses
)

target_link_libraries(thread_test PUBLIC
    Boost::thread
)

target_link_libraries(async_tcp_srv PUBLIC
    Boost::thread
)

target_link_libraries(async_tcp_srv1
    Boost::thread
)