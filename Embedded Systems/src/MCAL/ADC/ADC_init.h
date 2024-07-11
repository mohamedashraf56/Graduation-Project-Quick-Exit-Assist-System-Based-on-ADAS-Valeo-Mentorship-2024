/*
 * ADC_init.h
 *
 *  Created on: Jan 26, 2024
 *      Author: asabe
 */

#ifndef MCAL_ADC_ADC_INIT_H_
#define MCAL_ADC_ADC_INIT_H_

 enum {
	ADC_12_bit,
	ADC_10_bit,
	ADC_8_bit,
	ADC_6_bit,

}ADC_RES;

 enum {
	WD_ENABLE,
	WD_DISABLE,
};

 enum {
WD_CH_1,
WD_CH_2,
WD_CH_3,
WD_CH_4,
WD_CH_5,
WD_CH_6,
WD_CH_7,
WD_CH_8,
};


 enum {
ADC_CH_0,
ADC_CH_1,
ADC_CH_2,
ADC_CH_3,
ADC_CH_4,
ADC_CH_5,
ADC_CH_6,
ADC_CH_7,
ADC_CH_8,
ADC_CH_9,
ADC_CH_10,

};
 enum {
ADC_PRE_2,
ADC_PRE_4,
ADC_PRE_6,
ADC_PRE_8,
};



 void ADC_init (void);
 void ADC_CHANIL_CONFIG(uint8 channel_num);
 void MADC_voidStartConversion (uint8 A_u8ChannelNum);
 uint32 ADC_Get_Value_Sync (uint8 channel_num);
 void  ADC_Get_Value_Async(uint8 channel_num);
 void ADC_Interrupt_CB (void(*ptr)(void));

 uint16 ADC_Get_Value ();




#endif /* MCAL_ADC_ADC_INIT_H_ */
