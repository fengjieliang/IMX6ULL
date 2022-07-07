#ifndef _BSP_EXTI_H
#define _BSP_EXTI_H

#include "imx6u.h"



/* 函数声明 */
void exti_init(void);						/* 中断初始化 */
void gpio5_io1_irqhandler(void); 			/* 中断处理函数 */

#endif