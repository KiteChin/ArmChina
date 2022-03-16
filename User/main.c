#include "stm32f4xx.h"
#include "MSi001.h"
#include "delay.h"

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "GBK_LibDrive.h"	
#include "touch.h"
#include "w25qxx.h"

//#include "lv_conf.h"
#include "lvgl.h"
#include "lv_port_indev.h"
#include "lv_port_disp.h"
#include "basic_tim.h"
#include "lv_demos.h"


int main(void)
{
//	Transplant_Init();
//	MSI_Init();
//	MSI_ChageChannel(88.1);
	delay_init(168);
	LCD_Init();
	W25QXX_Init();
	POINT_COLOR=RED;      //画笔颜色：红色
	GBK_Lib_Init();       //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
	DrawFont_GBK24B(70,24,BLUE," ");
	TIMx_Configuration();
	
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
	
	
//	lv_obj_t * parent = lv_obj_create(lv_scr_act());   /*Create a parent object on the current screen*/
//	lv_obj_set_size(parent, 200, 200);	                 /*Set the size of the parent*/

//	lv_obj_t * obj1 = lv_obj_create(parent);	         /*Create an object on the previously created parent object*/
//	delay_ms(1000);
//	lv_obj_set_pos(obj1, 10, 10);	   
//	delay_ms(1000);
//	lv_obj_set_pos(parent, 10, 10);
//	lv_obj_set_x(obj1, -30);

	lv_demo_widgets();
//	lv_demo_keypad_encoder();
//	lv_demo_music();
	while(1)
	{
		
		lv_timer_handler_run_in_period(5);
	}

}

