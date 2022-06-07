#include "bsp_led.h"

/*初始化LED*/
void led_init(void)
{

    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO04_GPIO1_IO04,0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO04_GPIO1_IO04,0x10b0);
    
    GPIO1->GDIR=0x10;
    GPIO1->DR=0x0;
}



void led_on(void)
{
    GPIO1->DR&= ~(1<<4);           /*打开LED*/

}

void led_off(void)
{
    GPIO1->DR|= (1<<4);           /*打开LED*/
}


void led_switch(int led, int status)
{
    swich(led)
    {
        case LED0:
            if(status==ON)
                led_on();
            else if(status==OFF)
                led_off();
            break;
    }
}
