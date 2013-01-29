/*
 * ColorDecoder.h
 *
 *  Created on: Oct 18, 2012
 *      Author: Gabi
 */

#ifndef COLORDECODER_H_
#define COLORDECODER_H_

const double colorsArray[] =   {0x0009BA, 0x5B82FF, 0x8FBCFF,
								0x2C00B7, 0x6B67FF, 0x9EACFF,
								0x60179E, 0xAC6FFF, 0xCBAEFF,
								0x972577, 0xEF60FF, 0xF9AEFF,//
								0xAE1733, 0xFF607E, 0XFFB6C4,//
								0x774200, 0xFF9E00, 0xFFD79E,//
								0x585300, 0xE7CF25, 0xFFEF8F,//
								0x456800, 0xA9E700, 0xC7EF7F,//
								0x266B00, 0x6FEF42, 0xADEF9E,//
								0x336042, 0x6FDFAC, 0x9EFFD1,//
								0x33517F, 0X60CFDF, 0x9EFCFF,
								0x000000, 0x909090, 0xFFFFFF};

double decodeColorFor(char c) {
	short colorIndex = 666;

	if(c >= 48 && c <= 57) {
		colorIndex = c - 48 + 26;
	}

	if(c >= 97 && c <= 122) {
		colorIndex = c - 97;
	}

	if(colorIndex < 36) {
		return colorsArray[colorIndex];
	} else {
		//unknown color
		return -1;
	}
}

int getIForXYZ(float x, float y, float z) {
	return (x + y * 16.0f + z * 256.0f);
}

#endif /* COLORDECODER_H_ */
