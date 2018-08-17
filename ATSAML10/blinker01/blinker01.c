
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define PORTBASE 0x40003000

#define PORTADIRSET (PORTBASE+0x08)
#define PORTAOUTCLR (PORTBASE+0x14)
#define PORTAOUTSET (PORTBASE+0x18)

int notmain ( void )
{
    unsigned int ra;
    unsigned int rx;

    PUT32(PORTADIRSET,1<<15);
    PUT32(PORTADIRSET,1<<16);

    for(rx=0;;rx++)
    {
        PUT32(PORTAOUTSET,1<<15);
        PUT32(PORTAOUTSET,1<<16);
        for(ra=0;ra<200000;ra++) dummy(ra);
        PUT32(PORTAOUTCLR,1<<15);
        PUT32(PORTAOUTCLR,1<<16);
        for(ra=0;ra<200000;ra++) dummy(ra);
    }
    return(0);
}
/*


halt
load_image blinker01/blinker01.sram.elf
resume 0x20000000


*/
