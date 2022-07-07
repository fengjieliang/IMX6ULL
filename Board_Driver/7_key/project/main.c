#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"


int main(void)
{
    clk_enable();
    /*初始化LED*/
    led_init();
    beep_init();
    key_init();

    while(1)
    {
        if(key_getvalue()==1)
        {
            beep_on();
            led_on();
        }
        else{
            beep_off();
            led_off();
        }

        
        
        delay(100);
        
    }
    return 0;
}