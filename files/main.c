
#include "main.h"

uint8_t ring[64][16];
uint8_t ring_wr, ring_rd, can_on;


CanTxMsg TxMessage;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
CAN_InitTypeDef CAN_InitStructure;
CAN_FilterInitTypeDef CAN_FilterInitStructure;
USART_InitTypeDef USART_InitStructure;


int main(void)
{
	uint8_t n;
//	uint32_t temp;
	uint8_t tmp;
	
	Init_IWDG();			//



	Init_RCC();			//тактирование
	Init_GPIO();		//порты
	Init_Timer();		//таймеры
	Init_uart();		//UART
	Init_CAN();			//CAN
	
	
	//GPIO_SetBits(GPIOA, GPIO_Pin_15);


    while(1)
    {
		if(ring_rd != ring_wr){

			for(n=0; n<16; n++){
				while(USART_GetFlagStatus(USART2, USART_FLAG_TXE)==RESET);
				USART_SendData(USART2, ring[ring_rd][n]);

			}
			ring_rd++;
			ring_rd&=0x3f;

		}//*/

    }
}
