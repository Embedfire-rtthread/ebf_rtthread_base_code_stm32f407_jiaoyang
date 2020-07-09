/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./bsp_key.h"


 /**
  * @brief  配置 PA0 为线中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void EXTI_Key_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 

    /*开启按键GPIO口的时钟*/
    KEY1_INT_GPIO_CLK_ENABLE();
    KEY2_INT_GPIO_CLK_ENABLE();
    KEY3_INT_GPIO_CLK_ENABLE();
    KEY4_INT_GPIO_CLK_ENABLE();
    KEY5_INT_GPIO_CLK_ENABLE();

    /* 选择按键1的引脚 */ 
    GPIO_InitStructure.Pin = KEY1_INT_GPIO_PIN;
    /* 设置引脚为输入模式 */ 
    GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;	    		
    /* 设置引脚不上拉也不下拉 */
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    /* 使用上面的结构体初始化按键 */
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure); 
    /* 配置 EXTI 中断源 到key1 引脚、配置中断优先级*/
    HAL_NVIC_SetPriority(KEY1_INT_EXTI_IRQ, 6, 0);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(KEY1_INT_EXTI_IRQ);

    /* 选择按键2的引脚 */ 
    GPIO_InitStructure.Pin = KEY2_INT_GPIO_PIN;  
    /* 其他配置与上面相同 */
    HAL_GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);      
    /* 配置 EXTI 中断源 到key2 引脚、配置中断优先级*/
    HAL_NVIC_SetPriority(KEY2_INT_EXTI_IRQ, 6, 0);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(KEY2_INT_EXTI_IRQ);
	
    /* 选择按键3的引脚 */ 
    GPIO_InitStructure.Pin = KEY3_INT_GPIO_PIN;  
    /* 其他配置与上面相同 */
    HAL_GPIO_Init(KEY3_INT_GPIO_PORT, &GPIO_InitStructure);      
    /* 配置 EXTI 中断源 到key3 引脚、配置中断优先级*/
    HAL_NVIC_SetPriority(KEY3_INT_EXTI_IRQ, 6, 0);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(KEY3_INT_EXTI_IRQ);
	
    /* 选择按键4的引脚 */ 
    GPIO_InitStructure.Pin = KEY4_INT_GPIO_PIN;  
    /* 其他配置与上面相同 */
    HAL_GPIO_Init(KEY4_INT_GPIO_PORT, &GPIO_InitStructure);      
    /* 配置 EXTI 中断源 到key4 引脚、配置中断优先级*/
    HAL_NVIC_SetPriority(KEY4_INT_EXTI_IRQ, 6, 0);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(KEY4_INT_EXTI_IRQ);
	
    /* 选择按键5的引脚 */ 
    GPIO_InitStructure.Pin = KEY5_INT_GPIO_PIN;  
    /* 其他配置与上面相同 */
    HAL_GPIO_Init(KEY5_INT_GPIO_PORT, &GPIO_InitStructure);      
    /* 配置 EXTI 中断源 到key5 引脚、配置中断优先级*/
    HAL_NVIC_SetPriority(KEY5_INT_EXTI_IRQ, 6, 0);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(KEY5_INT_EXTI_IRQ);
}
/*********************************************END OF FILE**********************/
