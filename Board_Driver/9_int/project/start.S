.global _start


_start:
    ldr pc, =Reset_Handler  //复位中断函数
    ldr pc, =Undefined_Handler  //未定义指令中断函数
    ldr pc, =SVC_Handler  //SVC中断函数
    ldr pc, =PreAbort_Handler  //预取中止中断函数
    ldr pc, =DataAbort_Handler  //数据中止中断函数
    ldr pc, =Notused_Handler  //未使用
    ldr pc, =IRQ_Handler  //IRQ中断
    ldr pc, =FIQ_Handler  //FIQ中断

    //复位终端服务函数
Reset_Handler:

    cpsid  i    //关闭IRQ

    //关闭I，D cache 和 MMU
    //修改SCTLR寄存器，采用读改写的方式
        MRC p15, 0, r0, c1, c0, 0 //读取SCTLR寄存器的数据到r0寄存器
        bic r0, r0, #(1<<12) //关闭I Cache
        bic r0, r0, #(1<<11) //关闭分支预测
        bic r0, r0, #(1<<2) //关闭D Cache
        bic r0, r0, #(1<<1) //关闭对齐
        bic r0, r0, #(1<<0) //关闭MMU
        MCR p15, 0, r0, c1, c0, 0 //将r0寄存器的数据写入SCTLR寄存器


    //设置中断向量偏移
#        ldr r0, =0x87800000
#        dsb
#        isb
#        MCR p15, 0, r0, c12, c0, 0     //设置VBAR寄存器=0x87800000
#        dsb
#        isb


.global _bss_start
_bss_start:
    .word __bss_start

.global _bss_end
_bss_end:
    .word __bss_end


    /*清楚BSS段*/
        ldr r0, _bss_start
        ldr r1, _bss_end
        mov r2, #0
bss_loop:
        stmia r0!, {r2} 
        cmp r0, r1  /*比较r0和r1的值*/
        ble bss_loop    /*如果r0地址小于等于r1， 继续清除bss段*/  

    /*设置IRQ模式 */
        mrs r0, cpsr /*读取cpsr寄存器 */
        bic r0, r0, #0x1f /*清除cpsr bit 4-0 */
        orr r0, r0, #0x12   /*使用IRQ模式 */
        msr cpsr, r0    /*将r0写入cpsr */
    /*设置IRQ模式下的SP指针 */
        ldr sp, =0x80600000

    /*设置SYS模式 */
        mrs r0, cpsr /*读取cpsr寄存器 */
        bic r0, r0, #0x1f /*清除cpsr bit 4-0 */
        orr r0, r0, #0x1f   /*使用IRQ模式 */
        msr cpsr, r0    /*将r0写入cpsr */
    /*设置SYS模式下的SP指针 */
        ldr sp, =0x80400000

    /*设置SVC模式 */
        mrs r0, cpsr /*读取cpsr寄存器 */
        bic r0, r0, #0x1f /*清除cpsr bit 4-0 */
        orr r0, r0, #0x13   /*使用svc模式 */
        msr cpsr, r0    /*将r0写入cpsr */
    /*设置SVC模式下的SP指针 */
        ldr sp, =0x80200000

        cpsie i //打开IRQ
        b main      /*跳转到C语言卖弄函数 */



    //未定义指令中断函数
Undefined_Handler:
    ldr r0, =Undefined_Handler
    bx r0

    //SVC中断函数
SVC_Handler:
    ldr r0, =SVC_Handler
    bx r0

    //预取中止中断函数
PreAbort_Handler:
    ldr r0, =PreAbort_Handler
    bx r0

    //数据中止中断函数
DataAbort_Handler:
    ldr r0, =DataAbort_Handler
    bx r0

    //未使用中断函数
Notused_Handler:
    ldr r0, =Notused_Handler
    bx r0

    //IRQ中断函数
IRQ_Handler:
    push {lr}					/* 保存lr地址 */
	push {r0-r3, r12}			/* 保存r0-r3，r12寄存器 */

	mrs r0, spsr				/* 读取spsr寄存器 */
	push {r0}					/* 保存spsr寄存器 */

	mrc p15, 4, r1, c15, c0, 0 /* 从CP15的C0寄存器内的值到R1寄存器中
								* 参考文档ARM Cortex-A(armV7)编程手册V4.0.pdf P49
								* Cortex-A7 Technical ReferenceManua.pdf P68 P138
								*/							
	add r1, r1, #0X2000			/* GIC基地址加0X2000，也就是GIC的CPU接口端基地址 */
	ldr r0, [r1, #0XC]			/* GIC的CPU接口端基地址加0X0C就是GICC_IAR寄存器，
								 * GICC_IAR寄存器保存这当前发生中断的中断号，我们要根据
								 * 这个中断号来绝对调用哪个中断服务函数
								 */
	push {r0, r1}				/* 保存r0,r1 */
	
	cps #0x13					/* 进入SVC模式，允许其他中断再次进去 */
	
	push {lr}					/* 保存SVC模式的lr寄存器 */
	ldr r2, =system_irqhandler	/* 加载C语言中断处理函数到r2寄存器中*/
	blx r2						/* 运行C语言中断处理函数，带有一个参数，保存在R0寄存器中 */

	pop {lr}					/* 执行完C语言中断服务函数，lr出栈 */
	cps #0x12					/* 进入IRQ模式 */
	pop {r0, r1}				
	str r0, [r1, #0X10]			/* 中断执行完成，写EOIR */

	pop {r0}						
	msr spsr_cxsf, r0			/* 恢复spsr */

	pop {r0-r3, r12}			/* r0-r3,r12出栈 */
	pop {lr}					/* lr出栈 */
	subs pc, lr, #4				/* 将lr-4赋给pc */

    //FIQ中断函数
FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0



    





    
    
