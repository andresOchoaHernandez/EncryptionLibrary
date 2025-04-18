/**
 * @file SHAHashHandler.cpp
 * @author Andres Ochoa Hernandez
 * @brief Implementation file for SHAHashHandler.hpp
 */

#include <openssl/evp.h>

#include <vector>

#include "SHAHashHandler.hpp"
#include "Utils.hpp"

std::string SHA256HashHandler::hash(const std::string& payload)
{
    EVP_MD *md = EVP_MD_fetch(nullptr, "SHA256", nullptr);
    if (md == nullptr) 
    {
        throw HashHandlerException("Error fetching SHA256 hash algorithm");
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == nullptr) 
    {
        EVP_MD_free(md);
        throw HashHandlerException("Error creating MD Context");
    }

    int digestInitResult = EVP_DigestInit(mdctx, md);
    if (digestInitResult <= 0) 
    {
        EVP_MD_free(md);
        EVP_MD_CTX_free(mdctx);
        throw HashHandlerException("Error while initializing the digest context");
    }

    int digestUpdateResult = EVP_DigestUpdate(mdctx, payload.c_str(), payload.size());
    if (digestUpdateResult <= 0) 
    {
        EVP_MD_free(md);
        EVP_MD_CTX_free(mdctx);
        throw HashHandlerException("Error while updating the digest context");
    }
    
    std::vector<unsigned char> digestedPayload(EVP_MAX_MD_SIZE);
    uint digestedPayloadSize;

    int digestFinalResult = EVP_DigestFinal_ex(mdctx, digestedPayload.data(), &digestedPayloadSize);
    if (digestFinalResult <= 0) 
    {
        EVP_MD_free(md);
        EVP_MD_CTX_free(mdctx);
        throw HashHandlerException("Error while finalizing the digest context");
    }

    EVP_MD_free(md);
    EVP_MD_CTX_free(mdctx);

    digestedPayload.resize(digestedPayloadSize);
    
    return encodeInBase64(digestedPayload);
}