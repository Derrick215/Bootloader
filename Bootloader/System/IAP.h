#ifndef __IAP_H
#define __IAP_H

typedef void (*iapfun)(void);                   /* 定义一个函数类型的参数 */

#define FLASH_APP1_ADDR         0x08008000      /* 第一个应用程序起始地址(存放在内部FLASH)
                                                 * 保留 0X08000000~0X08008FFF(36KB) 的空间为 Bootloader 使用
                                                 */

void iap_load_app(uint32_t appxaddr);

#endif
