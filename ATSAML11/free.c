

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char data[0x40];


FILE *fp;

int main ( int argc, char *argv[] )
{
    unsigned int ra;

    if(argc<2) return(1);
    fp=fopen(argv[1],"rb");
    if(fp==NULL) return(1);
    fread(data,1,sizeof(data),fp);
    fclose(fp);

    data[0x5]&=(~(1<<3)); //RXN
    data[0x5]&=(~(1<<4)); //DXN


    printf("\n");
    printf("\n");
    printf("mww 0x4100501C 0x804000\n");
    printf("mwh 0x41005000 0xA502\n");
    printf("\n");
    printf("\n");
    printf("mdw 0x804000 0x40\n");
    printf("mdb 0x804000 0x40\n");
    printf("\n");
    printf("\n");
    for(ra=0;ra<0x40;ra+=4)
    {
        printf("mww 0x8040%02X 0x%02X%02X%02X%02X\n",
            ra&0xFF,
            data[ra+3],
            data[ra+2],
            data[ra+1],
            data[ra+0]
            );
    }
    printf("\n");
    printf("\n");
    printf("mww 0x4100501C 0x804000\n");
    printf("mwh 0x41005000 0xA504\n");
    printf("\n");
    printf("\n");
    printf("mdw 0x804000 0x40\n");
    printf("mdb 0x804000 0x40\n");
    printf("\n");
    printf("\n");



    return(0);
}

