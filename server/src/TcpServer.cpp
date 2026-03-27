#include "TcpServer.h"
#include <ctime>
#include <iostream>

TcpConnection::pointer TcpConnection::create(boost::asio::io_context& ioContext) {
    return pointer(new TcpConnection(ioContext));
}
TcpConnection::TcpConnection(boost::asio::io_context& io_context) : socketObject(io_context) {}
tcp::socket& TcpConnection::socket() {
    return socketObject;
}
void TcpConnection::start() {
    std::time_t now = std::time(0);
    message = std::ctime(&now);
    boost::asio::async_write(socketObject, boost::asio::buffer(message),
        [self = shared_from_this()](const boost::system::error_code& error, size_t bytes_transferred) {
            self->handle_write(error, bytes_transferred);
    });
}
void TcpConnection::handle_write(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) std::cout << "sent " << bytes_transferred << " bytes." << std::endl;
    else std::cerr << "write error: " << error.message() << std::endl;
}



TcpServer::TcpServer(boost::asio::io_context& ioContext, int port)
    : io_context_(ioContext),acceptor(ioContext, tcp::endpoint(tcp::v4(), port)) {
    startAccept();
}

void TcpServer::startAccept() {
    TcpConnection::pointer new_connection = TcpConnection::create(io_context_);
    acceptor.async_accept(new_connection->socket(),
        [this, new_connection](const boost::system::error_code& error) {
            this->handleAccept(new_connection, error);
        });
}

void TcpServer::handleAccept(TcpConnection::pointer new_connection, const boost::system::error_code& error) {
    if (!error) {
        std::cout << "client connected" << std::endl;
        new_connection->start();
    } else {
        std::cerr << "Accept error: " << error.message() << std::endl;
    }
    startAccept();
}