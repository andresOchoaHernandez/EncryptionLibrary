#include <random>

#include "Utils.hpp"

bool test_randomStringLength()
{
    const int maxStrLen = 10000;

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0,maxStrLen);

    const int strLen = distribution(generator);
    
    std::string randomString = generateRandomString(strLen);

    return randomString.size() == strLen;
}

bool test_padStringRandom()
{
    const int maxStrLen = 10000;

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0,maxStrLen);

    const int strLen = distribution(generator);
    const int nOfBytes = distribution(generator);

    std::string testString = "";

    for(int i = 0; i < strLen; i++)
    {
        testString += "1";
    }

    std::string argString = testString; 

    if(nOfBytes < strLen)
    {
        testString =  testString.substr(0,nOfBytes);
    }
    else if(nOfBytes > strLen)
    {
        int diffElems =  nOfBytes - strLen;

        for(int i = 0; i < diffElems ; i++)
        {
            testString += 'A';
        }
    }

    return testString == padString(argString,nOfBytes,'A');
}

bool test_padString()
{
    std::string testString = "hello111111111111111111111111111";
    return testString == padString("hello",32,'1');
}

int main (int argc, char* argv[])
{
    if(!test_padString())
        return -1;

    if(!test_padStringRandom())
        return -1;

    if(!test_randomStringLength())
        return -1;
        
    return 0;
}