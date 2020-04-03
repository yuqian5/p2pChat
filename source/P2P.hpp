//
// Created by Kerry Cao on 2020-03-29.
//

#ifndef PCHAT_P2P_HPP
#define PCHAT_P2P_HPP

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#include "ChatInterface.hpp"

#define RSAKEYSIZE 4096
#define AESKEYSIZE 256
#define MAXMESSAGELENGTH 511

struct ENCRYPTEDMESSAGE{
    std::string cipher;
    int length;
};

class P2P : private ChatInterface{
public:
    P2P();

    ~P2P();

    void connectNow();
    void handShake();

    void RSA_KEYGEN();
    void AES_KEYGEN();
    void constructFriendlyKey(const std::string& publicKey);

    ENCRYPTEDMESSAGE encryptMessage(const std::string& plainMessage)noexcept(true);
    std::string decryptMessage(const std::string& encryptedMessage, int encrypt_len)noexcept(true);

private:
    RSA *RSA_KEYPAIR_SELF;
    RSA *RSA_PUBKEY_FRIEND;
    AES_KEY *AESKEY;
    uint8_t *AESKEY_uint8;

};


#endif //PCHAT_P2P_HPP
