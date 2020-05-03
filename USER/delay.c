#include "delay.h"


static uint8_t fac_us=0;//us延时倍数

static uint16_t fac_ms=0;//ms延时倍数

void delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//选择外部时钟HCLK/8

	fac_us=SystemCoreClock/8000000; //72000000/8000000 = 9

	fac_ms=(uint16_t)fac_us*1000; //9000
}

void delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD = nus*fac_us;	//加载时间
	SysTick->VAL = 0x00; //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始计数
	do
	{
		temp = SysTick->CTRL;
	}while(temp&0x01&&!(temp&(1<<16))); //等待时间到达
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //停止计数
	SysTick->VAL = 0x00; //清空计数器
}

void delay_ms(uint16_t nms)
{
	uint32_t temp;
	SysTick->LOAD = nms*fac_ms;	//加载时间
	SysTick->VAL = 0x00; //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始计数
	do
	{
		temp = SysTick->CTRL;
	}while(temp&0x01&&!(temp&(1<<16))); //等待时间到达
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //停止计数
	SysTick->VAL = 0x00; //清空计数器
}
