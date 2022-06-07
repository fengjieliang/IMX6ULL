#include "main.h"


/*使能外设时钟*/
void clk_enable(void)
{
    CCM_CCGR0=0xffffffff;
    CCM_CCGR1=0xffffffff;
    CCM_CCGR2=0xffffffff;
    CCM_CCGR3=0xffffffff;
    CCM_CCGR4=0xffffffff;
    CCM_CCGR5=0xffffffff;
    CCM_CCGR6=0xffffffff;
}

/*初始化LED*/
void led_init(void)
{
    SW_MUX_GPIO1_IO04=5; /*服用为GPIO*/
    SW_PAD_GPIO1_IO04=0x10b0;

    GPIO1_GDIR=0x10;        /*设置为输出*/
    GPIO1_DR=0x0;           /*打开LED*/

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
     GPIO1_DR &= ~(1<<4);           /*打开LED*/
}

void led_off(void)
{
     GPIO1_DR |= (1<<4);           /*打开LED*/
}

int main(void)
{
    clk_enable();
    /*初始化LED*/
    led_init();
    while(1)
    {
        led_on();
        delay(100);
        led_off();
        delay(100);
    }
    return 0;
}