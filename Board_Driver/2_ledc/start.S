.global _start

_start:
    /*设置SVC模式 */
    mrs r0, cpsr /*读取cpsr寄存器 */
    bic r0, r0, #0x1f /*清除cpsr bit 4-0 */
    orr r0, r0, #0x13   /*使用svc模式 */
    msr cpsr, r0    /*将r0写入cpsr */


    /*设置SP指针 */
    ldr sp, =0x80200000
    b main      /*跳转到C语言卖弄函数 */
