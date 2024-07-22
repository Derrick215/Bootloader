#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "IAP.h"

iapfun jump2app;

/**
 * @brief       跳转到应用程序段(执行APP)
 * @param       appxaddr : 应用程序的起始地址

 * @retval      无
 */
void iap_load_app(uint32_t appxaddr)
{
	
//	/*清除所有中断标志位*/
//	for(uint8_t i = 0; i < 8; i++)
//	{
//		NVIC -> ICER[i] = 0xFFFFFFFF;
//		NVIC -> ICPR[i] = 0xFFFFFFFF;
//	}
//	
//	/*先关闭全局中断*/
//	__disable_irq();
	
	
    
    if (((*(volatile  uint32_t *)appxaddr) & 0x2FFE0000) == 0x20000000)     /* 检查栈顶地址是否合法.可以放在内部SRAM共64KB(0x20000000) */
    {
        /* 用户代码区第二个字为程序开始地址(复位地址) */
		jump2app = (iapfun) * (volatile uint32_t *)(appxaddr + 4);
        /* 初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址) */
        sys_msr_msp(*(volatile uint32_t *)appxaddr);
        /* 跳转到APP */
		jump2app();
    }
	
}
