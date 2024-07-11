/*
 * USART_init.h
 *
 *  Created on: Jan 27, 2024
 *      Author  : Sabet
 *      Version : 1.00
 */

#ifndef MCAL_USART_USART_INIT_H_
#define MCAL_USART_USART_INIT_H_
#include "../../lip/std_types.h"



typedef struct{
		 uint32 SR;
		 uint32 DR;
		 uint32 BRR;
		 uint32 CR1;
		 uint32 CR2;
		 uint32 CR3;
		 uint32 GTPR;
}USART_Memap;

#define 	USART1 		((USART_Memap *)0x40011000)
#define 	USART2 		((USART_Memap *)0x40004400)
#define 	USART6 		((USART_Memap *)0x40011400)


 enum {
Odd_Parity ,
Even_Parity
};

typedef enum {
DATA_Reg_8bit ,
DATA_Reg_9bit
}USART_Data_Lengh_enum;

typedef enum {
OverSampling_16 ,
OverSampling_8
}USART_OverSampling_enum;

typedef enum {
StopBit_1 ,
StopBit_Half ,
StopBit_2 ,
StopBit_1_Half ,
}USART_StopBit_enum;
 enum {
USART_DIS_RXTX ,
USART_RX ,
USART_TX ,
USART_RX_TX ,

};

 typedef enum {
     USART_Init_State,
     USART_TX_State,
     USART_RX_State,
     USART_States_num,
 } USART_States_Enum;

 typedef enum {
     USART_Init_Not_Done,
     USART_Init_Done,
     USART_TX_Ready,
     USART_TX_In_Prosses,
     USART_TX_Complete,
     USART_RX_Ready,
     USART_RX_In_Prosses,
     USART_RX_Complete,
     USART_Events_num,
 } USART_Events_Enum;

typedef struct{
	uint8 USART_TX_PIN ;
	uint8 USART_RX_PIN ;
	uint8 USART_TX_PORT ;
	uint8 USART_RX_PORT ;
	USART_Data_Lengh_enum  USART_Data_Lengh ;
	USART_OverSampling_enum  USART_OverSampling ;
	USART_StopBit_enum   USART_StopBit ;
	USART_Events_Enum USART_States [USART_States_num] ;

}USART_Confg_Struct;





void USART_Init(USART_Confg_Struct *ptr , USART_Memap *USART );
void USART_Transmiter ( USART_Memap *USART , USART_Confg_Struct *ptr );
void USART_Receiver ( USART_Memap *USART , USART_Confg_Struct *ptr );
void USART_Receiver_Transmiter ( USART_Memap *USART , USART_Confg_Struct *ptr );
void USART_Receiver_Transmiter_Dis ( USART_Memap *USART  );
void USART_Transmite_Byte_sync (uint8 data , USART_Memap *USART , USART_Confg_Struct *ptr  );
void USART_Transmite_String_sync (uint8 *data , USART_Memap *USART , USART_Confg_Struct *ptr  );
void USART1_Set_CBF(void(*ptr)(void)) ;
void USART2_Set_CBF(void(*ptr)(void)) ;
void USART6_Set_CBF(void(*ptr)(void)) ;
uint8 USART_Receive_Byte_sync_No_Block ( USART_Memap *USART,USART_Confg_Struct *ptr  );
void USART_Receive_Byte_Async_Interrupt_En ( USART_Memap *USART,USART_Confg_Struct *ptr  );
uint8 USART_Get_Data_Reg ( USART_Memap *USART ) ;





#endif /* MCAL_USART_USART_INIT_H_ */
