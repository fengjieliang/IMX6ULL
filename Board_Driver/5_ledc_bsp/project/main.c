#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"



int main(void)
{
    clk_enable();
    /*初始化LED*/
    led_init();
    while(1)
    {
        led_on();
        delay(1000);
        led_off();
        delay(1000);
    }
    return 0;
}