#include <iostream>
#include <TcpServer.h>

int main(int argc, char* argv[]) {
    std::cout << "Server Started..." << std::endl;
    try {
        boost::asio::io_context io_context;
        TcpServer server(io_context, 8080);

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}