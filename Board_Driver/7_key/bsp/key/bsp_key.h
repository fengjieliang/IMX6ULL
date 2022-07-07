#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"


void key_init(void);
int read_pin(void);
int key_getvalue(void);




#endif
