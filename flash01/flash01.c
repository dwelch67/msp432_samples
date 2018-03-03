
//-------------------------------------------------------------------
//-------------------------------------------------------------------

void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void PUT16 ( unsigned int, unsigned int );
unsigned int GET16 ( unsigned int );
void PUT8 ( unsigned int, unsigned int );
unsigned int GET8 ( unsigned int );

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

#define PORT_BASE 0x40004C00

#define PAOUT PAOUT_L
#define PAOUT_L (PORT_BASE+0x02)
#define PAOUT_H (PORT_BASE+0x03)
#define PADIR PADIR_L
#define PADIR_L (PORT_BASE+0x04)
#define PADIR_H (PORT_BASE+0x05)

#define WDTCTL   0x4000480C

int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;
    //unsigned int re;
    unsigned int bad;

    bad=0;
    PUT16(WDTCTL,0x5A84); //stop WDT

    PUT32(FLCTL_BANK0_MAIN_WEPROT,0xFFFFFFFE);
    PUT32(FLCTL_ERASE_CTLSTAT,0x00080000);
    PUT32(FLCTL_CLRIFG,0xFFFFFFFF);
    PUT32(FLCTL_IE,0x00000000);
    PUT32(FLCTL_ERASE_SECTADDR,0x00000000);
    PUT32(FLCTL_ERASE_CTLSTAT,0x00000001); //start erasing

    while(1)
    {
        rb=GET32(FLCTL_ERASE_CTLSTAT);
        //re=GET32(FLCTL_IFG);
        rc=rb&0x30000;
        if(rc==0x30000) break;
    }
    if(rb&0x40000) bad++;
    PUT32(FLCTL_ERASE_CTLSTAT,0x00080000);
    PUT32(FLCTL_BANK0_MAIN_WEPROT,0xFFFFFFFF);

    //LED on if it worked.
    PUT8(PADIR_L,GET8(PADIR_L)|0x01);
    ra=GET8(PAOUT_L);
    if(bad) ra&=(~1);
    else    ra|=1;
    PUT8(PAOUT_L,ra);

    return(0);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
