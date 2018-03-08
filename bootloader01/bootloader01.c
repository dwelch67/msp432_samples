
//-------------------------------------------------------------------
//-------------------------------------------------------------------

void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void PUT8 ( unsigned int, unsigned int );
unsigned int GET8 ( unsigned int );
void PUT16 ( unsigned int, unsigned int );
unsigned int GET16 ( unsigned int );
void dummy ( unsigned int );
unsigned int GETPC ( void );
void zap ( unsigned int, unsigned int, unsigned int );

#define FLCTL_BASE 0x40011000
#define FLCTL_PRG_CTLSTAT       (FLCTL_BASE+0x050)
#define FLCTL_PRGBRST_CTLSTAT   (FLCTL_BASE+0x054)
#define FLCTL_ERASE_CTLSTAT     (FLCTL_BASE+0x0A0)
#define FLCTL_ERASE_SECTADDR    (FLCTL_BASE+0x0A4)
#define FLCTL_BANK0_INFO_WEPROT (FLCTL_BASE+0x0B0)
#define FLCTL_BANK0_MAIN_WEPROT (FLCTL_BASE+0x0B4)
#define FLCTL_BANK1_INFO_WEPROT (FLCTL_BASE+0x0C0)
#define FLCTL_BANK1_MAIN_WEPROT (FLCTL_BASE+0x0C4)
#define FLCTL_IFG               (FLCTL_BASE+0x0F0)
#define FLCTL_IE                (FLCTL_BASE+0x0F4)
#define FLCTL_CLRIFG            (FLCTL_BASE+0x0F8)

extern const unsigned int flash_data_words;
extern const unsigned int flash_data[];

extern const unsigned int flash_data_words_wdt;
extern const unsigned int flash_data_wdt[];

#define UART0_BASE 0x40001000
#define UCA0CTLW0   (UART0_BASE+0x00)
#define UCA0BRW     (UART0_BASE+0x06)
#define UCA0MCTLW   (UART0_BASE+0x08)
#define UCA0RXBUF   (UART0_BASE+0x0C)
#define UCA0TXBUF   (UART0_BASE+0x0E)
#define UCA0IE      (UART0_BASE+0x1A)
#define UCA0IFG     (UART0_BASE+0x1C)

#define PORT_BASE 0x40004C00
#define PASEL0_L (PORT_BASE+0x0A)
#define PASEL1 PASEL1_L
#define PASEL1_L (PORT_BASE+0x0C)

#define WDTCTL   0x4000480C

static void uart_init ( void )
{
    PUT8(PASEL1_L,GET8(PASEL1_L)&0xF3);
    PUT8(PASEL0_L,GET8(PASEL0_L)|0x0C);

    PUT16(UCA0CTLW0,0x0081);
    //PUT16(UCA0BRW,104); //12000000/115200 = 104
    PUT16(UCA0BRW,26); //3000000/115200 = 26
    PUT16(UCA0MCTLW,0x0000);
    PUT16(UCA0IE,0);
    PUT16(UCA0CTLW0,0x0081);
    PUT16(UCA0CTLW0,0x0080);
}

static unsigned int uart_recv ( void )
{
    while(1)
    {
        if(GET16(UCA0IFG)&1) break;
    }
    return(GET16(UCA0RXBUF));
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

static unsigned int ctonib ( unsigned int c )
{
    if(c>0x39) c-=7;
    return(c&0xF);
}
// 00000
// 20000
// 32768 = 0x8000
#define ADDMASK  0x00007FFF
#define ADDCHECK 0xFFFF8000
#define ADDMATCH 0x00020000
#define ADDTOP   0x00028000
#define TEMPRAM  0x20004000
static unsigned int entry;
static unsigned int errors;
static unsigned int mypc;

static void write_byte ( unsigned int a, unsigned int d )
{
    if((a&ADDCHECK)!=ADDMATCH) errors++;
    PUT8(TEMPRAM+(a&ADDMASK),d);
}

static void erase_sector ( unsigned int add )
{
    unsigned int ra;
    unsigned int rb;

    PUT32(FLCTL_ERASE_SECTADDR,add);
    PUT32(FLCTL_ERASE_CTLSTAT,0x00000001);
    while(1)
    {
        ra=GET32(FLCTL_ERASE_CTLSTAT);
        rb=ra&0x30000;
        if(rb==0x30000) break;
    }
    PUT32(FLCTL_ERASE_CTLSTAT,0x00080000);
}

static void write_word ( unsigned int a, unsigned int d )
{
    unsigned int ra;
    unsigned int rb;

    PUT32(a,d);
    while(1)
    {
        ra=GET32(FLCTL_PRG_CTLSTAT);
        rb=ra&0x30000;
        if(rb==0x00000) break;
        if(rb==0x30000) break;
    }
}

static void write_flash ( void )
{
    unsigned int add;
    unsigned int sadd;

    hexstring(0xEEEEEEEE);

    PUT32(FLCTL_BANK1_MAIN_WEPROT,0xFFFFFF00);
    PUT32(FLCTL_ERASE_CTLSTAT,0x00080000);
    PUT32(FLCTL_CLRIFG,0xFFFFFFFF);
    PUT32(FLCTL_IE,0x00000000);

    for(add=ADDMATCH;add<ADDTOP;add+=0x1000)
    {
        hexstring(add);
        erase_sector(add);
    }
    hexstring(0xDDDDDDDD);
    PUT32(FLCTL_PRG_CTLSTAT,0xC1);
    for(add=ADDMATCH,sadd=TEMPRAM;add<ADDTOP;add+=4,sadd+=4)
    {
        if((add&0xFFF)==0) hexstring(add);
        write_word(add,GET32(sadd));
    }
    PUT32(FLCTL_BANK1_MAIN_WEPROT,0xFFFFFFFF);
    hexstring(0xFFFFFFFF);
}

static void write_bounce ( void )
{
    unsigned int add;
    unsigned int rf;

    hexstring(0xEEEEEEEE);

    PUT32(FLCTL_BANK0_MAIN_WEPROT,0xFFFFFFFE);
    PUT32(FLCTL_ERASE_CTLSTAT,0x00080000);
    PUT32(FLCTL_CLRIFG,0xFFFFFFFF);
    PUT32(FLCTL_IE,0x00000000);

    add=0x00000000;
    hexstring(add);
    erase_sector(add);
    hexstring(0xDDDDDDDD);
    PUT32(FLCTL_PRG_CTLSTAT,0xC1);
    for(rf=0,add=0x00000;rf<flash_data_words;rf++,add+=4)
    {
        write_word(add,flash_data[rf]);
    }
    PUT32(FLCTL_BANK0_MAIN_WEPROT,0xFFFFFFFF);
    hexstring(0xFFFFFFFF);
}

static void no_bounce ( void )
{
    unsigned int add;
    unsigned int rf;

    hexstring(0xEEEEEEEE);

    PUT32(FLCTL_BANK0_MAIN_WEPROT,0xFFFFFFFE);
    PUT32(FLCTL_ERASE_CTLSTAT,0x00080000);
    PUT32(FLCTL_CLRIFG,0xFFFFFFFF);
    PUT32(FLCTL_IE,0x00000000);

    add=0x00000000;
    hexstring(add);
    erase_sector(add);
    hexstring(0xDDDDDDDD);
    PUT32(FLCTL_PRG_CTLSTAT,0xC1);
    for(rf=0,add=0x00000;rf<flash_data_words_wdt;rf++,add+=4)
    {
        write_word(add,flash_data_wdt[rf]);
    }
    PUT32(FLCTL_BANK0_MAIN_WEPROT,0xFFFFFFFF);
    hexstring(0xFFFFFFFF);
}

int notmain ( void )
{
    unsigned int ra;

    unsigned int state;
    unsigned int type;
    unsigned int count;
    unsigned int sum;
    unsigned int addr;
    unsigned int data;

    PUT16(WDTCTL,0x5A84); //stop WDT

    uart_init();
    hexstring(0x12345678);
    mypc=GETPC();
    hexstring(mypc);

    zap(TEMPRAM,0x1000,0xFFFFFFFF);

    uart_send('S');
    uart_send('R');
    uart_send('E');
    uart_send('C');
    uart_send(0x0D);
    uart_send(0x0A);

    errors=0;
    data=0;
    state=0;
    count=0;
    sum=0;
    addr=0;
    type=0;
    entry=0xFFFFFFFF;
    while(1)
    {
        ra=uart_recv();
    //PUT16(UCA0TXBUF,ra);
        switch(state)
        {
            case 0:
            {
                if(ra=='S')
                {
                    sum=0;
                    state++;
                    break;
                }
                else
                if((ra=='w')||(ra=='W'))
                {
                    write_flash();
                    write_bounce();
                }
                else
                if((ra=='z')||(ra=='Z'))
                {
                    hexstring(addr);
                    no_bounce();
                }
                break;
            }
            case 1:
            {
                switch(ra)
                {
                    case '0':
                    {
                        state=0;
                        break;
                    }
                    case '3':
                    {
                        type=3;
                        state++;
                        break;
                    }
                    case '7':
                    {
                        type=7;
                        state++;
                        break;
                    }
                    default:
                    {
                        hexstring(ra);
                        hexstring(0xBADBAD00);
                        return(1);
                    }
                }
                break;
            }
            case 2:
            {
                count=ctonib(ra);
                state++;
                break;
            }
            case 3:
            {
                count<<=4;
                count|=ctonib(ra);
                if(count<5)
                {
                    hexstring(0xBADBAD01);
                    return(1);
                }
                sum+=count&0xFF;
                addr=0;
                state++;
                break;
            }
            case  4:
            case  6:
            case  8:
            case 10:
            {
                addr<<=4;
                addr|=ctonib(ra);
                state++;
                break;
            }
            case  5:
            case  7:
            case  9:
            {
                count--;
                addr<<=4;
                addr|=ctonib(ra);
                sum+=addr&0xFF;
                state++;
                break;
            }
            case 11:
            {
                count--;
                addr<<=4;
                addr|=ctonib(ra);
                sum+=addr&0xFF;
                state++;
                break;
            }
            case 12:
            {
                data=ctonib(ra);
                state++;
                break;
            }
            case 13:
            {
                data<<=4;
                data|=ctonib(ra);
                sum+=data&0xFF;
                count--;
                if(count==0)
                {
                    if(type==7)
                    {
                        entry=addr;
                        hexstring(entry);
                        hexstring(errors);
                        if(errors) hexstring(0xBADBAD);
                        //else       write_flash();
                    }
                    sum&=0xFF;
                    if(sum!=0xFF)
                    {
                        hexstring(0xBADBAD02);
                        return(1);
                    }
                    state=0;
                }
                else
                {
                    write_byte(addr,data);
                    addr++;
                    state=12;
                }
                break;
            }
        }
    }
    return(0);
}

//-------------------------------------------------------------------------
// Copyright (c) 2018 David Welch dwelch@dwelch.com
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//-------------------------------------------------------------------------
/*

reset halt
load_image utemp/bootloader01.sram.elf
resume 0x01000000

*/
