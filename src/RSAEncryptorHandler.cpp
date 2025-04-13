/**
 * @file RSAEncryptorHandler.cpp
 * @author Andres Ochoa Hernandez
 * @brief Implementation file for RSAEncryptorHandler.hpp
 */

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/decoder.h>

#include <vector>

#include "RSAEncryptorHandler.hpp"

EVP_PKEY* stringToEVP_PKEY(const std::string& stringKey,int keyType)
{
    const unsigned char* key = reinterpret_cast<unsigned char*>(const_cast<char*>(stringKey.c_str()));
    size_t keylen = stringKey.size();

    EVP_PKEY* pkey = nullptr;

    OSSL_DECODER_CTX* dctx = OSSL_DECODER_CTX_new_for_pkey(&pkey, "PEM", nullptr, "RSA", keyType, nullptr, nullptr);
    if (dctx == nullptr) 
    {
        throw CryptoHandlerException("Failed to create OSSL_DECODER_CTX");
    }

    int decodeFromDataResult = OSSL_DECODER_from_data(dctx, &key, &keylen);
    if (decodeFromDataResult <= 0) 
    {
        throw CryptoHandlerException("Failed to decode PEM key from data");
    }

    OSSL_DECODER_CTX_free(dctx);

    return pkey;
}

EVP_PKEY* privateKeyStringToEVP_PKEY(const std::string& privateKey)
{
    return stringToEVP_PKEY(privateKey,OSSL_KEYMGMT_SELECT_KEYPAIR);
}

EVP_PKEY* publicKeyStringToEVP_PKEY(const std::string& publicKey)
{
    return stringToEVP_PKEY(publicKey,OSSL_KEYMGMT_SELECT_PUBLIC_KEY);
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
    if(ctx == nullptr)
    {
        throw CryptoHandlerException("Failed to create EVP_PKEY_CTX object");
    }

    int intializeKeyGenResult = EVP_PKEY_keygen_init(ctx);
    if (intializeKeyGenResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to initialize the key object");
    }

    int setRsaBitsResult = EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits);
    if (setRsaBitsResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to set key length");
    }

    EVP_PKEY *key = nullptr;

    int keyGenResult = EVP_PKEY_keygen(ctx, &key);

    if (keyGenResult<= 0) 
    {
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
    EVP_PKEY *publicKey = publicKeyStringToEVP_PKEY(key);

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(publicKey, nullptr);
    if(ctx == nullptr)
    {
        throw CryptoHandlerException("Failed to create EVP_PKEY_CTX object");
    }

    int initializeEncryptionResult = EVP_PKEY_encrypt_init(ctx);
    if (initializeEncryptionResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to initialize the encryption object");
    }

    int setRsaPaddingResult = EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);
    if (setRsaPaddingResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to set the RSA padding");
    }

    size_t cipertextLength;

    int determineOutputLengthResult = EVP_PKEY_encrypt(
        ctx,
        nullptr, 
        &cipertextLength,
        reinterpret_cast<unsigned char*>(const_cast<char*>(plaintext.c_str())), 
        static_cast<int>(plaintext.length())
    );
    
    if (determineOutputLengthResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to determine the cyphertext length");
    }

    std::vector<unsigned char> cyphertext(cipertextLength);

    int encryptionResult = EVP_PKEY_encrypt(
        ctx,
        cyphertext.data(), 
        &cipertextLength,
        reinterpret_cast<unsigned char*>(const_cast<char*>(plaintext.c_str())), 
        static_cast<int>(plaintext.length())
    );
    
    if (encryptionResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to encrypt the plaintext");
    }

    EVP_PKEY_free(publicKey);
    EVP_PKEY_CTX_free(ctx);

    return std::string(cyphertext.begin(), cyphertext.end());
}

std::string RSAEncryptorHandler::decrypt(const std::string& cyphertext,const std::string& key)
{
    EVP_PKEY *privateKey = privateKeyStringToEVP_PKEY(key);

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(privateKey, nullptr);
    if(ctx == nullptr)
    {
        throw CryptoHandlerException("Failed to create EVP_PKEY_CTX object");
    }

    int initializeDecryptionResult = EVP_PKEY_decrypt_init(ctx);
    if (initializeDecryptionResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to initialize the decryption object");
    }

    int setRsaPaddingResult = EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING);
    if (setRsaPaddingResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to set the RSA padding");
    }

    size_t plainTextLength;

    int determineOutputLengthResult = EVP_PKEY_decrypt(
        ctx,
        nullptr, 
        &plainTextLength,
        reinterpret_cast<unsigned char*>(const_cast<char*>(cyphertext.c_str())), 
        static_cast<int>(cyphertext.length())
    );
    
    if (determineOutputLengthResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to determine the plaintext length");
    }

    std::vector<unsigned char> plaintext(plainTextLength);

    int decryptionResult = EVP_PKEY_decrypt(
        ctx,
        plaintext.data(), 
        &plainTextLength,
        reinterpret_cast<unsigned char*>(const_cast<char*>(cyphertext.c_str())), 
        static_cast<int>(cyphertext.length())
    );
    
    if (decryptionResult <= 0) 
    {
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to decrypt the cyphertext");
    }

    EVP_PKEY_free(privateKey);
    EVP_PKEY_CTX_free(ctx);

    return std::string(plaintext.begin(), plaintext.end());
}

std::string RSAEncryptorHandler::signMessageDigestSha256(const std::string& payload,const std::string& privateKey)
{
    EVP_PKEY *pKey = privateKeyStringToEVP_PKEY(privateKey);

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pKey, nullptr);
    if(ctx == nullptr)
    {
        EVP_PKEY_free(pKey);
        throw CryptoHandlerException("Failed to create EVP_PKEY_CTX object");
    }

    int initializeSigningInitializationResult = EVP_PKEY_sign_init(ctx);
    if (initializeSigningInitializationResult <= 0) 
    {
        EVP_PKEY_free(pKey);
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to initialize the initialization object");
    }

    int setRsaPaddingResult = EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING);
    if (setRsaPaddingResult <= 0) 
    {
        EVP_PKEY_free(pKey);
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to set the RSA padding");
    }

    /* Decoding the digest from base64 */
    int predictedPayloadBase64EncodedLength = 3*payload.size()/4;
    std::vector<unsigned char> payloadDecoded(predictedPayloadBase64EncodedLength);
    int decodeBlockResult = EVP_DecodeBlock(
        payloadDecoded.data(), 
        reinterpret_cast<unsigned char*>(const_cast<char*>(payload.c_str())), 
        payload.size()
    );

    if(decodeBlockResult != predictedPayloadBase64EncodedLength)
    {
        throw CryptoHandlerException("Error while decoding the hash from base64, predicted output length doesn't match the actual length");
    }

    size_t signatureLength;
    int determineSignatureLength = EVP_PKEY_sign(
        ctx, 
        nullptr, 
        &signatureLength, 
        payloadDecoded.data(), 
        payloadDecoded.size()
    );

    if (determineSignatureLength <= 0)
    {
        EVP_PKEY_free(pKey);
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to determine the signature length");
    }

    std::vector<unsigned char> signature(signatureLength);

    int signatureResult = EVP_PKEY_sign(
        ctx, 
        signature.data(), 
        &signatureLength, 
        payloadDecoded.data(), 
        payloadDecoded.size()
    );

    if (signatureResult <= 0)
    {
        EVP_PKEY_free(pKey);
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to sign the payload");
    }

    EVP_PKEY_free(pKey);
    EVP_PKEY_CTX_free(ctx);

    return std::string(signature.begin(), signature.end());
}

bool RSAEncryptorHandler::verifyMessageDigestSha256(const std::string& messageDigest,const std::string& digitalSignature,const std::string& publicKey)
{
    EVP_PKEY *pKey = publicKeyStringToEVP_PKEY(publicKey);

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pKey, nullptr);
    if(ctx == nullptr)
    {
        EVP_PKEY_free(pKey);
        throw CryptoHandlerException("Failed to create EVP_PKEY_CTX object");
    }

    int initializingVerifyContextResult = EVP_PKEY_verify_init(ctx);
    if (initializingVerifyContextResult <= 0) 
    {
        EVP_PKEY_free(pKey);
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to initialize the initialization object");
    }

    int setRsaPaddingResult = EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING);
    if (setRsaPaddingResult <= 0) 
    {
        EVP_PKEY_free(pKey);
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Failed to set the RSA padding");
    }

    /* Decoding the digest from base64 */
    int predictedPayloadBase64EncodedLength = 3*messageDigest.size()/4;
    std::vector<unsigned char> messageDigestDecoded(predictedPayloadBase64EncodedLength);
    int decodeBlockResult = EVP_DecodeBlock(
        messageDigestDecoded.data(), 
        reinterpret_cast<unsigned char*>(const_cast<char*>(messageDigest.c_str())), 
        messageDigest.size()
    );

    if(decodeBlockResult != predictedPayloadBase64EncodedLength)
    {
        EVP_PKEY_free(pKey);
        EVP_PKEY_CTX_free(ctx);
        throw CryptoHandlerException("Error while decoding the hash from base64, predicted output length doesn't match the actual length");
    }

    int verifyResult = EVP_PKEY_verify(
        ctx, 
        reinterpret_cast<unsigned char*>(const_cast<char*>(digitalSignature.c_str())), 
        digitalSignature.size(), 
        messageDigestDecoded.data(), 
        messageDigestDecoded.size()
    );

    EVP_PKEY_free(pKey);
    EVP_PKEY_CTX_free(ctx);

    return verifyResult == 1;
}