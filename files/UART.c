
#include "main.h"

void Init_uart(){

	USART_StructInit(&USART_InitStructure);

	USART_InitStructure.USART_BaudRate = 250000;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	USART_Cmd(USART2, ENABLE);
}
