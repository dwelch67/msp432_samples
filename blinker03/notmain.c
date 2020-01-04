
//-------------------------------------------------------------------
//-------------------------------------------------------------------

void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void PUT8 ( unsigned int, unsigned int );
unsigned int GET8 ( unsigned int );
void PUT16 ( unsigned int, unsigned int );
unsigned int GET16 ( unsigned int );

void ienable ( void );

#define PORT_BASE 0x40004C00
#define PAOUT_L (PORT_BASE+0x02)
#define PADIR_L (PORT_BASE+0x04)

#define WDTCTL   0x4000480C

#define TIMER32_BASE 0x4000C000

#define ICSR 0xE000ED04
#define SCR 0xE000ED10
#define VTOR 0xE000ED08
#define NVIC_ISER0 0xE000E100
#define NVIC_IABR0 0xE000E300
#define NVIC_ICPR0 0xE000E280

volatile unsigned int ticks;
void timer32_handler ( void )
{
    ticks^=1;
    PUT8(PAOUT_L,ticks);
    PUT32(TIMER32_BASE+0x0C,0);
    PUT32(NVIC_ICPR0,1<<25);
}

int notmain ( void )
{
    PUT16(WDTCTL,0x5A84); //stop WDT
    PUT8(PADIR_L,GET8(PADIR_L)|0x01);
    ticks=0;
    PUT32(VTOR,0x01000000);
    PUT32(NVIC_ISER0,1<<25);
    ienable();
    PUT32(TIMER32_BASE+0x08,0xA4);
    return(0);
}

/*

reset halt
load_image notmain.sram.elf
resume 0x01000000

*/
