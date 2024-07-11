/*
 * GSM_prg.c
 *
 *  Created on: Feb 3, 2024
 *      Author: Zahraa Mohamed
 */

#include "GSM_cfg.h"
#include "GSM_int.h"

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "../../MCAL/GPIO/GPIO_int_.h"
#include "../../MCAL/USART/USART_init.h"
#include "../../MCAL/USART/USART_priv.h"

uint8    SendATCommand[400];
uint8    ReceiveAnswer[400];
uint8 	 Temp[25];

USART_Confg_Struct GSM_ptr = {GSM_TX_PIN,GSM_RX_PIN,GSM_TX_PORT,GSM_RX_PORT,
			DATA_Reg_8bit,OverSampling_8,StopBit_1,{0}};

/* ********************************************************************
 * Name            : GSM_SendAtCommand
 * Description   : Send commands to GSM
 * Return  		  : Nothing
 * Argument     : The AT Command
 ***********************************************************************/
void GSM_SendAtCommand (char *AtCommand)
{
	memset(SendATCommand,0,sizeof(SendATCommand));
	memset(ReceiveAnswer,0,sizeof(ReceiveAnswer));
	strcpy((char *)SendATCommand, AtCommand);
	USART_Transmite_String_sync((uint8 *)SendATCommand,GSM_USART_NUMBER,&GSM_ptr);
	USART_Receive_Byte_sync_No_Block ( GSM_USART_NUMBER,&GSM_ptr );
}

/* ********************************************************************
 * Name          : GSM_FindAnswer
 * Description   : Checks the GSM response after sending any command
 * Return  		 : 1 (if the answer is found) / 0 (if the answer is not found)
 * Argument      : OK / ERROR
 ***********************************************************************/

char GSM_FindAnswer ( char * NewData)
{
	uint8 *ret;
	// find a sub string within another string
  ret = strstr((char *)ReceiveAnswer, NewData);
	if(ret)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* ********************************************************************
 * Name          : GSM_SetPower
 * Description   : Checks if the communication with the device is established
 * Return  		 : Nothing
 * Argument      : Nothing
 ***********************************************************************/
void  GSM_SetPower(void)
{
	uint8    Try = 0;
	/*
	 *  AT\n\r is a test command. When you send this command to the GSM module,
	 *	it's expecting to receive an "OK" response if it's operational
	 */
	GSM_SendAtCommand("AT\n\r");

	if(GSM_FindAnswer ("ERROR"))
	{
		while(Try < 3)
		{
			GSM_SendAtCommand("AT\n\r");
			if(GSM_FindAnswer ("OK"))
			{
				Try = 0;
				break;
			}
			Try++;
		}
		if(Try == 2)
		{
			GSM_ResetModule();
			GSM_SetPower();
			Try = 0;
		}
	}
}

/* ********************************************************************
 * Name          : GSM_ResetModule
 * Description   : Reset The GSM module
 * Return  		 : Nothing
 * Argument      : Nothing
 ***********************************************************************/
void GSM_ResetModule(void)
{
	GPIO_Set_Pin_Value(GSM_POWER_KEY_GPIO,GSM_POWER_KEY_PIN,0);
	HAL_Delay(1500);
	GPIO_Set_Pin_Value(GSM_POWER_KEY_GPIO,GSM_POWER_KEY_PIN,1);
	HAL_Delay(5000);
}

/* ********************************************************************
 * Name            : GSM_SetAPN
 * Description     : Configure the APN settings for establishing a proper data connection
 * Return  		   : Nothing
 * Argument        : The APN of the mobile carrier used (ex: internet.vodafone.net)
 ***********************************************************************/
void  GSM_SetAPN(char *APN)
{
	uint8 Temp[200];
	uint8 Flag=0;
	uint8 Try=0;

	strcpy((char *)Temp,"AT+SAPBR=3,1,\"APN\",\"");
	strcat((char *)Temp, APN);
	strcat((char *)Temp, "\"\n\r");
	GSM_SendAtCommand((char *)Temp);
	if(GSM_FindAnswer ("OK"))
	{
		Flag = 1;
	}
	if((GSM_FindAnswer ("ERROR")) && Flag == 0)
	{
		while(Try < 3)
		{
			GSM_SetAPN(APN);
			Try++;
		}
		if(Try == 2)
		{
			GSM_ResetModule();
			GSM_SetPower();
			Try = 0;
		}
	}
	memset(Temp,0,sizeof(Temp));
}

/* ********************************************************************
 * Name          : GSM_Initialise
 * Description   : Initializing the GSM & establishing a data connection for GPRS communication.
 * Return  		 : Nothing
 * Argument      : Nothing
 ***********************************************************************/
void GSM_Initialise (void)
{
	USART_Init(&GSM_ptr,USART1);
	USART_Receiver_Transmiter ( USART1 , &GSM_ptr );

	uint8 Try_GSM = 0;

	GSM_SendAtCommand("AT+SAPBR =1,1\n\r");
	if(GSM_FindAnswer ("ERROR"))
	{
		while(Try_GSM < 3)
		{
			GSM_SendAtCommand("AT+SAPBR =1,1\n\r");
			if(GSM_FindAnswer ("OK"))
			{
				Try_GSM = 0;
				break;
			}
			Try_GSM++;
		}
		if(Try_GSM == 2)
		{
			GSM_ResetModule();
			GSM_SetPower();
			Try_GSM = 0;
		}
	}
}
/* ********************************************************************
 * Name          : SetFactoryDefault
 * Description   : Restore the configuration settings to its factory defaults
 * Return  		 : Nothing
 * Argument      : Nothing
 ***********************************************************************/

void GSM_SetFactoryDefault (void)
{
	uint8    Try = 0;

	GSM_SendAtCommand("AT&F0\r\n");
	if(GSM_FindAnswer ("ERROR"))
	{
		while(Try < 3)
		{
			GSM_SendAtCommand("AT&F0\r\n");
			if(GSM_FindAnswer ("OK"))
			{
				Try = 0;
				break;
			}
			Try++;
		}
		if(Try == 2)
		{
			GSM_ResetModule();
			GSM_SetPower();
			Try = 0;
		}
	}
}
/* ********************************************************************
 * Name          : GSM_SendCall
 * Description   : Send a call to a specific number
 * Return  		 : Nothing
 * Argument      : The phone number
 ***********************************************************************/
void GSM_SendCall(uint32 GSM_PhoneNumber)
{
	uint8 Try = 0;
	uint8 Flag=0;
	uint8 Temp[200];
	strcpy((char *)Temp,"ATD");
	strcat((char *)Temp, GSM_PhoneNumber);
	strcat((char *)Temp, "\;\n\r");
	GSM_SendAtCommand((char *)Temp);
		if(GSM_FindAnswer ("OK"))
		{
			Flag = 1;
		}
		if((GSM_FindAnswer ("ERROR")) && Flag == 0)
		{
			while(Try < 3)
			{
				GSM_SendCall(GSM_PhoneNumber);
				Try++;
			}
			if(Try == 2)
			{
				GSM_ResetModule();
				GSM_SetPower();
				Try = 0;
			}
		}
		memset(Temp,0,sizeof(Temp));
}

/* ********************************************************************
 * Name          : GSM_EnableTextMode
 * Description   : Enable the text mode to interact with SMS messages using human-readable text
 * Return  		 : Nothing
 * Argument      : Nothing
 ***********************************************************************/
void GSM_EnableTextMode(void)
{
	uint8 Try = 0;
	uint8 Flag=0;
	GSM_SendAtCommand("AT+CMGF=1\n\r");
	if(GSM_FindAnswer ("OK"))
		{
			Flag = 1;
		}
		if((GSM_FindAnswer ("ERROR")) && Flag == 0)
		{
			while(Try < 3)
			{
				GSM_EnableTextMode();
				Try++;
			}
			if(Try == 2)
			{
				GSM_ResetModule();
				GSM_SetPower();
				Try = 0;
			}
		}
}
/* ********************************************************************
 * Name          : GSM_SendSMS
 * Description   : Send an SMS to a specific number
 * Return  		 : Nothing
 * Argument1     : The phone number
 * Argument2     : The message text
 ***********************************************************************/
void GSM_SendSMS(uint32 GSM_PhoneNumber, char* GSM_Message)
{
	uint8 Try1 = 0,Flag1=0,Try2=0,Flag2=0;
	uint8 Temp1[200];
	uint8 Temp2[200];
	GSM_EnableTextMode();
	strcpy((char *)Temp1,"AT+CMGS=\"");
	strcat((char *)Temp1, GSM_PhoneNumber);
	strcat((char *)Temp1, "\"\n\r");
	GSM_SendAtCommand((char *)Temp1);
	if(GSM_FindAnswer ("OK"))
		{
			Flag1 = 1;
			strcpy((char *)Temp2,GSM_Message);
			strcat((char *)Temp2, "\x1A\n\r");
			GSM_SendAtCommand((char *)Temp2);
			if(GSM_FindAnswer ("OK"))
				{
					Flag2 = 1;
				}
				if((GSM_FindAnswer ("ERROR")) && Flag2 == 0)
				{
					while(Try2 < 3)
					{
						GSM_SendAtCommand((char *)Temp2);
						Try2++;
					}
					if(Try2 == 2)
					{
						GSM_ResetModule();
						GSM_SetPower();
						Try2 = 0;
					}
				}
		}
		if((GSM_FindAnswer ("ERROR")) && Flag1 == 0)
		{
			while(Try1 < 3)
			{
				GSM_SendAtCommand((char *)Temp1);
				Try1++;
			}
			if(Try1 == 2)
			{
				GSM_ResetModule();
				GSM_SetPower();
				Try1 = 0;
			}
		}
}
