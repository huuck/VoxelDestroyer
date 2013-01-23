/*
 * ColorDecoder.h
 *
 *  Created on: Oct 18, 2012
 *      Author: Gabi
 */

#ifndef COLORDECODER_H_
#define COLORDECODER_H_

const double colorsArray[] =   {0x0009BA, 0x5884FF, 0x8FBDFF,
								0x2F00B9, 0x6D67FB, 0x9DACFF,
								0x62169C, 0xA872FC, 0xCEACFF,
								0x962577, 0xEE61FE, 0xF9AEFF,
								0xA91734, 0xFF5E80, 0XFEB5C6,
								0x744200, 0xFF9E00, 0xFED79C,
								0x585301, 0xDFD420, 0xFFEE90,
								0x456800, 0xABE507, 0xC7EF7F,
								0x266B00, 0x6FEF40, 0xAEEF9F,
								0x336041, 0x72DEAA, 0x9DFFD1,
								0x32517F, 0X5FD0E2, 0x9EFCFC,
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
	return ((x+8.0f) + (y+8.0f) * 16.0f + (z+8.0f) * 256.0f);
}

#endif /* COLORDECODER_H_ */
