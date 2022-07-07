#include "bsp_key.h"
#include "bsp_delay.h"

void key_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0x1080);
    
    GPIO5->GDIR&= ~(1<<1);    //GPIO设置为output
}

int read_pin(void)
{
    int ret;
    ret=(GPIO5->DR>>1)&0x01;
    return ret;
}

int key_getvalue(void)
{
    int ret=0;
    static unsigned char release=1;

    if((release==1)&&(read_pin()==1))
    {
        delay(10);
        release=0;
        if(read_pin()==1)
        {
            ret=1;
        }
    }
    else if(read_pin()==0)
    {
        ret=0;
        release=1;
    }
    else if((release==0)&&(read_pin()==1))
    {
        delay(10);
        release=0;
        if(read_pin()==1)
        {
            ret=1;
        }
    }
    return ret;
}