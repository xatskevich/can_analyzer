
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f0xx.h"                  // Device header
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_can.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_iwdg.h"
#include "stm32f0xx_usart.h"

#include "CAN.h"
#include "GPIO.h"
#include "rcc.h"
#include "timer.h"
#include "UART.h"

#define sys_clock 24000
#define power_address 0x061


extern unsigned char ring[64][16];
extern unsigned char ring_wr, ring_rd, can_on;

extern CanTxMsg TxMessage;
extern GPIO_InitTypeDef GPIO_InitStructure;
extern NVIC_InitTypeDef NVIC_InitStructure;
extern CAN_InitTypeDef CAN_InitStructure;
extern CAN_FilterInitTypeDef CAN_FilterInitStructure;
extern USART_InitTypeDef USART_InitStructure;


#endif
