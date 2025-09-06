/*
 * main.c
 *
 *  Created on: Oct 15, 2023
 *      Author: Fady Essam
 */
#include <avr/io.h>
#include "gpio.h"
#include "DC_Motor.h"
#include "lm35_sensor.h"
#include "lcd.h"
#include "PWM.h"
#include "adc.h"

int main (void)
{
	uint8 temperature = 0;
	ADC_ConfigType ADC_Configurations = {Internal,FCPUBY8};
	ADC_init(&ADC_Configurations);
	DcMotor_Init();
	LCD_init();
	SREG |= (1<<7);

	while(1)
	{
		temperature = LM35_getTemperature();
		if (temperature < 30)
		{
			DcMotor_Rotate(STOP,0);
			LCD_displayStringRowColumn(0,2,"THE FAN IS OFF");
			LCD_displayStringRowColumn(1,2,"TEMP = ");
			LCD_intgerToString(temperature);
			LCD_displayString(" C ");
		}
		else if ((temperature >= 30) && (temperature < 60))
		{
			DcMotor_Rotate(CW,25);
			LCD_displayStringRowColumn(0,2,"THE FAN IS ON ");
			LCD_displayStringRowColumn(1,2,"TEMP = ");
			LCD_intgerToString(temperature);
			LCD_displayString(" C ");

		}
		else if ((temperature >= 60) && (temperature < 90))
		{
			DcMotor_Rotate(CW,50);
			LCD_displayStringRowColumn(0,2,"THE FAN IS ON ");
			LCD_displayStringRowColumn(1,2,"TEMP = ");
			LCD_intgerToString(temperature);
			LCD_displayString(" C ");

		}
		else if ((temperature >= 90) && (temperature < 120))
		{
			DcMotor_Rotate(CW,75);
			LCD_displayStringRowColumn(0,2,"THE FAN IS ON ");
			LCD_displayStringRowColumn(1,2,"TEMP = ");
			LCD_intgerToString(temperature);
			LCD_displayString(" C ");

		}
		else if (temperature >= 120)
		{
			DcMotor_Rotate(CW,100);
			LCD_displayStringRowColumn(0,2,"THE FAN IS ON ");
			LCD_displayStringRowColumn(1,2,"TEMP = ");
			LCD_intgerToString(temperature);
			LCD_displayString(" C ");
		}

  }
}

