#include <random>

#include "AES256EncryptorHandler.hpp"
#include "Utils.hpp"

bool test_stressTest_randomKeyRandomLengthMessage()
{
    /* Maximum 1 MB messages */
    const int maximumNumberOfBytesOfTheMessage = 1000000;
    const int numberOfIterations = 1000;

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0,maximumNumberOfBytesOfTheMessage);

    AES256EncryptorHandler test;

    for(int i = 0 ; i < numberOfIterations; i++)
    {
        const std::string key = test.generateKey();

        const std::string message = generateRandomString(distribution(generator));

        const std::string cyphertext = test.encrypt(message,key);
    
        if(message != test.decrypt(cyphertext,key))
            return false;
    }

    return true;
}

bool test_stressTest_sameKeyRandomLengthMessage()
{
    /* Maximum 1 MB messages */
    const int maximumNumberOfBytesOfTheMessage = 1000000;
    const int numberOfIterations = 1000;

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0,maximumNumberOfBytesOfTheMessage);

    AES256EncryptorHandler test;

    const std::string key = test.generateKey();


    for(int i = 0 ; i < numberOfIterations; i++)
    {
        const std::string message = generateRandomString(distribution(generator));

        const std::string cyphertext = test.encrypt(message,key);
    
        if(message != test.decrypt(cyphertext,key))
            return false;
    }

    return true;
}

bool test_randomMessages_2048Bit()
{
    AES256EncryptorHandler test;

    const std::string key = test.generateKey();

    const std::string message = generateRandomString(2048);

    const std::string cyphertext = test.encrypt(message,key);

    return message == test.decrypt(cyphertext,key);
}

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

    if(!test_randomMessages_2048Bit())
        return -1;

    if(!test_stressTest_sameKeyRandomLengthMessage())
        return -1;

    if(!test_stressTest_randomKeyRandomLengthMessage())
        return -1;
        
    return 0;
}