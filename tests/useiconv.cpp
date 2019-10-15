#include <iostream>
#include <iconv.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int EbcdicToAscii(char* sIn, char *sOut)
{ 
    iconv_t cd;
    size_t  inBytesLeft = 0;
    size_t  outBytesLeft = 0;
    size_t  ret = 0;
    char* inTemp = sIn;
    char* outTemp = sOut;
    char localCode[20], targetCode[20];

    inBytesLeft  = strlen(sIn);
    outBytesLeft = strlen(sIn) * 2;
    memset(&localCode, 0x00, sizeof(localCode));
    sprintf(localCode, "%s", "IBM-037");/*850　ASCII　*/

    memset(&targetCode, 0x00, sizeof(targetCode));
    sprintf(targetCode, "%s", "UTF-8"); /*　037　for　EBCDIC　*/
    cd = iconv_open(targetCode, localCode);

    if (cd == (iconv_t)-1)
    {
        printf("iconv_open failed");
    }

    do {
        ret = iconv(
            cd, (const char* *)&inTemp, &inBytesLeft, &outTemp, &outBytesLeft);
    } while(0);
    printf("iconv returns: %u\n", ret);
    if ( ret == (size_t)-1)
    {
        printf("Error　calling　iconv\n");
        if (iconv_close(cd) == -1)
        {
            printf("Error　calling　iconv_Close\n");    
            return 1;
        }
    }
    
    if (iconv_close(cd) == -1)
    {
        printf("Error　calling　iconv_Close\n");
        return (1);
    }
    printf("0x%x0x%x 0x%x0x%x\n", 
        sOut[0], sOut[1], sOut[2], sOut[3]);
    return 0;
}

int main(int argc, const char* argv[])
{
    const iconv_t CDINVALID = (iconv_t)-1;
    iconv_t cd = CDINVALID;
    char from[2] = {0x41, 0x61};
    char to[30];
    char ebcdic[2] = {0xc1, 0x81};
    

    // cd = iconv_open("UTF-8", "IBM-037");
    // if (cd == CDINVALID)
    // {
    //     std::cout << "iconv_open failed" << std::endl;
    // }
    // size_t fz = sizeof(from);
    // size_t tz = sizeof(to);
    // size_t ret = 0;
    // ret = iconv(cd, (const char**)&from, &fz, (char**)&to, &tz);
    // iconv_close(cd);
    // to[2] = 0;
    memset(to, 0x00, sizeof(to));
    EbcdicToAscii(ebcdic, to);
    std::cout << "to: " << std::endl;
    
    printf("0x%x 0x%x\n", to[0], to[1]);

    return 0;
}