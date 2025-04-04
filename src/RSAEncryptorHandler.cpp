/**
 * @file RSAEncryptorHandler.cpp
 * @author Andres Ochoa Hernandez
 * @brief Implementation file for RSAEncryptorHandler.hpp
 */

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#include "RSAEncryptorHandler.hpp"

EVP_PKEY* keypairToEVP_PKEY(RsaKeyPair keyPair)
{
    return nullptr;
}

RsaKeyPair EVP_PKEYToKeypair(EVP_PKEY* keyPair)
{
    char *bp;
    size_t size;
    FILE *stream;

    /* Writing public key to a string */
    stream = open_memstream (&bp, &size);
    PEM_write_PUBKEY(stream, keyPair);
    fflush (stream);
    std::string publicKeyString = bp;
    fclose (stream);

    /* Writing private key to a string */
    stream = open_memstream (&bp, &size);
    PEM_write_PrivateKey(stream, keyPair, nullptr, nullptr, 0, nullptr, nullptr);
    fflush (stream);
    std::string privateKeyString = bp;
    fclose (stream);

    return {publicKeyString,privateKeyString};
}

RsaKeyPair RSAEncryptorHandler::generateKeyPair(int bits)
{
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    if(ctx == nullptr){
        throw CryptoHandlerException("Failed to create EVP_PKEY_CTX object");
    }

    int intializeKeyGenResult = EVP_PKEY_keygen_init(ctx);
    if (intializeKeyGenResult <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to initialize the key object");
    }

    int setRsaBitsResult = EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits);
    if (setRsaBitsResult <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to set key length");
    }

    EVP_PKEY *key = nullptr;

    int keyGenResult = EVP_PKEY_keygen(ctx, &key);

    if (keyGenResult<= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to generate the keypair");
    }

    RsaKeyPair result = EVP_PKEYToKeypair(key);

    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(ctx);

    return result;
}

std::string RSAEncryptorHandler::encrypt(const std::string& plaintext,const std::string& key)
{
    return "";
}

std::string RSAEncryptorHandler::decrypt(const std::string& cyphertext,const std::string& key)
{
    return "";
}