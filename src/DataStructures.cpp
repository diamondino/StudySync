#include "DataStructures.h"

User::User(int id, const std::string &username, bool hasAiAccess) : id(id), username(username), hasAiAccess(hasAiAccess) {}
int User::getId() const { return id;}
std::string User::getUsername() const { return username; }
bool User::getAiAcess() const { return hasAiAccess; }


void User::setId(int id) { this->id = id; }
void User::setUsername(const std::string &username) { this->username = username; }
void User::setAiAccess(bool hasAiAccess) { this->hasAiAccess = hasAiAccess; }

boost::json::object User::toJson() const {
    boost::json::object jsonObject = {
        {"id", id},
        {"username", username},
        {"aiAccess", hasAiAccess}
    };
    return jsonObject;
}

User User::fromJson(const boost::json::object& obj) {
    int id = obj.at("id").as_int64();
    std::string username = obj.at("username").as_string().c_str();
    bool hasAiAccess = obj.at("aiAccess").as_bool();
    return User(id, username, hasAiAccess);
}