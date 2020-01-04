
.thumb

.thumb_func
.global _start
_start:
b reset
nop
.word loop /*0x0004 1    Reset                   */
.word loop /*0x0008 2    NMI                     */
.word loop /*0x000C 3    HardFault               */
.word loop /*0x0010 4    MemManage               */
.word loop /*0x0014 5    BusFault                */
.word loop /*0x0018 6    UsageFault              */
.word loop /*0x001C 7    Reserved                */
.word loop /*0x0020 8    Reserved                */
.word loop /*0x0024 9    Reserved                */
.word loop /*0x0028 10   Reserved                */
.word loop /*0x002C 11   SVCall                  */
.word loop /*0x0030 12   DebugMonitor            */
.word loop /*0x0034 13   Reserved                */
.word loop /*0x0038 14   PendSV                  */
.word loop /*0x003C 15   SysTick                 */
.word loop /*0x0040 16   External interrupt  0   */
.word loop /*0x0044 17   External interrupt  1   */
.word loop /*0x0048 18   External interrupt  2   */
.word loop /*0x004C 19   External interrupt  3   */
.word loop /*0x0050 20   External interrupt  4   */
.word loop /*0x0054 21   External interrupt  5   */
.word loop /*0x0058 22   External interrupt  6   */
.word loop /*0x005C 23   External interrupt  7   */
.word loop /*0x0060 24   External interrupt  8   */
.word loop /*0x0064 25   External interrupt  9   */
.word loop /*0x0068 26   External interrupt 10   */
.word loop /*0x006C 27   External interrupt 11   */
.word loop /*0x0070 28   External interrupt 12   */
.word loop /*0x0074 29   External interrupt 13   */
.word loop /*0x0078 30   External interrupt 14   */
.word loop /*0x007C 31   External interrupt 15   */
.word loop /*0x0080 32   External interrupt 16   */
.word loop /*0x0084 33   External interrupt 17   */
.word loop /*0x0088 34   External interrupt 18   */
.word loop /*0x008C 35   External interrupt 19   */
.word loop /*0x0090 36   External interrupt 20   */
.word loop /*0x0094 37   External interrupt 21   */
.word loop /*0x0098 38   External interrupt 22   */
.word loop /*0x009C 39   External interrupt 23   */
.word loop /*0x00A0 40   External interrupt 24   */
.word timer32_handler /*0x00A4 41   External interrupt 25   */
.word loop /*0x00A8 42   External interrupt 26   */
.word loop /*0x00AC 43   External interrupt 27   */
.word loop /*0x00B0 44   External interrupt 28   */
.word loop /*0x00B4 45   External interrupt 29   */
.word loop /*0x00B8 46   External interrupt 30   */
.word loop /*0x00BC 47   External interrupt 31   */
.word loop /*0x00C0 48   External interrupt 32   */

reset:
    cpsid i
    ldr r0,stacktop
    mov sp,r0
    bl notmain
    b loop

.thumb_func
loop:   b .

.align
stacktop: .word 0x20008000

.thumb_func
.globl ienable
ienable:
    cpsie i
    bx lr

.thumb_func
.globl PUT8
PUT8:
    strb r1,[r0]
    bx lr

.thumb_func
.globl GET8
GET8:
    ldrb r0,[r0]
    bx lr

.thumb_func
.globl PUT16
PUT16:
    strh r1,[r0]
    bx lr

.thumb_func
.globl GET16
GET16:
    ldrh r0,[r0]
    bx lr

.thumb_func
.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.thumb_func
.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.thumb_func
.globl get_addr
get_addr:
    ldr r0,=timer32_handler
    bx lr

