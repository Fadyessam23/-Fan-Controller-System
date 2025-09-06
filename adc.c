/*
 * ADC.c
 *
 *  Created on: Oct 9, 2023
 *      Author: Fady Essam
 */
#include<avr/io.h>
#include<avr/interrupt.h>
#include"adc.h"
#include"common_macros.h"
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr){

	ADMUX=0;
	ADMUX=(ADMUX&0x3F) |((Config_Ptr->ref_volt)<<6);
	ADCSRA|=(1<<ADEN);
	ADCSRA=(ADCSRA&0xF8) |(Config_Ptr->prescaler);


}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07;
	ADMUX &= 0xE0;
	ADMUX = ADMUX | channel_num;
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}
