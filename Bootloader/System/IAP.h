#ifndef __IAP_H
#define __IAP_H

typedef void (*iapfun)(void);                   /* ����һ���������͵Ĳ��� */

#define FLASH_APP1_ADDR         0x08008000      /* ��һ��Ӧ�ó�����ʼ��ַ(������ڲ�FLASH)
                                                 * ���� 0X08000000~0X08008FFF(36KB) �Ŀռ�Ϊ Bootloader ʹ��
                                                 */

void iap_load_app(uint32_t appxaddr);
void iap_write_appbin(uint32_t appxaddr, uint8_t *appbuf, uint32_t appsize);
	
#endif
