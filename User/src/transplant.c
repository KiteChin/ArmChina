#include "transplant.h"
#include "delay.h"

static void Tran_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(GPIO1_GPIO_CLK |
                            GPIO2_GPIO_CLK |
                            GPIO3_GPIO_CLK,
                            ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIO1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO2_PIN;
    GPIO_Init(GPIO2_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO3_PIN;
    GPIO_Init(GPIO3_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO4_PIN;
    GPIO_Init(GPIO4_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO5_PIN;
    GPIO_Init(GPIO5_GPIO_PORT, &GPIO_InitStructure);

}

/*--------------------timer------------------------*/
static __IO u32 TimingDelay;
 

static void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock / 100000))
	{ 
		/* Capture error */ 
		while (1);
	}
}


void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	while(TimingDelay != 0);
}


static void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}


void Transplant_Init(void)
{
	delay_init(168);
	SysTick_Init();
	Tran_GPIO_Init();
}

