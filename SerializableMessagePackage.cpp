//
// Created by Kerry Cao on 2020-03-30.
//

#include "SerializableMessagePackage.hpp"

SerializableMessagePackage::SerializableMessagePackage(std::string identity, std::string message) {
    this->identity = std::move(identity);
    this->message = std::move(message);
}

SerializableMessagePackage::SerializableMessagePackage() = default;

SerializableMessagePackage::~SerializableMessagePackage() = default;

std::string &SerializableMessagePackage::getIdentity() {
    return identity;
}

std::string &SerializableMessagePackage::getMessage() {
    return message;
}

void SerializableMessagePackage::setIdentity(const std::string &identity) {
    SerializableMessagePackage::identity = identity;
}

void SerializableMessagePackage::setMessage(const std::string &message) {
    SerializableMessagePackage::message = message;
}

std::string SerializableMessagePackage::serialize() {
    return identity + "\f\a\b\r\f\f" + message;
}

SerializableMessagePackage SerializableMessagePackage::deserialize(std::string &serialized) {
    SerializableMessagePackage obj;

    std::string identity = serialized.substr(0, serialized.rfind("\f\a\b\r\f\f"));
    std::string message = serialized.substr(serialized.rfind("\f\a\b\r\f\f")+6, serialized.length()-serialized.rfind("\f\a\b\r\f\f")-6);

    obj.setIdentity(identity);
    obj.setMessage(message);
    return obj;
}
