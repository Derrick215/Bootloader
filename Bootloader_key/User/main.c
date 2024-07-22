#include "stm32f10x.h"                  // Device header
#include "Delay.h"  
#include "LED.h" 
#include "Key.h"
#include "sys.h"

uint8_t KeyNum;

int main(void)
{
	/* ��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ) */
    __set_MSP(*(volatile uint32_t *)0x08008000);
	sys_nvic_set_vector_table(FLASH_BASE,0x8000);
	LED_Init();
	Key_Init();
	
	while (1)	
	{
		KeyNum=GetKeyNum();
		if(KeyNum==1)
		{
			LED1_TURN();
		}
		if(KeyNum==2)
		{
			LED2_TURN();
		}
	}
			
}
