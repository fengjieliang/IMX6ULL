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
    unsigned int reg=0;
    //set imx6u system clock 528MHz
    if(((CCM->CCSR)>>2)&0x1==0) //当前时钟使用pll1_clk
    {
        CCM->CCSR &=~(1<<8);//设置step_clk=osc_clk=24M
        CCM->CCSR |=(1<<2);//pll1-sw_clk=step_clk=24MHz
    }

    //设置PLL1 =1056MHz
    CCM_ANALOG->PLL_ARM =(1<<13)|((88<<0)&0x7f);
    CCM->CACRR=1;   //设置二分频
    CCM->CCSR &=~(1<<2);    //设置pll1_sw_clk=pll1_main_clk=1056MHz


    //设置PLL2的4路PFD
    reg=CCM_ANALOG->PFD_528;
    reg &= ~(0x3F3F3F3F); //相应的位清零
    reg|=(32<<24);          //PLL2_PDF3=297MHz
    reg|=(24<<16);          //PLL2_PDF2=396MHz
    reg|=(16<<8);          //PLL2_PDF1=594MHz
    reg|=(27<<0);          //PLL2_PDF0=352MHz
    CCM_ANALOG->PFD_528=reg;


    //设置PLL3的4路PFD
    reg=0;
    reg=CCM_ANALOG->PFD_480;
    reg &= ~(0x3F3F3F3F); //相应的位清零
    reg|=(19<<24);          //PLL2_PDF3=454.7MHz
    reg|=(17<<16);          //PLL2_PDF2=508.2MHz
    reg|=(16<<8);          //PLL2_PDF1=540MHz
    reg|=(12<<0);          //PLL2_PDF0=720MHz
    CCM_ANALOG->PFD_480=reg;


    //设置AHB_CLK_ROOT=132MHz
    CCM->CBCMR&=~(3<<8);
    CCM->CBCMR|=1<<18;  //设置pre_periph_clock=PLL2_PFD2=396MHz
    CCM->CBCDR&=~(1<<25);
    while(CCM->CDHIPR&(1<<5));
 #if 0   
    CCM->CBCDR&=~(7<<10);
    CCM->CBCDR |= (2<<10);      //3分频
    while(CCM->CDHIPR&(1<<1));
#endif
    //IPG_CLK_ROOT=66MHz
    CCM->CBCDR &=~(3<<8);  //清零
    CCM->CBCDR |=~(1<<8);   //2分频

    //PER_CLK_ROOT=66MHz
    CCM->CSCMR1 &=~(1<<6);  //PER_CLK_ROOT时钟源为IPG_CLK_ROOT
    CCM->CSCMR1 &=~(0x3f<<0);


}