
//-------------------------------------------------------------------
//-------------------------------------------------------------------

void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void PUT8 ( unsigned int, unsigned int );
unsigned int GET8 ( unsigned int );
void PUT16 ( unsigned int, unsigned int );
unsigned int GET16 ( unsigned int );

void ienable ( void );

#define UART0_BASE 0x40001000
#define UCA0CTLW0   (UART0_BASE+0x00)
#define UCA0BRW     (UART0_BASE+0x06)
#define UCA0MCTLW   (UART0_BASE+0x08)
#define UCA0TXBUF   (UART0_BASE+0x0E)
#define UCA0IE      (UART0_BASE+0x1A)
#define UCA0IFG     (UART0_BASE+0x1C)

#define PORT_BASE 0x40004C00
#define PASEL0_L (PORT_BASE+0x0A)
#define PASEL1_L (PORT_BASE+0x0C)

#define WDTCTL   0x4000480C

#define TIMER32_BASE 0x4000C000

#define ICSR 0xE000ED04
#define SCR 0xE000ED10
#define VTOR 0xE000ED08
#define NVIC_ISER0 0xE000E100
#define NVIC_IABR0 0xE000E300
#define NVIC_ICPR0 0xE000E280

static void uart_init ( void )
{
    PUT8(PASEL1_L,GET8(PASEL1_L)&0xF3);
    PUT8(PASEL0_L,GET8(PASEL0_L)|0x0C);

    PUT16(UCA0CTLW0,0x0081);
    PUT16(UCA0BRW,26); //3000000/115200 = 26
    PUT16(UCA0MCTLW,0x0000);
    PUT16(UCA0IE,0);
    PUT16(UCA0CTLW0,0x0081);
    PUT16(UCA0CTLW0,0x0080);
}

static void uart_send ( unsigned int x )
{
    while(1)
    {
        if(GET16(UCA0IFG)&2) break;
    }
    PUT16(UCA0TXBUF,x);
}

static void hexstrings ( unsigned int d )
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

static void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}

void timer32_handler ( void )
{
}

int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;

    PUT16(WDTCTL,0x5A84); //stop WDT
    uart_init();
    hexstring(0x12345678);

    rb=0;

    PUT32(TIMER32_BASE+0x08,0xA8);
    while(1)
    {
        hexstrings(GET32(TIMER32_BASE+0x04));
        hexstrings(GET32(TIMER32_BASE+0x10));
        ra=GET32(TIMER32_BASE+0x14);
        hexstrings(ra);
        if(ra&1)
        {
            PUT32(TIMER32_BASE+0x0C,0);
            rb++;
        }
        hexstrings(rb);
        hexstring(GET32(ICSR));
    }

    return(0);
}


/*

reset halt
load_image notmain.sram.elf
resume 0x01000000

*/
