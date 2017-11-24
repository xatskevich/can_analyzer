
//#include "main.h"
#include "CAN.h"

void CEC_CAN_IRQHandler (void)
{
	uint8_t tmp, i;

	
	if (CAN_GetITStatus(CAN,CAN_IT_FMP0))
	{
		CAN_ClearITPendingBit(CAN, CAN_IT_FMP0);

	can_on = 1;
	//GPIOA->ODR ^= 0x400;

	CanRxMsg msg_buf;
	CAN_Receive(CAN, CAN_FIFO0, &msg_buf);
	
		for(i=0; i<16; i++) ring[ring_wr][i]=0;

		if(msg_buf.IDE){
			ring[ring_wr][0]=(unsigned char) 0xff & (msg_buf.ExtId>>24);
			ring[ring_wr][1]=(unsigned char) 0xff & (msg_buf.ExtId>>16);
			ring[ring_wr][2]=(unsigned char) 0xff & (msg_buf.ExtId>>8);
			ring[ring_wr][3]=(unsigned char) 0xff & msg_buf.ExtId;
			ring[ring_wr][4]=0;
			ring[ring_wr][5]=0;
			ring[ring_wr][6]=msg_buf.DLC;
			ring[ring_wr][7]=0;
		} else {
			ring[ring_wr][0]=(unsigned char) 0xf & (msg_buf.StdId>>8);
			ring[ring_wr][1]=(unsigned char) 0xff & msg_buf.StdId;
			ring[ring_wr][2]=0;
			ring[ring_wr][3]=0;
			ring[ring_wr][4]=0;
			ring[ring_wr][5]=0;
			ring[ring_wr][6]=msg_buf.DLC;
			ring[ring_wr][7]=0;
		}
		for(i=0; i<msg_buf.DLC; i++)
			ring[ring_wr][i+8]=msg_buf.Data[i];
		//if((ring[ring_wr][1]!=0x0)||(ring[ring_wr][2]!=0x0)) return;
		ring_wr++;
		ring_wr&=0x3f;

		GPIOA->ODR ^= 0x400;

	}
}

void Init_CAN(){

	/* CAN register init */
	CAN_DeInit(CAN);

	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = ENABLE;
	CAN_InitStructure.CAN_AWUM = ENABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

	/* CAN Baudrate = 250 kBps (CAN clocked at 24 MHz) */
	CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler = 6;
	CAN_Init(CAN, &CAN_InitStructure);
	/* Enable FIFO 0 message pending Interrupt */
	CAN_ITConfig(CAN, CAN_IT_FMP0, ENABLE);
	//CAN_ITConfig(CAN, CAN_IT_TME, ENABLE);
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);


	//вектор
	NVIC_InitStructure.NVIC_IRQChannel = CEC_CAN_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
