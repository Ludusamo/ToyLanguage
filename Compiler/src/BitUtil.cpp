#include "BitUtil.h"

const static char BIT_DATA[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
const char* BitUtil::BITS = BIT_DATA;

const static char BIT_MASK_DATA[] = { 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F };
const char* BitUtil::BIT_MASKS = BIT_MASK_DATA;

void BitUtil::turnOnBit(char &byte, int bit) {
	byte |= BITS[bit];
}

void BitUtil::turnOffBit(char &byte, int bit) {
	byte &= BIT_MASKS[bit];
}

bool BitUtil::checkBit(char byte, int bit) {
	byte |= BIT_MASKS[bit];	
	return byte != BIT_MASKS[bit];
}

void BitUtil::flipBit(char &byte, int bit) {
	(checkBit(byte, bit)) ? turnOffBit(byte, bit) : turnOnBit(byte, bit);
}
