find_package(Boost REQUIRED)

add_executable(studysync_server
        src/main.cpp
        src/TcpServer.cpp
        include/TcpServer.h
)

target_link_libraries(studysync_server PRIVATE
        studysync_shared
)

target_include_directories(studysync_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(studysync_server PRIVATE ${Boost_INCLUDE_DIRS})