/*
* ADU_ATMEGA2560.h
* Erstellt am: 9.5.2020  / 7.3.2021
* Autor: Peter Frauscher / Manfred Dobaj
* Aufgabenstellung: Bibliothek mit Funktionen für LCD mit ATMEGA2560
* Update DO 07.03.2021 ... LCD auf AddonBoard -Pins angepasst
* Version: 1.1
*/

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

#define SEND_DATA 0
#define SEND_COMMAND 1

#define RS 0 //PORTH, Bit 0
#define EN 1 //PORTH, Bit 1
#define D4 3 //PORTH, Bit 3
#define D5 4 //PORTH, Bit 4
#define D6 5 //PORTH, Bit 5
#define D7 6 //PORTH, Bit 6

#ifdef LCD_C
volatile uint8_t *CommandPort = &PORTH;
volatile uint8_t *CommandDDR = &DDRH;
volatile uint8_t *DataPort[] = {&PORTH,&PORTH,&PORTH,&PORTH};
volatile uint8_t *DataDDR[] = {&DDRH,&DDRH,&DDRH,&DDRH};
char DataBit[] = {D4,D5,D6,D7};
#endif

void LCD_Send4Bit(char data, char modus);
void LCD_Reset();
void LCD_Clear();
void LCD_Send8Bit(char data, char modus);
void LCD_Init();
void LCD_SetCursorPos(char row, char column);
void LCD_SendData(char data, char row, char column);
void LCD_SendText(char text[], char row, char column);

#endif /* LCD_H_ */