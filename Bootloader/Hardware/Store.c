#include "stm32f10x.h"                  // Device header
#include "MyFlash.h"                  


uint16_t Store_Data[512] = {0};

void Store_Init(void)
{
    if(MyFlash_ReadHalfWord(0x0800FC00) != 0xA5A5)            //如果未向flash最后一页写入数据，初始化，并设置标志位
    {
        MyFlash_ErasePage(0x0800FC00);
        MyFlash_ProgramHalfWord(0x0800FC00, 0xA5A5);          //设置标志位
        for(uint16_t i = 1; i < 512; i ++)                    //其他位全写0
        {
            MyFlash_ProgramHalfWord(0x0800FC00 + i *2, 0x0000);
        }
    }

    for(uint16_t i = 0; i < 512; i ++)          //如已经向最后一页写入数据，则加载数据到缓存数组
    {
        Store_Data[i] = MyFlash_ReadHalfWord(0x0800FC00 + i * 2);
    }
}

void Store_Save(void)
{
    MyFlash_ErasePage(0x0800FC00);
    for(uint16_t i = 0; i < 512; i ++)          //保存缓存数组到最后一页
    {
        MyFlash_ProgramHalfWord(0x0800FC00 + i *2, Store_Data[i]);
    }
}

void Store_Clear(void)
{
    for(uint16_t i = 1; i < 512; i ++)          //缓存数组除标志位外清零
    {
        Store_Data[i] = 0x00;
    }
    Store_Save();
}
