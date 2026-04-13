#include "MessageRouter.h"
#include "Database.h"
#include <ctime>
#include <string>

void registerServerRoutes() {
    auto& router = MessageRouter::getInstance();

    router.registerRoute("ping", [](const boost::json::object& req, boost::json::object& res) {
        res["status"] = "success";
    });

    router.registerRoute("time", [](const boost::json::object& req, boost::json::object& res) {
        std::time_t now = std::time(0);
        std::string timeStr = std::ctime(&now);
        if (!timeStr.empty() && timeStr.back() == '\n') timeStr.pop_back();

        res["data"] = timeStr;
        res["status"] = "success";
    });

    router.registerRoute("createUser", [](const boost::json::object& req, boost::json::object& res) {
        std::string username = req.at("username").as_string().c_str();
        std::string email = req.at("email").as_string().c_str();
        std::string password = req.at("password").as_string().c_str();

        int newId = Database::getInstance().createUser(username, email, password);
        if (newId != -1) {
            Database::getInstance().createTemplateForUser(newId);
            res["status"] = "success";
            res["message"] = "User created successfully";
            res["sync_counter"] = Database::getInstance().getSyncCounter();
        } else {
            res["status"] = "error";
            res["message"] = "Username already exists.";
        }
    });

    router.registerRoute("login", [](const boost::json::object& req, boost::json::object& res) {
        std::string username = req.at("username").as_string().c_str();
        std::string password = req.at("password").as_string().c_str();
        int userId = -1;

        if (Database::getInstance().validateLogin(username, password, userId)) {
            res["status"] = "success";
            std::string token = "session_" + std::to_string(userId) + "_" + std::to_string(time(0));
            LoginPayload payload = Database::getInstance().getFullUserData(userId, token);
            res["payload"] = payload.toJson();
            res["sync_counter"] = Database::getInstance().getSyncCounter();
        } else {
            res["status"] = "error";
            res["message"] = "Invalid username or password.";
        }
    });

    router.registerRoute("deleteUser", [](const boost::json::object& req, boost::json::object& res) {
        int userId = req.at("userId").as_int64();
        Database::getInstance().deleteUser(userId);

        res["status"] = "success";
        res["sync_counter"] = Database::getInstance().getSyncCounter();
    });
}