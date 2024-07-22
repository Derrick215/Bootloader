#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "IAP.h"
#include "MyFlash.h"
#include "Serial.h"

iapfun jump2app;


/**
 * @brief       IAPд��APP BIN
 * @param       appxaddr : Ӧ�ó������ʼ��ַ
 * @param       appbuf   : Ӧ�ó���CODE
 * @param       appsize  : Ӧ�ó����С(�ֽ�)
 * @retval      ��
 */
void iap_write_appbin(uint32_t appxaddr, uint8_t *appbuf, uint32_t appsize)
{
	uint16_t temp;
	uint8_t *dfu = appbuf;
	uint32_t fwaddr = appxaddr; /* ��ǰд��ĵ�ַ */
	
	MyFlash_EraseAPPPage();							//flash_app�洢�β���
	for(uint32_t i = 0; i < appsize; i += 2)		//ÿ�����ֽ�д��
	{
		temp = (uint16_t)dfu[1] << 8;
        temp |= (uint16_t)dfu[0];
		dfu += 2;               /* ƫ��2���ֽ� */
		MyFlash_ProgramHalfWord(fwaddr, temp);
		fwaddr+= 2;
	}
	if(appsize%2 != 0)
	{
		dfu -= 1;
		temp = (uint16_t)dfu[1] << 8;
        temp |= (uint16_t)dfu[0];
		MyFlash_ProgramHalfWord((fwaddr - 1), temp);
	}
}

/**
 * @brief       ��ת��Ӧ�ó����(ִ��APP)
 * @param       appxaddr : Ӧ�ó������ʼ��ַ

 * @retval      ��
 */
void iap_load_app(uint32_t appxaddr)
{
    if (((*(volatile  uint32_t *)appxaddr) & 0x2FFE0000) == 0x20000000)     /* ���ջ����ַ�Ƿ�Ϸ�.���Է����ڲ�SRAM��64KB(0x20000000) */
    {
        /* �û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ) */
		jump2app = (iapfun) * (volatile uint32_t *)(appxaddr + 4);
//        /* ��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ) */
//        sys_msr_msp(*(volatile uint32_t *)appxaddr);
        /* ��ת��APP */
		jump2app();
    }
	
}
