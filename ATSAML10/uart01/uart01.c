
void PUT32 ( unsigned int, unsigned int );
void PUT16 ( unsigned int, unsigned int );
void PUT8  ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
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

    PUT32(STK_CSR,4);
    PUT32(STK_RVR,1000000-1);
    PUT32(STK_CVR,0x00000000);
    PUT32(STK_CSR,5);

    while(1)
    {
        PUT16(SERCOM1_DATA,0x55);
        delay(8);
    }
    return(0);
}
/*


halt
load_image uart01/uart01.sram.elf
resume 0x20000000


*/
