/**
 * @file AES256EncryptorHandler.cpp
 * @author Andres Ochoa Hernandez
 * @brief Implementation file for AES256EncryptorHandler.hpp
 */

#include <openssl/evp.h>
#include <openssl/aes.h>

#include <vector>

#include "AES256EncryptorHandler.hpp"

#include "Utils.hpp"

std::string AES256EncryptorHandler::generateKey()
{
    return generateRandomString(32);
}

std::string AES256EncryptorHandler::encrypt(const std::string& plaintext,const std::string& key)
{
    std::string key256Bit = padString(key,32,'0');
    std::string iv128Bit = generateRandomString(AES_BLOCK_SIZE);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(ctx == nullptr)
    {
        throw CryptoHandlerException("Failed to create EVP_CIPHER_CTX object");
    }

    int encryptInitResult = 
        EVP_EncryptInit_ex(
            ctx, 
            EVP_aes_256_gcm(), 
            nullptr, 
            reinterpret_cast<unsigned char*>(const_cast<char*>(key256Bit.c_str())), 
            reinterpret_cast<unsigned char*>(const_cast<char*>(iv128Bit.c_str()))
        );

    if (encryptInitResult != 1) 
    {
        EVP_CIPHER_CTX_free(ctx);
        throw CryptoHandlerException("Failed to create initialize symmetric encryption object");
    }

    std::vector<unsigned char> cyphertext(plaintext.size() + AES_BLOCK_SIZE);
    int cipertextLength;

    int encryptUpdateResult = 
        EVP_EncryptUpdate(
            ctx, 
            cyphertext.data(), 
            &cipertextLength, 
            reinterpret_cast<unsigned char*>(const_cast<char*>(plaintext.c_str())), 
            static_cast<int>(plaintext.length())
        );

    if (encryptUpdateResult != 1) 
    {
        EVP_CIPHER_CTX_free(ctx);
        throw CryptoHandlerException("Failed to update the encryption");
    }

    cyphertext.resize(cipertextLength);

    EVP_CIPHER_CTX_free(ctx);
    
    return iv128Bit + encodeInBase64(cyphertext);
}

std::string AES256EncryptorHandler::decrypt(const std::string& base64EncodedCyphertext,const std::string& key)
{
    std::string key256Bit = padString(key,32,'0');
    std::string iv128Bit(AES_BLOCK_SIZE,'0');

    std::copy(base64EncodedCyphertext.begin(), base64EncodedCyphertext.begin() + AES_BLOCK_SIZE, iv128Bit.begin());


    std::vector<unsigned char> cyphertext = decodeFromBase64(std::string(base64EncodedCyphertext.begin() + AES_BLOCK_SIZE,base64EncodedCyphertext.end()));

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if(ctx == nullptr)
    {
        throw CryptoHandlerException("Failed to create EVP_CIPHER_CTX object");
    }

    int decryptInitResult = 
        EVP_DecryptInit_ex(
            ctx, 
            EVP_aes_256_gcm(), 
            nullptr, 
            reinterpret_cast<unsigned char*>(const_cast<char*>(key256Bit.c_str())), 
            reinterpret_cast<unsigned char*>(const_cast<char*>(iv128Bit.c_str()))
        );

    if (decryptInitResult != 1) 
    {
        EVP_CIPHER_CTX_free(ctx);
        throw CryptoHandlerException("Failed to create initialize symmetric decryption object");
    }

    std::vector<unsigned char> plaintext(cyphertext.size());
    int plaintextLength;

    int decryptUpdateResult = 
        EVP_DecryptUpdate(
            ctx, 
            plaintext.data(), 
            &plaintextLength, 
            cyphertext.data(), 
            cyphertext.size()
        );

    if (decryptUpdateResult != 1) 
    {
        EVP_CIPHER_CTX_free(ctx);
        throw CryptoHandlerException("Failed to update the decryption object");
    }

    plaintext.resize(plaintextLength);

    EVP_CIPHER_CTX_free(ctx);

    return std::string(plaintext.begin(), plaintext.end());
}