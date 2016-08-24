
#include <Time.h>
#include <TimeLib.h>

#ifndef ESP_H
#include <LedControl.h>
#else
//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

class LedControl {
private:
	void spiTransfer(int addr, volatile byte opcode, volatile byte data) {
		//Create an array with the data to shift out
		byte spidata[16];
		/* The array for shifting the data to the devices */
		int offset = addr * 2;
		int maxbytes = maxDevices * 2;

		for (int i = 0; i<maxbytes; i++)
			spidata[i] = (byte)0;
		//put our device data into the array
		spidata[offset + 1] = opcode;
		spidata[offset] = data;
		//enable the line 
		digitalWrite(SPI_CS, LOW);
		//Now shift out the data 
		for (int i = maxbytes; i>0; i--)
			shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, spidata[i - 1]);
		//latch the data onto the display
		digitalWrite(SPI_CS, HIGH);
	}

	/* Data is shifted out of this pin*/
	int SPI_MOSI;
	/* The clock is signaled on this pin */
	int SPI_CLK;
	/* This one is driven LOW for chip selection */
	int SPI_CS;
	/* The maximum number of devices we use */
	int maxDevices;
public:
	LedControl(int dataPin, int clkPin, int csPin, int numDevices) {
		SPI_MOSI = dataPin;
		SPI_CLK = clkPin;
		SPI_CS = csPin;
		if (numDevices <= 0 || numDevices > 8)
			numDevices = 8;
		maxDevices = numDevices;
		pinMode(SPI_MOSI, OUTPUT);
		pinMode(SPI_CLK, OUTPUT);
		pinMode(SPI_CS, OUTPUT);
		digitalWrite(SPI_CS, HIGH);
		SPI_MOSI = dataPin;
		for (int i = 0; i < maxDevices; i++) {
			spiTransfer(i, OP_DISPLAYTEST, 0);
			//scanlimit is set to max on startup
			setScanLimit(i, 7);
			//decode is done in source
			spiTransfer(i, OP_DECODEMODE, 0);
			clearDisplay(i);
			//we go into shutdown-mode on startup
			shutdown(i, true);
		}
	}

	void shutdown(int addr, bool b) {
		if (addr<0 || addr >= maxDevices)
			return;
		if (b)
			spiTransfer(addr, OP_SHUTDOWN, 0);
		else
			spiTransfer(addr, OP_SHUTDOWN, 1);
	}

	void setScanLimit(int addr, int limit) {
		if (addr<0 || addr >= maxDevices)
			return;
		if (limit >= 0 && limit<8)
			spiTransfer(addr, OP_SCANLIMIT, limit);
	}

	void setIntensity(int addr, int intensity) {
		if (addr<0 || addr >= maxDevices)
			return;
		if (intensity >= 0 && intensity<16)
			spiTransfer(addr, OP_INTENSITY, intensity);
	}

	void clearDisplay(int addr) {
		if (addr<0 || addr >= maxDevices)
			return;
		for (int i = 0; i<8; i++) {
			spiTransfer(addr, i + 1, 0);
		}
	}

	void setRow(int addr, int row, byte value) {
		if (addr < 0 || addr >= maxDevices)
			return;
		if (row < 0 || row>7)
			return;
		spiTransfer(addr, row + 1, value);
	}
};
#endif

const int numDevices = 4;      // number of MAX7219s used
LedControl lc = LedControl(12, 11, 10, numDevices);

unsigned char scrollText[] =
{"00:00:00am\0"};
//01234567890

void setup() {
  // put your setup code here, to run once:
  for (int x=0; x<numDevices; x++)
  {
    lc.shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
    lc.setIntensity(x,0);       // Set the brightness to default value
    lc.clearDisplay(x);         // and clear the display
  }
  setTime(12, 59, 0, 23, 7, 2016);
  Serial.begin(57600);
}

void UpdateTime(void);
void LoadMessage(unsigned char * message);
void LoadDisplayBuffer(void);

void loop() {
  // put your main code here, to run repeatedly:
  UpdateTime();
  LoadMessage(scrollText);
  LoadDisplayBuffer();
  delay(100);
}

void UpdateTime(void)
{
  time_t tm = now();

  int hour = hourFormat12(tm);
  if (hour < 10)
  {
    scrollText[0] = ' ';
    scrollText[1] = '0' + hour;
  }
  else
  {
    scrollText[0] = '1';
    scrollText[1] = '0' + (hour-10);
  }

  int min = minute(tm);
  int min10 = min / 10;
  scrollText[3] = '0' + min10;
  scrollText[4] = '0' + min - (min10 * 10);

  int sec = second(tm);
  int sec10 = sec / 10;
  scrollText[6] = '0' + sec10;
  scrollText[7] = '0' + sec - (sec10 * 10);

  if (isAM(tm))
  {
    scrollText[8] = 'a';
    scrollText[9] = 'm';
  }
  else
  {
    scrollText[8] = 'p';
    scrollText[9] = 'm';
  }
}


