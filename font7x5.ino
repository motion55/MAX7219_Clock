
#ifdef ESP_H
#undef PROGMEM
#ifndef PROGMEM
#define PROGMEM
#endif
#else
#include <avr/pgmspace.h>
#endif


const unsigned char font7x5[] PROGMEM = {
	//   offset = 0
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// ! offset = 6
	0b01001111,
	0b00000000,
	// " offset = 8
	0b00000111,
	0b00000000,
	0b00000111,
	0b00000000,
	// # offset = 12
	0b00010100,
	0b01111111,
	0b00010100,
	0b01111111,
	0b00010100,
	0b00000000,
	// $ offset = 18
	0b00100100,
	0b00101010,
	0b01111111,
	0b00101010,
	0b00010010,
	0b00000000,
	// % offset = 24
	0b00100011,
	0b00010011,
	0b00001000,
	0b01100100,
	0b01100010,
	0b00000000,
	// & offset = 30
	0b00110110,
	0b01001001,
	0b01010101,
	0b00100010,
	0b01010000,
	0b00000000,
	// ' offset = 36
	0b00000101,
	0b00000011,
	0b00000000,
	// ( offset = 39
	0b00011100,
	0b00100010,
	0b01000001,
	0b00000000,
	// ) offset = 43
	0b01000001,
	0b00100010,
	0b00011100,
	0b00000000,
	// * offset = 47
	0b00010100,
	0b00001000,
	0b00111110,
	0b00001000,
	0b00010100,
	0b00000000,
	// + offset = 53
	0b00001000,
	0b00001000,
	0b00111110,
	0b00001000,
	0b00001000,
	0b00000000,
	// , offset = 59
	0b01010000,
	0b00110000,
	0b00000000,
	// - offset = 62
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000000,
	// . offset = 68
	0b01100000,
	0b01100000,
	0b00000000,
	// / offset = 71
	0b00100000,
	0b00010000,
	0b00001000,
	0b00000100,
	0b00000010,
	0b00000000,
	// 0 offset = 77
	0b00111110,
	0b01010001,
	0b01001001,
	0b01000101,
	0b00111110,
	0b00000000,
	// 1 offset = 83
	0b00000000,
	0b01000010,
	0b01111111,
	0b01000000,
	0b00000000,
	0b00000000,
	// 2 offset = 89
	0b01000010,
	0b01100001,
	0b01010001,
	0b01001001,
	0b01000110,
	0b00000000,
	// 3 offset = 95
	0b00100001,
	0b01000001,
	0b01000101,
	0b01001011,
	0b00110001,
	0b00000000,
	// 4 offset = 101
	0b00011000,
	0b00010100,
	0b00010010,
	0b01111111,
	0b00010000,
	0b00000000,
	// 5 offset = 107
	0b00100111,
	0b01000101,
	0b01000101,
	0b01000101,
	0b00111001,
	0b00000000,
	// 6 offset = 113
	0b00111100,
	0b01001010,
	0b01001001,
	0b01001001,
	0b00110000,
	0b00000000,
	// 7 offset = 119
	0b00000011,
	0b00000001,
	0b01110001,
	0b00001001,
	0b00000111,
	0b00000000,
	// 8 offset = 125
	0b00110110,
	0b01001001,
	0b01001001,
	0b01001001,
	0b00110110,
	0b00000000,
	// 9 offset = 131
	0b00000110,
	0b01001001,
	0b01001001,
	0b00101001,
	0b00011110,
	0b00000000,
	// : offset = 137
	0b00110110,
	0b00110110,
	0b00000000,
	// ; offset = 140
	0b01010110,
	0b00110110,
	0b00000000,
	// < offset = 143
	0b00001000,
	0b00010100,
	0b00100010,
	0b01000001,
	0b00000000,
	// = offset = 148
	0b00010100,
	0b00010100,
	0b00010100,
	0b00010100,
	0b00010100,
	0b00000000,
	// > offset = 154
	0b01000001,
	0b00100010,
	0b00010100,
	0b00001000,
	0b00000000,
	// ? offset = 159
	0b00000010,
	0b00000001,
	0b01010001,
	0b00001001,
	0b00000110,
	0b00000000,
	// @ offset = 165
	0b00110010,
	0b01001001,
	0b01111001,
	0b01000001,
	0b00111110,
	0b00000000,
	// A offset = 171
	0b01111110,
	0b00010001,
	0b00010001,
	0b00010001,
	0b01111110,
	0b00000000,
	// B offset = 177
	0b01111111,
	0b01001001,
	0b01001001,
	0b01001001,
	0b00110110,
	0b00000000,
	// C offset = 183
	0b00111110,
	0b01000001,
	0b01000001,
	0b01000001,
	0b00100010,
	0b00000000,
	// D offset = 189
	0b01111111,
	0b01000001,
	0b01000001,
	0b00100010,
	0b00011100,
	0b00000000,
	// E offset = 195
	0b01111111,
	0b01001001,
	0b01001001,
	0b01001001,
	0b01000001,
	0b00000000,
	// F offset = 201
	0b01111111,
	0b00001001,
	0b00001001,
	0b00001001,
	0b00000001,
	0b00000000,
	// G offset = 207
	0b00111110,
	0b01000001,
	0b01001001,
	0b01001001,
	0b01111010,
	0b00000000,
	// H offset = 213
	0b01111111,
	0b00001000,
	0b00001000,
	0b00001000,
	0b01111111,
	0b00000000,
	// I offset = 219
	0b01000001,
	0b01111111,
	0b01000001,
	0b00000000,
	// J offset = 223
	0b00100000,
	0b01000000,
	0b01000001,
	0b00111111,
	0b00000001,
	0b00000000,
	// K offset = 229
	0b01111111,
	0b00001000,
	0b00010100,
	0b00100010,
	0b01000001,
	0b00000000,
	// L offset = 235
	0b01111111,
	0b01000000,
	0b01000000,
	0b01000000,
	0b01000000,
	0b00000000,
	// M offset = 241
	0b01111111,
	0b00000010,
	0b00001100,
	0b00000010,
	0b01111111,
	0b00000000,
	// N offset = 247
	0b01111111,
	0b00000100,
	0b00001000,
	0b00010000,
	0b01111111,
	0b00000000,
	// O offset = 253
	0b00111110,
	0b01000001,
	0b01000001,
	0b01000001,
	0b00111110,
	0b00000000,
	// P offset = 259
	0b01111111,
	0b00001001,
	0b00001001,
	0b00001001,
	0b00000110,
	0b00000000,
	// Q offset = 265
	0b00111110,
	0b01000001,
	0b01010001,
	0b00100001,
	0b01011110,
	0b00000000,
	// R offset = 271
	0b01111111,
	0b00001001,
	0b00011001,
	0b00101001,
	0b01000110,
	0b00000000,
	// S offset = 277
	0b01000110,
	0b01001001,
	0b01001001,
	0b01001001,
	0b00110001,
	0b00000000,
	// T offset = 283
	0b00000001,
	0b00000001,
	0b01111111,
	0b00000001,
	0b00000001,
	0b00000000,
	// U offset = 289
	0b00111111,
	0b01000000,
	0b01000000,
	0b01000000,
	0b00111111,
	0b00000000,
	// V offset = 295
	0b00011111,
	0b00100000,
	0b01000000,
	0b00100000,
	0b00011111,
	0b00000000,
	// W offset = 301
	0b00111111,
	0b01000000,
	0b00111000,
	0b01000000,
	0b00111111,
	0b00000000,
	// X offset = 307
	0b01100011,
	0b00010100,
	0b00001000,
	0b00010100,
	0b01100011,
	0b00000000,
	// Y offset = 313
	0b00000111,
	0b00001000,
	0b01110000,
	0b00001000,
	0b00000111,
	0b00000000,
	// Z offset = 319
	0b01100001,
	0b01010001,
	0b01001001,
	0b01000101,
	0b01000011,
	0b00000000,
	// [ offset = 325
	0b01111111,
	0b01000001,
	0b01000001,
	0b00000000,
	// \ offset = 329
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b00000000,
	// ] offset = 335
	0b01000001,
	0b01000001,
	0b01111111,
	0b00000000,
	// ^ offset = 339
	0b00000100,
	0b00000010,
	0b00000001,
	0b00000010,
	0b00000100,
	0b00000000,
	// _ offset = 345
	0b01000000,
	0b01000000,
	0b01000000,
	0b01000000,
	0b01000000,
	0b00000000,
	// ` offset = 351
	0b00000001,
	0b00000010,
	0b00000100,
	0b00000000,
	// a offset = 355
	0b00100000,
	0b01010100,
	0b01010100,
	0b01010100,
	0b01111000,
	0b00000000,
	// b offset = 361
	0b01111111,
	0b01001000,
	0b01000100,
	0b01000100,
	0b00111000,
	0b00000000,
	// c offset = 367
	0b00111000,
	0b01000100,
	0b01000100,
	0b01000100,
	0b00101000,
	0b00000000,
	// d offset = 373
	0b00111000,
	0b01000100,
	0b01000100,
	0b01001000,
	0b01111111,
	0b00000000,
	// e offset = 379
	0b00111000,
	0b01010100,
	0b01010100,
	0b01010100,
	0b00011000,
	0b00000000,
	// f offset = 385
	0b00001000,
	0b01111110,
	0b00001001,
	0b00000001,
	0b00000010,
	0b00000000,
	// g offset = 391
	0b00001100,
	0b01010010,
	0b01010010,
	0b01010010,
	0b00111110,
	0b00000000,
	// h offset = 397
	0b01111111,
	0b00001000,
	0b00000100,
	0b00000100,
	0b01111000,
	0b00000000,
	// i offset = 403
	0b01000100,
	0b01111101,
	0b01000000,
	0b00000000,
	// j offset = 407
	0b00100000,
	0b01000000,
	0b01000100,
	0b00111101,
	0b00000000,
	// k offset = 412
	0b01111111,
	0b00010000,
	0b00101000,
	0b01000100,
	0b00000000,
	// l offset = 417
	0b01000001,
	0b01111111,
	0b01000000,
	0b00000000,
	// m offset = 421
	0b01111100,
	0b00000100,
	0b00011000,
	0b00000100,
	0b01111000,
	0b00000000,
	// n offset = 427
	0b01111100,
	0b00001000,
	0b00000100,
	0b00000100,
	0b01111000,
	0b00000000,
	// o offset = 433
	0b00111000,
	0b01000100,
	0b01000100,
	0b01000100,
	0b00111000,
	0b00000000,
	// p offset = 439
	0b01111100,
	0b00010100,
	0b00010100,
	0b00010100,
	0b00001000,
	0b00000000,
	// q offset = 445
	0b00001000,
	0b00010100,
	0b00010100,
	0b00011000,
	0b01111100,
	0b00000000,
	// r offset = 451
	0b01111100,
	0b00001000,
	0b00000100,
	0b00000100,
	0b00001000,
	0b00000000,
	// s offset = 457
	0b01001000,
	0b01010100,
	0b01010100,
	0b01010100,
	0b00100000,
	0b00000000,
	// t offset = 463
	0b00000100,
	0b00111111,
	0b01000100,
	0b01000000,
	0b00100000,
	0b00000000,
	// u offset = 469
	0b00111100,
	0b01000000,
	0b01000000,
	0b00100000,
	0b01111100,
	0b00000000,
	// v offset = 475
	0b00011100,
	0b00100000,
	0b01000000,
	0b00100000,
	0b00011100,
	0b00000000,
	// w offset = 481
	0b00111100,
	0b01000000,
	0b00111000,
	0b01000000,
	0b00111100,
	0b00000000,
	// x offset = 487
	0b01000100,
	0b00101000,
	0b00010000,
	0b00101000,
	0b01000100,
	0b00000000,
	// y offset = 493
	0b00001100,
	0b01010000,
	0b01010000,
	0b01010000,
	0b00111100,
	0b00000000,
	// z offset = 499
	0b01000100,
	0b01100100,
	0b01010100,
	0b01001100,
	0b01000100,
	0b00000000,
	// { offset = 505
	0b00001000,
	0b00110110,
	0b01000001,
	0b00000000,
	// | offset = 509
	0b01111111,
	0b00000000,
	// } offset = 511
	0b01000001,
	0b00110110,
	0b00001000,
	0b00000000,
	// ~ offset = 515
	0b00010000,
	0b00001000,
	0b00001000,
	0b00010000,
	0b00001000,
	0b00000000,
	//  offset = 521
	0b00000110,
	0b00001001,
	0b00001001,
	0b00000110,
	0b00000000,
};

const char font7x5_kern[] PROGMEM = {
	6,2,4,6,6,6,6,3,
	4,4,6,6,3,6,3,6,
	6,6,6,6,6,6,6,6,
	6,6,3,3,5,6,5,6,
	6,6,6,6,6,6,6,6,
	6,4,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,
	6,6,6,4,6,4,6,6,
	4,6,6,6,6,6,6,6,
	6,4,5,5,4,6,6,6,
	6,6,6,6,6,6,6,6,
	6,6,6,4,2,4,6,5,
};

const int font7x5_offset[] PROGMEM = {
	0,  6,  8, 12, 18, 24, 30, 36,
	39, 43, 47, 53, 59, 62, 68, 71,
	77, 83, 89, 95,101,107,113,119,
	125,131,137,140,143,148,154,159,
	165,171,177,183,189,195,201,207,
	213,219,223,229,235,241,247,253,
	259,265,271,277,283,289,295,301,
	307,313,319,325,329,335,339,345,
	351,355,361,367,373,379,385,391,
	397,403,407,412,417,421,427,433,
	439,445,451,457,463,469,475,481,
	487,493,499,505,509,511,515,521,
};

int LoadPos = 0;
const int ColumnBufferLen = 64;
unsigned char ColumnBuffer[ColumnBufferLen];

void ResetColumnBuffer()
{
	for (int col = 0; col < ColumnBufferLen; col++)
	{
		ColumnBuffer[col] = 0;
	}
	LoadPos = 0;
}

char LoadColumnBuffer(char ascii)
{
	char kern = 0;
	if (ascii >= 0x20 && ascii <= 0x7f)
	{
#ifdef ESP_H
		kern = font7x5_kern[ascii - 0x20];
		int offset = font7x5_offset[ascii - 0x20];
#else
		kern = pgm_read_byte_near(font7x5_kern + (ascii-0x20));
		int offset = pgm_read_word_near(font7x5_offset + (ascii-0x20));
#endif

		for (int i = 0; i < kern; i++)
		{
			if (LoadPos >= ColumnBufferLen) return i;
#ifdef ESP_H
			ColumnBuffer[LoadPos] = font7x5[offset];
#else
			ColumnBuffer[LoadPos] = pgm_read_byte_near(font7x5 + offset);
#endif
			LoadPos++; offset++;
		}
	}
	return kern;
}

int LoadMessage(unsigned char * message)
{
	ResetColumnBuffer();
	for (int counter = 0; ; counter++)
	{
		// read back a char 
		unsigned char myChar = message[counter];
		if (myChar != 0)
		{
			LoadColumnBuffer(myChar);
		}
		else break;
	}
	return LoadPos;
}

int ScrollPos;

void ResetScrollPos(void)
{
	ScrollPos = 0;
}

int LoadDisplayBuffer(int BufferLen)
{
	unsigned char DisplayBuffer[8];

	if (ScrollPos >= BufferLen) ScrollPos = 0;
	int Pos = ScrollPos++;

	for (int device = numDevices - 1; device >= 0; device--)
	{
		for (int col = 0; col < 8; col++)
		{
			if (Pos >= BufferLen) Pos = 0;
			unsigned char dat = ColumnBuffer[Pos++];
			for (int row = 0; row < 8; row++)
			{
				DisplayBuffer[row] <<= 1;
				if (dat & 1)
				{
					DisplayBuffer[row] += 1;
				}
				dat >>= 1;
			}
		}

		for (int row = 0; row < 8; row++)
		{
			byte x = DisplayBuffer[row];
			lc.setRow(device, row, x);	// Send row to relevent MAX7219 chip
		}
	}

	return Pos;
}
