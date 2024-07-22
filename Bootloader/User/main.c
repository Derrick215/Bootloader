#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Serial.h"
#include "IAP.h"

uint8_t KeyNum;
uint8_t RxData;

int main(void)
{
	Key_Init();
	OLED_Init();
	Serial_Init();		
	OLED_ShowString(1, 1, "RxData:");
	OLED_ShowString(2, 1, "Bootloader!");

	Serial_Printf("Bootloader!\r\n");

	while (1)
	{
//		if (Serial_GetRxFlag() == 1)
//		{
//			RxData = Serial_GetRxData();
//			Serial_SendByte(RxData);
//			OLED_ShowHexNum(1, 8, RxData, 2);
//		}
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			Serial_Printf("IAP_Load_APP!\r\n");
			Delay_ms(10);
			iap_load_app(0x08008000);
		}
		
	}
}
