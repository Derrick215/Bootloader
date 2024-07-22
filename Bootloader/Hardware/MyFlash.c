#include "stm32f10x.h"                  // Device header

//读取
uint32_t MyFlash_ReadWord(uint32_t Address)
{
	return *((__IO uint32_t*)(Address));
}

uint16_t MyFlash_ReadHalfWord(uint32_t Address)
{
	return *((__IO uint16_t*)(Address));
}

uint8_t MyFlash_ReadByte(uint32_t Address)
{
	return *((__IO uint8_t*)(Address));
}

//擦除
void MyFlash_EraseAllPage(void)
{
	FLASH_Unlock();
	FLASH_EraseAllPages();
	FLASH_Lock();
}

void MyFlash_ErasePage(uint32_t Page_Address)
{
	FLASH_Unlock();
	FLASH_ErasePage(Page_Address);
	FLASH_Lock();
}

//编程
void MyFlash_ProgramWord(uint32_t Address, uint32_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramWord(Address, Data);
	FLASH_Lock();
}

void MyFlash_ProgramHalfWord(uint32_t Address, uint32_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramHalfWord(Address, Data);
	FLASH_Lock();
}

void MyFlash_EraseAPPPage(void)
{
	for(uint8_t i = 0; i < 32; i ++)
	{
		MyFlash_ErasePage(0x08008000 + 0x400 * i);
	}
}

