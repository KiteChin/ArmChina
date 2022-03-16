#ifndef __QN8027__H
#define __QN8027__H

#include "stm32f4xx.h"
#include "transplant.h"

#define QN8027_SCL(a) GPIO4(a)
#define QN8027_SDA(a) GPIO5(a)
#define QN8027_SDA_READ() GPIO5_READ() 

void QN8027_Init(void);
#endif 
