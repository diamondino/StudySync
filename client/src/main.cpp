#include <QApplication>
#include "Window.ui"
#include "ClientNetworkManager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    ClientNetworkManager api("127.0.0.1", "8080");
    api.setOnConnectCallback([&api]() {
        std::cout << "Connected to server" << std::endl;
        std::cout << "testing tcp" << std::endl;
        api.ping([](bool success) {
            std::cout << "testing ping: " << (success ? "Success" : "Failed") << std::endl;
        });

        api.getTime([](std::string timeStr) {
            std::cout << timeStr << std::endl;
        });

        api.printString("Hello world", [](bool success) {
            std::cout << "Print string result: " << (success ? "Success" : "Failed") << std::endl;
        });
    });
    QApplication app(argc, argv);
    Window w;
    w.show();
    return app.exec();
}
