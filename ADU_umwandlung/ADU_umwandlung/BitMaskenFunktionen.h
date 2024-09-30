/*
 * BitMaskenFunktionen.h
 *
 * Created: 28.04.2021 12:42:37
 *  Author: Peter Frauscher
 */ 


#ifndef BITMASKENFUNKTIONEN_H_
#define BITMASKENFUNKTIONEN_H_
	#include <stdint.h>

	#define CLEARED 0
	#define SET 1

	void BitSet(volatile uint8_t *target, unsigned int bit);
	void BitClear(volatile uint8_t *target, unsigned int bit);
	void BitToggle(volatile uint8_t *target, unsigned int bit);
	char BitQuery(volatile uint8_t *target, unsigned int bit);

#endif /* BITMASKENFUNKTIONEN_H_ */