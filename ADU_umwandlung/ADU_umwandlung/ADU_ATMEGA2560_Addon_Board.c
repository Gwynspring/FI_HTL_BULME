/*
 * ADU_ATMEGA2560_Addon_Board.c
 *
 * Created: 14.10.2024 17:58:08
 *  Author: gspur
 */ 
#include "BitMaskenFunktionen.h"
#include "ADU_ATMEGA2560_Addon_Board.h"
#include <avr/io.h>

void ADU_Init()
{
	//ADU Kanal 0
	//ADMUX 0100 0000
	ADMUX = 0x40;
	
	//ADCSRA: 1000 0111 (aktivieren und nicht gestarten)
	ADCSRA = 0x87;
}

short ADU_Read(char ADU_channel)
{
	short resultat;
	
	ADMUX &= 0xF8;
	//BitClear(&ADMUX, MUX0);
	ADMUX |= ADU_channel;
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
	
	return resultat;
}


