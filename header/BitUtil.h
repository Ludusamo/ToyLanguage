#ifndef BITUTIL_H
#define BITUTIL_H

class BitUtil {
public:
	const static char *BITS;
	const static char *BIT_MASKS;
	static void turnOnBit(char &byte, int bit);
	static void turnOffBit(char &byte, int bit);	
	static bool checkBit(char byte, int bit);
	static void flipBit(char &byte, int bit);
};

#endif // BITUTIL_H
