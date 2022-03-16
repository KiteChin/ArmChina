#include "basic_tim.h"
#include "touch.h"

static u32 TIM6_MS_CNT = 0;
static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQn; 	
		// 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// 开启TIMx_CLK,x[6,7] 
  RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE); 

  TIM_TimeBaseStructure.TIM_Period = 10-1;       
	
	//定时器时钟源TIMxCLK = 2 * PCLK1  
  //				PCLK1 = HCLK / 4 
  //				=> TIMxCLK=HCLK/2=SystemCoreClock/2=84MHz
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=10000Hz
  TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;	
	
	// 初始化定时器TIMx, x[2,3,4,5]
	TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
	
	
	// 清除定时器更新中断标志位
	TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
	
	// 开启定时器更新中断
	TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
	
	// 使能定时器
	TIM_Cmd(BASIC_TIM, ENABLE);	
}

void TIMx_Configuration(void)
{
	TIMx_NVIC_Configuration();	
  
  TIM_Mode_Config();
}

void TIM6_DAC_IRQHandler(void)
{
  if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) 
	{	
		TIM6_MS_CNT++;
		tp_dev.scan(0);
		TIM_ClearITPendingBit(BASIC_TIM , TIM_IT_Update);  		 
	}		 	
}

u32 TIM6_MS_GET(void)
{
	return TIM6_MS_CNT;
}
