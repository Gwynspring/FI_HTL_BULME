/*
 * ADU_umwandlung.c
 *
 * Created: 23.09.2024 18:09:42
 * Author : gspur
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "LCD_ATMEGA2560_Addon_Board.h"
#include "ADU_ATMEGA2560_Addon_Board.h"


#define ADU_CHANNEL_POTENTIOMETER 0
#define ADU_CHANNEL_TEMPERATURE 1



int main(void)
{
	short resultat_poti;
	short resultat_temp;
	char text[20];
	
	ADU_Init();
	LCD_Init();
	
	DDRA = 0xFF;
	
    while (1) 
    {
		resultat_poti = ADU_Read(ADU_CHANNEL_POTENTIOMETER);
		
		if(resultat_poti > 500)
		{
			PORTA = 0xFF;
		}
		else
		PORTA = 0x00;
		
		sprintf(text, "ADU = %04d", resultat_poti);
		LCD_SendText(text, 1, 1);
		
		resultat_temp = ADU_Read(ADU_CHANNEL_TEMPERATURE);
		
		sprintf(text, "ADU_Temp = %04d", resultat_temp);
		LCD_SendText(text,2,1);	
    }
}



