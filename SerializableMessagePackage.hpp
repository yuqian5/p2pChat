//
// Created by Kerry Cao on 2020-03-30.
//

#ifndef PCHAT_SERIALIZABLEMESSAGEPACKAGE_HPP
#define PCHAT_SERIALIZABLEMESSAGEPACKAGE_HPP

#include <iostream>

class SerializableMessagePackage {
public:
    SerializableMessagePackage();
    SerializableMessagePackage(std::string identity, std::string message);
    ~SerializableMessagePackage();

    std::string serialize();
    static SerializableMessagePackage deserialize(std::string &serialized);

public:
    std::string &getIdentity();
    std::string &getMessage();

    void setMessage(const std::string &message);
    void setIdentity(const std::string &identity);

private:
    std::string message;
    std::string identity;
};


#endif //PCHAT_SERIALIZABLEMESSAGEPACKAGE_HPP
