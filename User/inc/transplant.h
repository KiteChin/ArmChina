#ifndef __TRANSPLANT_H
#define __TRANSPLANT_H

#include "stm32f4xx.h"

/*---------------------GPIO-----------------------*/
#define GPIO1_PIN                  GPIO_Pin_6                 
#define GPIO1_GPIO_PORT            GPIOF                      
#define GPIO1_GPIO_CLK             RCC_AHB1Periph_GPIOF

#define GPIO2_PIN                  GPIO_Pin_7                 
#define GPIO2_GPIO_PORT            GPIOF                      
#define GPIO2_GPIO_CLK             RCC_AHB1Periph_GPIOF

#define GPIO3_PIN                  GPIO_Pin_8                 
#define GPIO3_GPIO_PORT            GPIOF                       
#define GPIO3_GPIO_CLK             RCC_AHB1Periph_GPIOF

#define GPIO4_PIN                  GPIO_Pin_1                 
#define GPIO4_GPIO_PORT            GPIOC                      
#define GPIO4_GPIO_CLK             RCC_AHB1Periph_GPIOC

#define GPIO5_PIN                  GPIO_Pin_2                 
#define GPIO5_GPIO_PORT            GPIOC                       
#define GPIO5_GPIO_CLK             RCC_AHB1Periph_GPIOC

#define GPIO1(a)	if (a)	\
					GPIO_SetBits(GPIO1_GPIO_PORT,GPIO1_PIN);\
					else		\
					GPIO_ResetBits(GPIO1_GPIO_PORT,GPIO1_PIN)
#define GPIO2(a)	if (a)	\
					GPIO_SetBits(GPIO2_GPIO_PORT,GPIO2_PIN);\
					else		\
					GPIO_ResetBits(GPIO2_GPIO_PORT,GPIO2_PIN)
#define GPIO3(a)	if (a)	\
					GPIO_SetBits(GPIO3_GPIO_PORT,GPIO3_PIN);\
					else		\
					GPIO_ResetBits(GPIO3_GPIO_PORT,GPIO3_PIN)
#define GPIO4(a)	if (a)	\
					GPIO_SetBits(GPIO4_GPIO_PORT,GPIO4_PIN);\
					else		\
					GPIO_ResetBits(GPIO4_GPIO_PORT,GPIO4_PIN)
#define GPIO5(a)	if (a)	\
					GPIO_SetBits(GPIO5_GPIO_PORT,GPIO5_PIN);\
					else		\
					GPIO_ResetBits(GPIO5_GPIO_PORT,GPIO5_PIN)
#define GPIO5_READ() GPIO_ReadInputDataBit(GPIO5_GPIO_PORT, GPIO5_PIN)
				
/*---------------------TIMER-----------------------*/
void Delay_us(__IO u32 nTime);
#define Delay_ms(x) Delay_us(100*x)	 //µ¥Î»ms
							

void Transplant_Init(void);				

#endif
