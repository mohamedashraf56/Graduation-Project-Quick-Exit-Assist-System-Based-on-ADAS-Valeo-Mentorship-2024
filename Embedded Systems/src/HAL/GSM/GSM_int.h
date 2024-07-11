/*
 * GSM_int.h
 *
 *  Created on: Feb 3, 2024
 *      Author: Zahraa Mohamed
 */

#ifndef HAL_GSM_GSM_INT_H_
#define HAL_GSM_GSM_INT_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../../lip/std_types.h"

void GSM_SendAtCommand (char *AtCommand);
char GSM_FindAnswer ( char *NewData);
void  GSM_SetPower(void);
void GSM_ResetModule(void);
void  GSM_SetAPN(char *APN);
void GSM_Initialise (void);
void GSM_SetFactoryDefault (void);
void GSM_SendCall(uint32 GSM_PhoneNumber);
void GSM_EnableTextMode(void);
void GSM_SendSMS(uint32 GSM_PhoneNumber, char* GSM_Message);

#endif /* HAL_GSM_GSM_INT_H_ */
