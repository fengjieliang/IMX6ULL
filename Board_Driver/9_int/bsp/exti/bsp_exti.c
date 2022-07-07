#include "bsp_exti.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_delay.h"
#include "bsp_beep.h"


/*
 * @description			: 初始化外部中断
 * @param				: 无
 * @return 				: 无
 */
void exti_init(void)
{
	gpio_pin_config_t key_config;

	/* 1、设置IO复用 */
	IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0x1080);

	/* 2、初始化GPIO为中断模式 */
	key_config.direction = kGPIO_DigitalInput;
	key_config.interruptMode = kGPIO_IntRisingEdge;
	key_config.outputLogic = 1;
	gpio_init(GPIO5, 1, &key_config);

	GIC_EnableIRQ(GPIO5_Combined_0_15_IRQn);				/* 使能GIC中对应的中断 */
	system_register_irqhandler(GPIO5_Combined_0_15_IRQn, (system_irq_handler_t)gpio5_io1_irqhandler, NULL);	/* 注册中断服务函数 */
	gpio_enableint(GPIO5, 1);								/* 使能GPIO1_IO18的中断功能 */
}

void gpio5_io1_irqhandler(void)
{
    static unsigned char state = 0;
    delay(10);
	if(gpio_pinread(GPIO5, 1) == 1)	/* 按键按下了  */
	{
		state = !state;
		if(state==1)
        {beep_on();}
        else
        {beep_off();}
	}
	
	gpio_clearintflags(GPIO5, 1); /* 清除中断标志位 */
}
