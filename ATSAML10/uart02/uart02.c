
void PUT32 ( unsigned int, unsigned int );
void PUT16 ( unsigned int, unsigned int );
void PUT8  ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
unsigned int GET16 ( unsigned int );
unsigned int GET8  ( unsigned int );
void dummy ( unsigned int );


#define PORTBASE_NS  0x40003000
#define PORTBASE_SEC 0x40003200

#define PORTBASE PORTBASE_NS

#define PORTAPMUX8  (PORTBASE+0x38)
#define PORTAPINCFG16 (PORTBASE+0x50)
#define PORTAPINCFG17 (PORTBASE+0x51)

#define MCLKBASE 0x40000800
#define APBCMASK (MCLKBASE+0x1C)

#define GCLKBASE 0x40001C00
#define PCHCTRL12 (GCLKBASE+0xB0)

#define SERCOM1_BASE 0x42000800
#define SERCOM1_CTRLA (SERCOM1_BASE+0x00)
#define SERCOM1_CTRLB (SERCOM1_BASE+0x04)
#define SERCOM1_BAUD  (SERCOM1_BASE+0x0C)
#define SERCOM1_INTFLAG (SERCOM1_BASE+0x18)
#define SERCOM1_SYNCBUSY (SERCOM1_BASE+0x1C)
#define SERCOM1_DATA (SERCOM1_BASE+0x28)

#define DSU_BASE 0x41002000
#define DSU_DID (DSU_BASE+0x18)

#define CPUID 0xE000ED00
#define ACTLR 0xE000E008

static void uart_init ( void )
{
    //unsigned int ra;

    PUT8(PORTAPINCFG16,0x01);
    PUT8(PORTAPINCFG17,0x01);
    PUT8(PORTAPMUX8,0x22);

    //APBCMASK sercoms default to enabled
    //ra=GET32(APBCMASK);
    //ra|=(1<<2); //SERCOM1
    //PUT32(APBCMASK,ra);

    PUT32(PCHCTRL12,0x00000040); //CHEN, GEN0
    while(1)
    {
        if(GET32(PCHCTRL12)&0x40) break; //CHEN
    }
    while(GET32(SERCOM1_SYNCBUSY)) continue;
    PUT32(SERCOM1_CTRLA,0x00000000);
    while(GET32(SERCOM1_SYNCBUSY)) continue;
    PUT32(SERCOM1_CTRLA,0x00000001);
    while(GET32(SERCOM1_SYNCBUSY)) continue;
    PUT32(SERCOM1_CTRLA,0x40100004);
    while(GET32(SERCOM1_SYNCBUSY)) continue;
    PUT32(SERCOM1_CTRLB,0x00030000);
    while(GET32(SERCOM1_SYNCBUSY)) continue;
    PUT16(SERCOM1_BAUD,35337);
    while(GET32(SERCOM1_SYNCBUSY)) continue;
    PUT32(SERCOM1_CTRLA,0x40100006);
    while(GET32(SERCOM1_SYNCBUSY)) continue;
}
static void uart_flush ( void )
{
    while(1)
    {
        if(GET8(SERCOM1_INTFLAG)&2) break;
    }
}
static void uart_send ( unsigned int d )
{
    while(1)
    {
        if(GET8(SERCOM1_INTFLAG)&1) break;
    }
    PUT8(SERCOM1_DATA,d&0xFF);
}
static unsigned int uart_recv ( void )
{
    while(1)
    {
        if(GET8(SERCOM1_INTFLAG)&4) break;
    }
    return(GET8(SERCOM1_DATA)&0xFF);
}

void hexstrings ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_send(rc);
        if(rb==0) break;
    }
    uart_send(0x20);
}

void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}

int notmain ( void )
{
    unsigned int ra;

    uart_init();

    for(ra=0;ra<10000;ra++)
    {
        uart_send(0x30+(ra&7));
    }
    //uart_send(0x0D);
    //uart_send(0x0A);
    hexstring(0x12345678);
    hexstring(GET32(DSU_DID));
    hexstring(GET32(CPUID));
    //hexstring(GET32(ACTLR));
    while(1)
    {
        ra=uart_recv();
        hexstring(ra);
    }
    return(0);
}
/*


halt
load_image uart02/uart02.sram.elf
resume 0x20000000


*/
