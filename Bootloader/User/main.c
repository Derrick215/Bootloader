#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Serial.h"
#include "IAP.h"
#include "MyFlash.h"

uint8_t KeyNum;
uint8_t RxData;

int main(void)
{
	uint32_t applenth = 0;
	uint32_t lastcount = 0;
	Key_Init();
	OLED_Init();
	Serial_Init();		
	OLED_ShowString(1, 1, "RxData:");
	OLED_ShowString(2, 1, "Bootloader!");

	Serial_Printf("Bootloader!\r\n");

	while (1)
	{
		KeyNum = Key_GetNum();
		if (Serial_RxData_CNT)
        {
            if (lastcount == Serial_RxData_CNT)   /* ��������,û���յ��κ�����,��Ϊ�������ݽ������ */
            {
                applenth = Serial_RxData_CNT;
                lastcount = 0;
                Serial_RxData_CNT = 0;
                Serial_Printf("�û�����������!\r\n");
                Serial_Printf("���볤��:%dBytes\r\n", applenth);
            }
            else
            {
                lastcount = Serial_RxData_CNT;
            }
        }
		
		switch(KeyNum)
		{
			case 1:						//B1���£���ת��app����ִ��
			{
				Serial_Printf("flash_APP addr :%x \r\n",(*(volatile uint32_t *)(FLASH_APP1_ADDR + 4)) & 0xFF00F000);
                
                if (((*(volatile uint32_t *)(FLASH_APP1_ADDR + 4)) & 0xFF000000) == 0x08000000)
                {
                    Serial_Printf("��ʼִ��FLASH�û�����!!\r\n\r\n");
                    Delay_ms(10);
                    iap_load_app(FLASH_APP1_ADDR);
                }
                else
                {
                    Serial_Printf("û�п������еĹ̼�!\r\n");
                    Serial_Printf("No APP!\r\n");
                }
				break;
			}
			case 2:							//B11���£���SRAM(0x20001000)���³���Flashָ��λ��(0x08008000)
			{
				Serial_Printf("��ʼ���¹̼�...\r\n");
				Serial_Printf("Copying APP2FLASH...\r\n");
				if (((*(volatile uint32_t *)(0x20001000 + 4)) & 0xFF000000) == 0x08000000)
				{
					iap_write_appbin(FLASH_APP1_ADDR, Serial_RxData_ARR, applenth);
					Serial_Printf("Copy APP Successed!!\r\n");
					Serial_Printf("�̼��������!\r\n");
				}
				else
				{
					Serial_Printf("Illegal FLASH APP!  \r\n");
					Serial_Printf("��FLASHӦ�ó���!\r\n");
				}
			}
		}
		Delay_ms(100);			//�����У���Ϊ��ѭ��Ƶ�ʱȴ��ڿ죬��֤lastcount���±�Serial_RxData_CNT����
	}
}
