/*
 * USART_prog.c
 *
 *  Created on: Jan 27, 2024
 *      Author  : Sabet
 *      Version : 1.00
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "../RCC/RCC_int.h"
#include "../NVIC/NVIC_int.h"
#include "../GPIO/GPIO_int_.h"
#include "USART_cfg.h"
#include "USART_init.h"
#include "USART_priv.h"



//static uint8 *RX_Buffer ;

/***********************************************************Call back functions pointers**********************************/
void (*USART1_CBFun_notifi) (void) = NULL_PTR ;
void (*USART2_CBFun_notifi) (void) = NULL_PTR ;
void (*USART6_CBFun_notifi) (void) = NULL_PTR ;
/****************************************************************************************************************************/

/* ********************************************************************
 * Name            : USART_Init
 * Description   :  Initialization for USART and set over sampling mode , data length mode , stop bit , party , and Baud rate
 * Return  		  : NOTHING
 * Argument 1	  : Config struct for USART Settings
 * Argument 2   : USART number
 * TYPE       		  : SYNC
 ***********************************************************************/

void USART_Init(USART_Confg_Struct *ptr , USART_Memap *USART )
{
	ptr->USART_States[USART_Init_State] = USART_Init_Not_Done ;
	if(USART==USART1)
	{
		RCC_Enable_Clock(RCC_APB2,RCC_USART1);
		NVIC_En_Interrupt(NVIC_USART1);
	}
	if(USART==USART2)
	{
		RCC_Enable_Clock(RCC_APB1,RCC_USART2);
		NVIC_En_Interrupt(NVIC_USART2);
	}
	if(USART==USART6)
	{
		RCC_Enable_Clock(RCC_APB1,RCC_USART6);
		NVIC_En_Interrupt(NVIC_USART6);
	}

        	GPIO_Set_Pin_Direction(ptr->USART_TX_PORT, ptr->USART_TX_PIN, GPIO_MODE_ALTFUN);
			GPIO_Set_Pin_Direction(ptr->USART_RX_PORT, ptr->USART_RX_PIN, GPIO_MODE_ALTFUN);
			GPIO_Alternate_Function(ptr->USART_TX_PORT, ptr->USART_TX_PIN, 7);    // AF_7 for USART
		 	GPIO_Alternate_Function(ptr->USART_RX_PORT, ptr->USART_RX_PIN, 7);    // AF_7 for USART


	switch(ptr->USART_OverSampling)                            // choosing the baud rate which is depending on USART_OverSampling
	{
	case OverSampling_16:
	USART->BRR =USART_BRR_SAMPLING16(_PCLK_, _BAUD_);                  // macro from STM
	break;
	case OverSampling_8:
		USART->BRR =USART_BRR_SAMPLING8(_PCLK_, _BAUD_);              // macro from STM
			break;
	}


	INSERST_BITS(USART->CR1,USART_CR1_OVER8_BIT   ,   1  ,       ptr->USART_OverSampling); // Over sampling mode
	INSERST_BITS(USART->CR1,USART_CR1_M_BIT           ,   1  ,      ptr->USART_Data_Lengh); // Data length mode
	INSERST_BITS(USART->CR1,USART_CR1_PCE_BIT        ,   1  ,      USART_Party); // Party mode
	INSERST_BITS(USART->CR1,USART_CR1_PS_BIT          ,   1  ,      USART_Party_Select); // Party select
	INSERST_BITS(USART->CR2,USART_CR2_STOP_BIT0    ,   1  ,      ptr->USART_StopBit); // stop bits
//	USART->SR = 0 ;                                                                                                                 // Clearing statues reg
	SET_BIT(USART->CR1,USART_CR1_UE_BIT);                                                    // Enabling the usart
	ptr->USART_States[USART_Init_State] = USART_Init_Done ;

}


/* ********************************************************************
 * Name            : USART_Transmiter
 * Description   :  make USART in Transmitter mode
 * Return  		  : NOTHING
 * Argument 1   : USART number
 * Argument 2   : USART_Confg_Struct
 * TYPE       		  : SYNC
 ***********************************************************************/

void USART_Transmiter ( USART_Memap *USART , USART_Confg_Struct *ptr )
{

	INSERST_BITS(USART->CR1,USART_CR1_RE_BIT  ,   2  , USART_TX  );        //insert in transmit and Receiving bits
	if (ptr->USART_States[USART_Init_State] ==USART_Init_Done)
	{
	    ptr->USART_States[USART_TX_State] = USART_TX_Ready ;
	}

}

/* ********************************************************************
 * Name            : USART_Receiver
 * Description   :  make USART in Receiver mode
 * Return  		  : NOTHING
 * Argument 1   : USART number
 * Argument 2   : USART_Confg_Struct
 * TYPE       		  : SYNC
 ***********************************************************************/

void USART_Receiver ( USART_Memap *USART , USART_Confg_Struct *ptr )
{
	INSERST_BITS(USART->CR1,USART_CR1_RE_BIT  ,   2  , USART_RX  );
	if (ptr->USART_States[USART_Init_State] == USART_Init_Done)
	{
	    ptr->USART_States[USART_RX_State] = USART_RX_Ready ;
	}

}
/* ********************************************************************
 * Name            : USART_Receiver_Transmiter
 * Description   :  make USART in Receiver and Transmitter mode
 * Return  		  : NOTHING
 * Argument 1   : USART number
 * Argument 2   : USART_Confg_Struct
 * TYPE       		  : SYNC
 ***********************************************************************/

void USART_Receiver_Transmiter ( USART_Memap *USART , USART_Confg_Struct *ptr )
{
	INSERST_BITS(USART->CR1,USART_CR1_RE_BIT  ,   2  , USART_RX_TX  );
	if (ptr->USART_States[USART_Init_State] ==USART_Init_Done)
	{
	    ptr->USART_States[USART_RX_State] = USART_RX_Ready ;
	    ptr->USART_States[USART_TX_State] = USART_TX_Ready ;
	}

}

/* ********************************************************************
 * Name            : USART_Receiver_Transmiter_Dis
 * Description   :  Disable both modes Receiver and Transmitter
 * Return  		  : NOTHING
 * Argument 1   : USART number
 * TYPE       		  : SYNC
 ***********************************************************************/
void USART_Receiver_Transmiter_Dis ( USART_Memap *USART  )
{
	INSERST_BITS(USART->CR1,USART_CR1_RE_BIT  ,   2  , USART_DIS_RXTX  );
}


/* ********************************************************************
 * Name            : USART_Transmite_Byte_sync
 * Description   : Send Byte of data by Polling
 * Return  		  : NOTHING
 * Argument 1	  : Data to send
 * Argument 2   : USART number
 * Argument 3   : USART_Confg_Struct
 * TYPE       		  : SYNC
 ***********************************************************************/

void USART_Transmite_Byte_sync (uint8 data , USART_Memap *USART , USART_Confg_Struct *ptr  )
{
	if (ptr->USART_States[USART_TX_State]== USART_TX_Ready  ||		ptr->USART_States[USART_TX_State]== USART_TX_Complete)
	{
		while(BIT_IS_CLEAR(USART->SR,USART_SR_TXE_BIT))  //if transmit reg is busy . wait
		{
			ptr->USART_States[USART_TX_State] = USART_TX_In_Prosses ;
		}
		USART->DR=data ;
		while(BIT_IS_CLEAR(USART->SR,USART_SR_TC_BIT))   //waiting until the data transmitting
		{
			ptr->USART_States[USART_TX_State] = USART_TX_In_Prosses ;
		}
		SET_BIT(USART->SR,USART_SR_TC_BIT) ; //clearing the flag
		ptr->USART_States[USART_TX_State] = USART_TX_Complete ;

	}

}

/* ********************************************************************
 * Name            : USART_Transmite_String_sync
 * Description   : Send String of data by Polling
 * Return  		  : NOTHING
 * Argument 1	  : String to send (Pointer of Char)
 * Argument 2   : USART number
 * Argument 3   : USART_Confg_Struct
 * TYPE       		  : SYNC
 ***********************************************************************/

void USART_Transmite_String_sync (uint8 *data , USART_Memap *USART , USART_Confg_Struct *ptr  )
{
	uint16 counter=0 ;
	while (data[counter] !='\0')
	{
		 USART_Transmite_Byte_sync (data[counter] ,  USART,ptr  );
		//	DELAY_Micro(800);
		 counter++;
	}
	USART_Transmite_Byte_sync ('\0',  USART , ptr );
}

/* ********************************************************************
 * Name            :  USART1_Set_CBF  ,   USART2_Set_CBF,    USART6_Set_CBF
 * Description   : Set Call back functions
 * Return  		  : NOTHING
 * Argument 1	  : Pointer to Function that will be called in USART Handler
 * TYPE       		  : SYNC
 ***********************************************************************/
void USART1_Set_CBF(void(*ptr)(void))
{
	if (USART1_CBFun_notifi==NULL_PTR)
	{
		USART1_CBFun_notifi = ptr ;
	}
}

void USART2_Set_CBF(void(*ptr)(void))
{
	if (USART2_CBFun_notifi==NULL_PTR)
	{
		USART2_CBFun_notifi = ptr ;
	}
}

void USART6_Set_CBF(void(*ptr)(void))
{
	if (USART6_CBFun_notifi==NULL_PTR)
	{
		USART6_CBFun_notifi = ptr ;
	}
}

/*********************************************************************************************************************/



/* ********************************************************************
 * Name            : USART_Receive_Byte_sync_No_Block
 * Description   : Receive Byte of data by Polling
 * Return  		  : the data that will be Received
 * Argument 1   : USART number
 * Argument 2   : USART_Confg_Struct
 * TYPE       		  : SYNC Non Blocking (After a cretin time of Polling will break)
 ***********************************************************************/

uint8 USART_Receive_Byte_sync_No_Block ( USART_Memap *USART,USART_Confg_Struct *ptr  )
{
	uint8 data=0 ;
	uint16 time=0 ;

	if (ptr->USART_States[USART_RX_State]  ==USART_RX_Ready ||		ptr->USART_States[USART_RX_State]== USART_RX_Complete)
	{
		while (BIT_IS_CLEAR(USART->SR,USART_SR_RXNE_BIT)&&(time<USART_MaxReceive_Time))
		{
			ptr->USART_States[USART_RX_State] = USART_RX_In_Prosses ;
			time++;
		}
		if (time<=USART_MaxReceive_Time)
		{
			data =USART->DR;
			CLEAR_BIT(USART->SR,USART_SR_RXNE_BIT); //clearing the flag
			ptr->USART_States[USART_RX_State] = USART_RX_Complete ;

		}
		else {
			data = 255 ; //no receiving return 255 ascii
		}
		return data ;

	}
	else {
		return 255 ; // No data
	}
}

/* ********************************************************************
 * Name            : USART_Receive_Byte_Async_Interrupt_En
 * Description   : Receive Byte of data by Interrupt
 * Return  		  : Void
 * Argument 1   : USART number
 * Argument 2   : USART_Confg_Struct
 * TYPE       		  : ASYNC
 ***********************************************************************/
void USART_Receive_Byte_Async_Interrupt_En ( USART_Memap *USART,USART_Confg_Struct *ptr  )
{
	if (ptr->USART_States[USART_RX_State]  ==USART_RX_Ready)
	{
    	ptr->USART_States[USART_RX_State] = USART_RX_In_Prosses ;
         SET_BIT(USART->CR1,USART_CR1_RXNEIE_BIT) ;
	}
}

/* ********************************************************************
 * Name            : USART_Get_Data_Reg
 * Description   : Getter function to return the data that being Received
 * Return  		  : the data that will be Received
 * Argument 1   : USART number
 * TYPE       		  : Getter
 ***********************************************************************/


uint8 USART_Get_Data_Reg ( USART_Memap *USART )
{
	 return (USART->DR) ;
}

/**************************************************************USART Handlers************************************************/

 void USART1_IRQHandler(void)
{
    USART1->SR = 0;    // clear flags
	if(USART1_CBFun_notifi != NULL_PTR)
	{
		USART1_CBFun_notifi();
	}

}
 void USART2_IRQHandler(void)
{
    USART2->SR = 0;    // clear flags
	if(USART2_CBFun_notifi != NULL_PTR)
	{
		USART2_CBFun_notifi();
	}
}
 void USART6_IRQHandler(void)
{
    USART6->SR = 0;    // clear flags
	if(USART6_CBFun_notifi != NULL_PTR)
	{
		USART6_CBFun_notifi();
	}
}
/**********************************************************************************************************************/



