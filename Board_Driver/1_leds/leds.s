.global _start /*全局标号 */

_start:

    /*使能所有外设时钟 */
    ldr r0, =0x020c4068 @CCGR0
    ldr r1, =0xffffffff @要向CCGR0写入的数据
    str r1, [r0] @将0xffffffff写入CCGR0

    ldr r0, =0x020c406c @CCGR1
    str r1, [r0] @将0xffffffff写入CCGR1

    ldr r0, =0x020c4070 @CCGR2
    str r1, [r0] @将0xffffffff写入CCGR2

    ldr r0, =0x020c4074 @CCGR3
    str r1, [r0] @将0xffffffff写入CCGR3

    ldr r0, =0x020c4078 @CCGR4
    str r1, [r0] @将0xffffffff写入CCGR4

    ldr r0, =0x020c407c @CCGR5
    str r1, [r0] @将0xffffffff写入CCGR5

    ldr r0, =0x020c4080 @CCGR6
    str r1, [r0] @将0xffffffff写入CCGR6

    /*配置PIN复用为GPIO */
    ldr r0, =0x020e006c @IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO04地址
    ldr r1, =0x5 @写入5
    str r1, [r0] @向寄存器地址写入5，配置为GPIO

    /*配置电气属性 */

    /*
    bit0: 0 低速率
    bit 5:3 : 110 R0/6驱动能力
    bit 7:6 : 10 100MHz速度
    bit 11: 0 关闭开路输出
    bit 12: 1 使能pull/keeper
    bit 13: 0 kepper
    bit15:14: 00 100K下拉
    bit 16: 0 关闭hys
     */

    ldr r0, =0x020e02f8 @IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO04  GPIO1_IO4
    ldr r1, =0x10b0 
    str r1, [r0] @向寄存器地址写入5，配置为GPIO

    /*设置GPIO */
    ldr r0, =0x0209c004 @GPIO1_GDIR地址
    ldr r1, =0x16 @写入8 output
    str r1, [r0] @向寄存器地址写入5，配置为GPIO

    ldr r0, =0x0209c000 @GPIO1_DR地址
    ldr r1, =0x0 @GPIO5_IO3=0
    str r1, [r0] @向寄存器地址写入0，配置为GPIO

   loop:
    b loop
