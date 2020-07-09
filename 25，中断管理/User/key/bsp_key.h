#ifndef __EXTI_H
#define	__EXTI_H

#include "stm32f4xx.h"

//Òý½Å¶¨Òå
/*******************************************************/
#define KEY1_INT_GPIO_PORT                GPIOA
#define KEY1_INT_GPIO_CLK_ENABLE()        __GPIOA_CLK_ENABLE();
#define KEY1_INT_GPIO_PIN                 GPIO_PIN_0
#define KEY1_INT_EXTI_IRQ                 EXTI0_IRQn
#define KEY1_IRQHandler                   EXTI0_IRQHandler

#define KEY2_INT_GPIO_PORT                GPIOC
#define KEY2_INT_GPIO_CLK_ENABLE()        __GPIOA_CLK_ENABLE();
#define KEY2_INT_GPIO_PIN                 GPIO_PIN_13
#define KEY2_INT_EXTI_IRQ                 EXTI15_10_IRQn
#define KEY2_IRQHandler                   EXTI15_10_IRQHandler

#define KEY3_INT_GPIO_PORT                GPIOG
#define KEY3_INT_GPIO_CLK_ENABLE()        __GPIOG_CLK_ENABLE();
#define KEY3_INT_GPIO_PIN                 GPIO_PIN_2
#define KEY3_INT_EXTI_IRQ                 EXTI2_IRQn
#define KEY3_IRQHandler                   EXTI2_IRQHandler

#define KEY4_INT_GPIO_PORT                GPIOG
#define KEY4_INT_GPIO_CLK_ENABLE()        __GPIOG_CLK_ENABLE();
#define KEY4_INT_GPIO_PIN                 GPIO_PIN_3
#define KEY4_INT_EXTI_IRQ                 EXTI3_IRQn
#define KEY4_IRQHandler                   EXTI3_IRQHandler

#define KEY5_INT_GPIO_PORT                GPIOG
#define KEY5_INT_GPIO_CLK_ENABLE()        __GPIOG_CLK_ENABLE();
#define KEY5_INT_GPIO_PIN                 GPIO_PIN_4
#define KEY5_INT_EXTI_IRQ                 EXTI4_IRQn
#define KEY5_IRQHandler                   EXTI4_IRQHandler
/*******************************************************/


void EXTI_Key_Config(void);

#endif /* __EXTI_H */
