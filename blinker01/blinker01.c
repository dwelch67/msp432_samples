
//-------------------------------------------------------------------
//-------------------------------------------------------------------

void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void PUT8 ( unsigned int, unsigned int );
unsigned int GET8 ( unsigned int );
void PUT16 ( unsigned int, unsigned int );
unsigned int GET16 ( unsigned int );
void dummy ( unsigned int );

#define PORT_BASE 0x40004C00

#define PAOUT PAOUT_L
#define PAOUT_L (PORT_BASE+0x02)
#define PAOUT_H (PORT_BASE+0x03)
#define PADIR PADIR_L
#define PADIR_L (PORT_BASE+0x04)
#define PADIR_H (PORT_BASE+0x05)

#define DELAY_COUNT 200000

#define WDTCTL   0x4000480C

void delay ( unsigned int x )
{
    while(x--) dummy(x);
}
int notmain ( void )
{
    unsigned int ra;

    PUT16(WDTCTL,0x5A84); //stop WDT

    PUT8(PADIR_L,GET8(PADIR_L)|0x01);
    ra=GET8(PAOUT_L);
    while(1)
    {
        ra^=1;
        PUT8(PAOUT_L,ra);
        delay(DELAY_COUNT);
        ra^=1;
        PUT8(PAOUT_L,ra);
        delay(DELAY_COUNT);
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


halt
load_image blinker01/blinker01.sram.elf
resume 0x01000000


*/
