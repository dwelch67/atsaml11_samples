
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define PORTBASE_NS  0x40003000
#define PORTBASE_SEC 0x40003200

#define PORTBASE PORTBASE_NS

#define PORTADIRSET (PORTBASE+0x08)
#define PORTAOUTCLR (PORTBASE+0x14)
#define PORTAOUTSET (PORTBASE+0x18)

#define STK_CSR 0xE000E010
#define STK_RVR 0xE000E014
#define STK_CVR 0xE000E018
#define STK_MASK 0x00FFFFFF


int delay ( unsigned int n )
{
    unsigned int ra;

    while(n--)
    {
        while(1)
        {
            ra=GET32(STK_CSR);
            if(ra&(1<<16)) break;
        }
    }
    return(0);
}


int notmain ( void )
{

    PUT32(PORTADIRSET,1<<15);
    PUT32(PORTADIRSET,1<<16);

    PUT32(STK_CSR,4);
    PUT32(STK_RVR,1000000-1);
    PUT32(STK_CVR,0x00000000);
    PUT32(STK_CSR,5);

    while(1)
    {
        PUT32(PORTAOUTSET,1<<15);
        PUT32(PORTAOUTSET,1<<16);
        //delay(32); //8 seconds
        delay(8);
        PUT32(PORTAOUTCLR,1<<15);
        PUT32(PORTAOUTCLR,1<<16);
        //delay(32); //8 seconds
        delay(8);
    }
    return(0);
}
/*


halt
load_image blinker02/blinker02.sram.elf
resume 0x20000000


*/
