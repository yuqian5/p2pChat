//
// Created by Kerry Cao on 2020-03-29.
//

#include "P2P.hpp"

P2P::P2P() {
    AES_KEYGEN();

}

P2P::~P2P(){
    RSA_free(RSA_PUBKEY_FRIEND);
    RSA_free(RSA_KEYPAIR_SELF);
}

void P2P::AES_KEYGEN() {
    uint8_t Key[32];
    uint8_t IV[AES_BLOCK_SIZE];
    RAND_bytes(Key, sizeof(Key));
    RAND_bytes(IV, sizeof(IV));

    AESKEY_uint8 = new uint8_t[32];
    memcpy(AESKEY_uint8, Key, sizeof(Key));

    AESKEY = new AES_KEY();
    AES_set_encrypt_key(Key, 256, AESKEY);
}


void P2P::RSA_KEYGEN() {
    BIGNUM *bne;

    unsigned long e = RSA_F4;

    bne = BN_new();
    if(BN_set_word(bne,e) != 1){
        std::cerr << "KeyGen failed\n";
        exit(0x1d);
    }

    RSA_KEYPAIR_SELF = RSA_new();
    if(RSA_generate_key_ex(RSA_KEYPAIR_SELF, RSAKEYSIZE, bne, nullptr) != 1){
        std::cerr << "KeyGen failed\n";
        exit(0x1e);
    }

    BN_free(bne);
}

void P2P::constructFriendlyKey(const std::string& publicKey) {
    // read public key
    BIO* bo = BIO_new(BIO_s_mem());
    BIO_write( bo, publicKey.c_str(),strlen(publicKey.c_str()));
    EVP_PKEY* pkey = nullptr;
    PEM_read_bio_PrivateKey(bo, &pkey, nullptr, nullptr);

    // construct RSA object
    RSA_PUBKEY_FRIEND = EVP_PKEY_get1_RSA(pkey);

    // free memory
    BIO_free(bo);
    EVP_PKEY_free(pkey);
}

ENCRYPTEDMESSAGE P2P::encryptMessage(const std::string& plainMessage) noexcept(true){
    int encrypt_len;
    char *encrypt = static_cast<char *>(malloc(RSA_size(RSA_KEYPAIR_SELF)));

    if((encrypt_len =RSA_public_encrypt(
                        strlen(plainMessage.c_str())+1,
                        (unsigned char*)plainMessage.c_str(),
                        (unsigned char*)encrypt,
                        RSA_KEYPAIR_SELF,
                        RSA_PKCS1_OAEP_PADDING)) == -1) {
        std::cerr << "Encryption Failed" << std::endl;
        exit(0x20);
    }

    ENCRYPTEDMESSAGE encryptedMessage = {std::string(encrypt), encrypt_len};
    return encryptedMessage;
}

std::string P2P::decryptMessage(const std::string& encryptedMessage, const int encrypt_len) noexcept(true){
    char *decrypt = static_cast<char *>(malloc(RSA_size(RSA_PUBKEY_FRIEND)));

    if(RSA_private_decrypt(encrypt_len, (unsigned char*)encrypt, (unsigned char*)decrypt, RSA_KEYPAIR_SELF, RSA_PKCS1_OAEP_PADDING) == -1){
        std::cerr << "Decryption Failed" << std::endl;
        exit(0x1f);
    }

    return std::string(decrypt);
}
