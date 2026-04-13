#pragma once
#include "ClientNetworkManager.h"
#include <memory>
#include <string>
#include <functional>
#include <boost/json.hpp>

class ServerAPI {
public:
    ServerAPI(std::shared_ptr<ClientNetworkManager> networkManager);

    void login(const std::string& username, const std::string& password, std::function<void(bool, const std::string&)> callback);

    void createUser(const std::string& username, const std::string& email, const std::string& password, std::function<void(bool)> callback);

private:
    std::shared_ptr<ClientNetworkManager> network;
};