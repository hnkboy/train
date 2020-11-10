#include <arpa/inet.h>
#include <stdio.h>




void main(int argn, char *argc[])
{
    unsigned int a;
    unsigned char *p;

    a = 0x01000000;
    p = (unsigned char*)&a;
    //a = htonl(a);
    a = __builtin_bswap32(p);
    printf("a = %x",a);
    return ;
}