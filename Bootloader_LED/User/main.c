#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Serial.h"
#include "sys.h"

uint8_t KeyNum;

int main(void)
{
	/* 初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址) */
    __set_MSP(*(volatile uint32_t *)0x08008000);
	sys_nvic_set_vector_table(FLASH_BASE,0x8000);
	LED_Init();
	Key_Init();
	OLED_Init();
	Serial_Init();
//	OLED_ShowString(1, 1, "Key:");
	while (1)
	{
//		KeyNum = Key_GetNum();
//		if (KeyNum == 1)
//		{
//			LED1_Turn();
//			OLED_ShowNum(1, 5, KeyNum, 1);
//			Serial_Printf("LED1_ON!\n");
//		}
//		if (KeyNum == 2)
//		{
//			LED2_Turn();
//			OLED_ShowNum(1, 5, KeyNum, 1);
//			Serial_Printf("LED2_ON!\n");
//		}
		LED2_Turn();
		Delay_ms(200);
	}
}
