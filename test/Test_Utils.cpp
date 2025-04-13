#include <random>

#include <iostream>

#include "Utils.hpp"

bool test_base64Decoding()
{
    std::string str = "sALDCFHNSAODFHn;oasVNDJP[O}{][asdf[as[fpdkasefionjmasolfnioalsindlas;D";    
    std::string strBase64 = "c0FMRENGSE5TQU9ERkhuO29hc1ZOREpQW099e11bYXNkZlthc1tmcGRrYXNlZmlvbmptYXNvbGZuaW9hbHNpbmRsYXM7RA==";    
    return str == decodeFromBase64(strBase64);
}

bool test_base64Encoding()
{
    std::string str = "sALDCFHNSAODFHn;oasVNDJP[OLAIVSNDP[;WJPASOFDKJ[PAOFSDKJp]AOSJDKOJAOS;JD';OASJD'[poALSIJFD'LSIFDJnl;asdfkj;laskdjbnfv;aklsjdvbn;alksdjvnb;alksdjvbn;lksdajvbn;askldjvb;askdjvbas;kdjfbvn;aslkdjfhn'l;sADKFHJaSASafqawr3weq54r324534fwe327456276gr23g c8t43782tr82tcrb e879387rqwgduyvasudg23978yret21398rte87gfciwegf9weqhf";    
    std::string strBase64 = "c0FMRENGSE5TQU9ERkhuO29hc1ZOREpQW09MQUlWU05EUFs7V0pQQVNPRkRLSltQQU9GU0RLSnBdQU9TSkRLT0pBT1M7SkQnO09BU0pEJ1twb0FMU0lKRkQnTFNJRkRKbmw7YXNkZmtqO2xhc2tkamJuZnY7YWtsc2pkdmJuO2Fsa3NkanZuYjthbGtzZGp2Ym47bGtzZGFqdmJuO2Fza2xkanZiO2Fza2RqdmJhcztrZGpmYnZuO2FzbGtkamZobidsO3NBREtGSEphU0FTYWZxYXdyM3dlcTU0cjMyNDUzNGZ3ZTMyNzQ1NjI3NmdyMjNnIGM4dDQzNzgydHI4MnRjcmIgZTg3OTM4N3Jxd2dkdXl2YXN1ZGcyMzk3OHlyZXQyMTM5OHJ0ZTg3Z2ZjaXdlZ2Y5d2VxaGY=";    
    return strBase64 == encodeInBase64(str);
}

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

    if(!test_base64Encoding())
        return -1;

    if(!test_base64Decoding())
        return -1;

    return 0;
}