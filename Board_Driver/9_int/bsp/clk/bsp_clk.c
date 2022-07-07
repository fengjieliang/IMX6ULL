#include "bsp_clk.h"

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

void imx6u_clkinit(void)
{
    //set imx6u system clock 528MHz
    if((((CCM->CCSR)>>2) & (0x1))==0) //当前时钟使用pll1_clk
    {
        CCM->CCSR &=~(1<<8);//设置step_clk=osc_clk=24M
        CCM->CCSR |=(1<<2);//pll1-sw_clk=step_clk=24MHz
    }

    //设置PLL1 =1056MHz
    CCM_ANALOG->PLL_ARM =(1<<13)|((88<<0)&0x7f);
    CCM->CACRR=1;   //设置二分频
    CCM->CCSR &=~(1<<2);    //设置pll1_sw_clk=pll1_main_clk=1056MHz

}