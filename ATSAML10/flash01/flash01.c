
#include "flash-bin.h"

void PUT32 ( unsigned int, unsigned int );
//unsigned int GET32 ( unsigned int );
void PUT16 ( unsigned int, unsigned int );
//unsigned int GET16 ( unsigned int );
//void PUT8 ( unsigned int, unsigned int );
unsigned int GET8 ( unsigned int );

#define NVMCTRL_BASE 0x41004000
#define NVM_CTRLA   (NVMCTRL_BASE+0x00)
//#define NVM_CTRLB   (NVMCTRL_BASE+0x04)
//#define NVM_CTRLC   (NVMCTRL_BASE+0x08)
//#define NVM_PARAM   (NVMCTRL_BASE+0x24)
//#define NVM_INTFLAG (NVMCTRL_BASE+0x14)
#define NVM_STATUS  (NVMCTRL_BASE+0x18)
#define NVM_ADDR    (NVMCTRL_BASE+0x1C)

static void flash_busy ( void )
{
    while(1)
    {
        if(GET8(NVM_STATUS)&(1<<2)) break;
    }
}

static void flash_command ( unsigned int cmd )
{
    PUT16(NVM_CTRLA,0xA500+cmd);
    flash_busy();
}

#define FLASH_ER 0x02
#define FLASH_WP 0x04
#define FLASH_PBC 0x44

int notmain ( void )
{
    unsigned int ra;
    unsigned int addr;

    //64 byte page, 0x100 byte row (page * 4)

    flash_busy();
    for(addr=0x0000;addr<0x1000;addr+=0x100)
    {
        PUT32(NVM_ADDR,addr);
        flash_command(FLASH_ER); //erase row
    }

if(1)
{
    flash_command(FLASH_PBC); //page buffer clear
    for(addr=0x0000,ra=0;ra<(0x800>>2);ra++,addr+=4)
    {
        PUT32(addr,rom[ra]);
        if((addr&0x3F)==0x3C)
        {
            flash_command(FLASH_WP); //write page
        }
    }
}

    return(0);
}


