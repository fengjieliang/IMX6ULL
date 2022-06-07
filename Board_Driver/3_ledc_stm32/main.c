#include "imx6u.h"


/*使能外设时钟*/
void clk_enable(void)
{
    CCM->CCGR0=0xffffffff;
    CCM->CCGR1=0xffffffff;
    CCM->CCGR2=0xffffffff;
    CCM->CCGR3=0xffffffff;
    CCM->CCGR4=0xffffffff;
    CCM->CCGR5=0xffffffff;
    CCM->CCGR6=0xffffffff;

    
}

/*初始化LED*/
void led_init(void)
{
    IOMUX_SW_MUX->GPIO1_IO04=5;
    IOMUX_SW_PAD->GPIO1_IO04=0x10b0;
    
    GPIO1->GDIR=0x10;
    GPIO1->DR=0x0;
}

void delay_short(volatile unsigned int n)
{
    while(n--){}
}

void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0x7ff);
    }
}

void led_on(void)
{
    GPIO1->DR&= ~(1<<4);           /*打开LED*/

}

void led_off(void)
{
    GPIO1->DR|= (1<<4);           /*打开LED*/
}

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