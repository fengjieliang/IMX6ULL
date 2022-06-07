#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"


int main(void)
{
    clk_enable();
    /*初始化LED*/
    led_init();
    beep_init();
    
    while(1)
    {
        led_on();
        beep_on();
        delay(1000);
        led_off();
        //beep_off();
        delay(1000);
    }
    return 0;
}