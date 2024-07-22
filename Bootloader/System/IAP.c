#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "IAP.h"

iapfun jump2app;

/**
 * @brief       ��ת��Ӧ�ó����(ִ��APP)
 * @param       appxaddr : Ӧ�ó������ʼ��ַ

 * @retval      ��
 */
void iap_load_app(uint32_t appxaddr)
{
	
//	/*��������жϱ�־λ*/
//	for(uint8_t i = 0; i < 8; i++)
//	{
//		NVIC -> ICER[i] = 0xFFFFFFFF;
//		NVIC -> ICPR[i] = 0xFFFFFFFF;
//	}
//	
//	/*�ȹر�ȫ���ж�*/
//	__disable_irq();
	
	
    
    if (((*(volatile  uint32_t *)appxaddr) & 0x2FFE0000) == 0x20000000)     /* ���ջ����ַ�Ƿ�Ϸ�.���Է����ڲ�SRAM��64KB(0x20000000) */
    {
        /* �û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ) */
		jump2app = (iapfun) * (volatile uint32_t *)(appxaddr + 4);
        /* ��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ) */
        sys_msr_msp(*(volatile uint32_t *)appxaddr);
        /* ��ת��APP */
		jump2app();
    }
	
}
