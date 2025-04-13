#include "RSAEncryptorHandler.hpp"
#include "SHAHashHandler.hpp"

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

    return 0;
}