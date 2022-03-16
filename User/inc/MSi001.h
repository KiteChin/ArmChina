#ifndef __MSI001_H
#define __MSI001_H

#include "stm32f4xx.h"
#include "transplant.h"

#define MSI001_Reg0     0x0
#define MSI001_Reg1     0x1
#define MSI001_Reg2     0x2
#define MSI001_Reg3     0x3
#define MSI001_Reg4     0x4
#define MSI001_Reg5     0x5
#define MSI001_Reg6     0x6

#define MSI_REFERENCE_FRE 	24
#define MSI_THRESH		3000
#define LOdiv		32

//GPIOx(a) from transplant.h
#define MSI001_EN(a) GPIO1(a)
#define MSI001_CLK(a) GPIO2(a)
#define MSI001_DATA(a) GPIO3(a)

void MSI_Init(void);

/**
 * @brief 
 * 
 * @param data 
 * @param addr 
 */
void MSI_Write(u32 data, u8 addr);
/**
 * @brief 
 * 
 * @param FRF 
 */
void MSI_ChangeChannel(double FRF);
#endif
