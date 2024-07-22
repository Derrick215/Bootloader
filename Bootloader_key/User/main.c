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
	sys_nvic_set_vector_table(FLASH_BASE,0x08000);
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
