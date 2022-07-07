#include "imx6u.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_exti.h"

int main(void)
{
    int_init();
    imx6u_clkinit();
    clk_enable();
    /*初始化LED*/
    led_init();
    beep_init();
    key_init();
    exti_init();
    while(1)
    {
        led_on();
        delay(100);
        led_off();
        delay(100);          
    }
    return 0;
}