/*
 * LCD_ATMEGA2560_Addon_Board.c
 * Erstellt am:			9.5.2020
 * Autor:				Peter Frauscher
 * Aufgabenstellung:	Bibliothek mit Funktionen für LCD mit ATMEGA2560
 * Update:				16.3.2021
 *						Pinbelegung für Addon Board angepasst
 * Version:				1.1
 */ 

/*
LCD-Ansteuerung / Pinbelegung:
					Pin		PORT	Bit
Register Select RS	7		H		0
Enable EN			8		H		1
Datenleitung D4		9		H		3		
Datenleitung D5		10		H		4
Datenleitung D6		11		H		5
Datenleitung D7		12		H		6
Read/Write R/W		GND
VSS					GND
VCC					+5V
10k Widerstand:		Auf +5V bzw. GND, Schleifer auf LCD, Pin 3
Kontrast LCD VO		3	 
*/

#define LCD_C
#include "LCD_ATMEGA2560_Addon_Board.h"

/* void LCD_Send4Bit(char data, char modus)
 *	Aufgabe:			4 Bit Daten über den 4 Bit Datenbus senden
 *	Rückgabewert:		Keiner
 *	Übergabeparameter:	
 *		char data		Die unteren 4 Bit werden auf den 4 Bit-Datenbus gelegt und ans LCD gesendet
 *		char modus		SEND_COMMAND:	Es wird ein Kommando gesendet
 *						SEND_DATA:		Es werden Daten gesendet				
 */
void LCD_Send4Bit(char data, char modus)
{
	int i;
	
	if(modus == SEND_COMMAND)
	{
		//RS löschen
		*CommandPort &= ~(1<<RS);
	}
	else
	{
		//RS setzen
		*CommandPort |= (1<<RS);
	}
	
	//EN setzen
	*CommandPort |= (1<<EN);
	//4 Datenleitungen löschen
	for (i=0; i<4; i++)
	{
		*DataPort[i] &= ~(1<<DataBit[i]);
	}
	//4 Datenbits auf Datenleitungen setzen
	for (i=0; i<4; i++)
	{
		//Datenbit zu setzen
		if(data & (1<<i))
			*DataPort[i] |= (1<<DataBit[i]);
	}
	//EN löschen
	*CommandPort &= ~(1<<EN);
}

/* void LCD_Send8Bit(char data, char modus)
 *	Aufgabe:			Verwendet die Funktion LCD_Send4Bit(), um zuerst die oberen 4 Bit
 *						und dann die unteren 4 Bit des Parameters data zu senden
 *	Rückgabewert:		Keiner
 *	Übergabeparameter:	
 *		char data		Die 8 Bit werden zu je 4 bit auf den 4 Bit-Datenbus gelegt und ans LCD gesendet
 *		char modus		SEND_COMMAND:	Es wird ein Kommando gesendet
 *						SEND_DATA:		Es werden Daten gesendet				
 */
void LCD_Send8Bit(char data, char modus)
{
	//data = 0x28
	LCD_Send4Bit(data>>4, modus);
	_delay_us(1);
	LCD_Send4Bit(data&0x0F, modus);
	_delay_us(40);
}

/* LCD_Reset()
 *	Aufgabe:			Arbeitet eine bestimmte Kommandosequenz ab, um das LCD zurück setzen
 *	Rückgabewert:		Keiner
 *	Übergabeparameter:	Keiner
 */
void LCD_Reset()
{
	_delay_ms(15);
	LCD_Send4Bit(0x03, SEND_COMMAND);
	_delay_ms(4.1);
	LCD_Send4Bit(0x03, SEND_COMMAND);
	_delay_us(100);
	LCD_Send4Bit(0x03, SEND_COMMAND);
	_delay_us(40);
	LCD_Send4Bit(0x02, SEND_COMMAND);
	_delay_us(40);
}

/* LCD_Init()
 *	Aufgabe:			Initialisiert die digitalen I/Os und sendet Kommandos zur Initialisierung ans LCD
 *	Rückgabewert:		Keiner
 *	Übergabeparameter:	Keiner
 */
void LCD_Init()
{
	int i;
	
	//Alle LCD-Pins als Ausgänge
	*CommandDDR |= (1<<EN);
	*CommandDDR |= (1<<RS);
	for (i=0; i<4; i++)
	{
		*DataDDR[i] |= (1<<DataBit[i]);
	}
	//EN löschen
	*CommandPort &= ~(1<<EN);

	LCD_Reset();
	LCD_Send8Bit(0x28, SEND_COMMAND);
	LCD_Send8Bit(0x06, SEND_COMMAND);
	LCD_Send8Bit(0x0C, SEND_COMMAND);
	LCD_Send8Bit(0x01, SEND_COMMAND);
	_delay_ms(1.64);
	
	LCD_Clear();
}

/* LCD_Clear()
 *	Aufgabe:			Löscht das LCD
 *	Rückgabewert:		Keiner
 *	Übergabeparameter:	Keiner
 */
void LCD_Clear()
{
	LCD_Send8Bit(0x01, SEND_COMMAND);
	_delay_ms(1.64);
}

/* void LCD_SetCursorPos(char row, char column)
 *	Aufgabe:			Setzt die Cursor-Position auf eine gewisse Zeile / Spalte
 *	Rückgabewert:		Keiner
 *	Übergabeparameter:	
 *		char row		Zeile: 1 oder 2
 *		char column		Spalte: 1 bis 16
 */
void LCD_SetCursorPos(char row, char column)
{
	LCD_Send8Bit(0x80 + (column-1) + 0x40*(row-1), SEND_COMMAND);
}

/* void LCD_SendData(char data, char row, char column)
 *	Aufgabe:			Sendet ein bestimmtes Zeichen, das an einer bestimmten Position dargestellt wird
 *	Rückgabewert:		Keiner
 *	Übergabeparameter:	
 *		char data		Zeichen
 *		char row		Zeile: 1 oder 2
 *		char column		Spalte: 1 bis 16
 */
void LCD_SendData(char data, char row, char column)
{
	LCD_SetCursorPos(row,column);
	LCD_Send8Bit(data, SEND_DATA);
}

/* void LCD_SendText(char text[], char row, char column)
 *	Aufgabe:			Sendet einen bestimmten Text, der ab einer bestimmten Position dargestellt wird
 *	Rückgabewert:		Keiner
 *	Übergabeparameter:	
 *		char text[]		Text (String)
 *		char row		Zeile: 1 oder 2
 *		char column		Spalte: 1 bis 16
 */
void LCD_SendText(char text[], char row, char column)
{
	int i;
	for(i=0; text[i] != '\0'; i++)
	LCD_SendData(text[i], row, column+i);
	
}
