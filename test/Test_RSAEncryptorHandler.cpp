#include <random>

#include "RSAEncryptorHandler.hpp"
#include "SHAHashHandler.hpp"
#include "Utils.hpp"

#include <iostream>

bool test_stressTest_randomKeyRandomLengthMessage()
{
    const int maximumNumberOfBytesOfTheMessage = 256;
    const int numberOfIterations = 1000;

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0,maximumNumberOfBytesOfTheMessage);

    RSAEncryptorHandler test;

    for(int i = 0 ; i < numberOfIterations; i++)
    {
        const RsaKeyPair key = test.generateKeyPair(2048);

        const std::string message = generateRandomString(distribution(generator));

        const std::string cyphertext = test.encrypt(message,key.publicKey);
    
        const std::string decryptedMessage = test.decrypt(cyphertext,key.privateKey);

        if(message != decryptedMessage)
        {
            std::cout << message.size() << std::endl;
            std::cout << message << std::endl;
            std::cout << decryptedMessage.size() << std::endl;
            std::cout << decryptedMessage << std::endl;
            return false;
        }
    }

    return true;
}

bool test_signature()
{
    RSAEncryptorHandler test;
    RsaKeyPair res =  test.generateKeyPair(2048);
    const std::string message = "Hello world!";

    SHA256HashHandler hasher; 
    const std::string messageDigest = hasher.hash(message);
    const std::string signedDigest = test.signMessageDigestSha256(messageDigest,res.privateKey);
    const bool verifyResult = test.verifyMessageDigestSha256(messageDigest,signedDigest,res.publicKey);

    return verifyResult;
}

bool test_helloWorld()
{
    RSAEncryptorHandler test;
        
    RsaKeyPair res =  test.generateKeyPair(2048);

    const std::string message = "Hello world!";

    const std::string cyphertext = test.encrypt(message,res.publicKey);
    
    /* RSA at 2048 bits supports messages of maximum 256 bytes */
    const std::string decryptedMessage = test.decrypt(cyphertext,res.privateKey).substr(0,message.size());

    return message == decryptedMessage;
}

int main (int argc, char* argv[])
{
    if(!test_helloWorld())
        return -1;

    if(!test_signature())
        return -1;

    if(!test_stressTest_randomKeyRandomLengthMessage())
        return -1;

    return 0;
}