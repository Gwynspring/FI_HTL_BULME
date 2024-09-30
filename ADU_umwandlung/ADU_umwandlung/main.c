/*
 * ADU_umwandlung.c
 *
 * Created: 23.09.2024 18:09:42
 * Author : gspur
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "BitMaskenFunktionen.h"
#include "LCD_ATMEGA2560_Addon_Board.h"

int main(void)
{
	short resultat;
	char text[20];
	//ADU Kanal 0
	//ADMUX 0100 0000
	ADMUX = 0x40;
	
	//ADCSRA: 1000 0111 (aktivieren und nicht gestarten)
	ADCSRA = 0x87;
	
	LCD_Init();
	
	DDRA = 0xFF;
	
    while (1) 
    {
		//1: ADU starten
		//Bit ADSC im Register ADSCRA setzen
		ADCSRA |= (1<<ADSC);
		
		//2: Warten, solange ADU beschäftigt ist -> Solange ADSC gesetzt ist
		//while ((ADSCRA&0x40)!= 0)
		while(BitQuery(&ADCSRA, ADSC) == SET)
		{	
		}
		//3: Ergebnis auswerten 
		resultat = ADCL + (ADCH << 8); 
		//short value = ADCL + ADCH * 256;
	
		if(resultat > 500)
		{
			PORTA = 0xFF;
		}
		else
		PORTA = 0x00;
		
		sprintf(text, "ADU = %04d", resultat);
		LCD_SendText(text, 1, 1);	
    }
}

