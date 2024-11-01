/*
 * InterruptServiceRoutine.c
 *
 * Created: 21.10.2024 17:47:59
 * Author : gspur
 
 *Aufgabenstellung: 
 * Bei Betätigung von Taster 1 soll ein Zähler erhöht werden.
 * Der Zustand des Zählers soll mit den LEDs an Port A angezeigt werden.
 * Taster 1: angeschlossen an Port D, Bit2 -> externer Interrupt 2, negative Flanke bei Betätigung 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRA |= 0xFF;
    DDRD &= 0x00;
	
	EICRA |= 0x30;
	EIMSK |= 0x04;
	//EIMSK |= (1<<INT1);
	sei();
	
    while (1) 
    {
    }
}

