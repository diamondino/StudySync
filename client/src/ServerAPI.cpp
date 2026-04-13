#include "ServerAPI.h"
#include "ui/ClientState.h"    // Needed to update the state
#include "DataStructures.h" // Needed for LoginPayload

ServerAPI::ServerAPI(std::shared_ptr<ClientNetworkManager> networkManager)
    : network(std::move(networkManager)) {}

void ServerAPI::login(const std::string& username, const std::string& password, std::function<void(bool, const std::string&)> callback) {
    boost::json::object payload = {
        {"username", username},
        {"password", password}
    };

    network->sendRequest("login", payload, [callback](const boost::json::object& response) {
        bool success = response.contains("status") &&
                       response.at("status").as_string() == "success";

        std::string msg = response.contains("message")
            ? response.at("message").as_string().c_str()
            : "";

        if (success && response.contains("payload")) {
            try {
                LoginPayload loginData = LoginPayload::fromJson(response.at("payload").as_object());
                ClientState::loadFromPayload(loginData);
            } catch (const std::exception& e) {
                success = false;
                msg = "Data parsing error: " + std::string(e.what());
            }
        }

        callback(success, msg);
    });
}

void ServerAPI::createUser(const std::string& username, const std::string& email, const std::string& password, std::function<void(bool)> callback) {
    boost::json::object payload = {
        {"username", username},
        {"email", email},
        {"password", password}
    };

    network->sendRequest("createUser", payload, [callback](const boost::json::object& response) {
        bool success = response.contains("status") && response.at("status").as_string() == "success";
        callback(success);
    });
}