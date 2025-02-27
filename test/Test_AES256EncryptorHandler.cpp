#include "AES256EncryptorHandler.hpp"

bool test_helloWorld()
{
    AES256EncryptorHandler test;

    const std::string key = test.generateKey();

    const std::string message = "Hello world!";

    const std::string cyphertext = test.encrypt(message,key);

    return message == test.decrypt(cyphertext,key);
}

int main (int argc, char* argv[])
{
    if(!test_helloWorld())
        return -1;
        
    return 0;
}