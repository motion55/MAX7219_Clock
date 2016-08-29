
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "BST";  //  your network SSID (name)
char pass[] = "";       // your network password

unsigned int localPort = 2390;      // local port to listen for UDP packets

const char* ntpServerName = "ntp.pagasa.dost.gov.ph";

// NTP time stamp is in the first 48 bytes of the message
const int NTP_PACKET_SIZE = 48; 

//buffer to hold incoming and outgoing packets
byte packetBuffer[NTP_PACKET_SIZE]; 

//A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

/*////////////////////////////////////////////////////////////////////////////////*/

#include <Time.h>
#include <TimeLib.h>

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
		for (int i = maxbytes; i > 0; i--)
		{
			shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, spidata[i - 1]);
			delay(0);
		}
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
		pinMode(10, OUTPUT);
		digitalWrite(10, HIGH); //To enusre SS pin is HIGH
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

const int numDevices = 4;      // number of MAX7219s used
const int SPI_MOSI = 13;
const int SPI_CLK = 14;
const int SPI_CS = 15;

LedControl lc = LedControl(SPI_MOSI, SPI_CLK, SPI_CS, numDevices);

unsigned char scrollText[] =
{ "00:00:00am \0" };
// 01234567890

void UpdateTime(void);
int LoadMessage(unsigned char * message);
void ResetScrollPos(void);
int LoadDisplayBuffer(int BufferLen);

void setup() {
	// put your setup code here, to run once:
	for (int x=0; x<numDevices; x++)
	{
		lc.shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
		lc.setIntensity(x,1);       // Set the brightness to minimum value
		lc.clearDisplay(x);         // and clear the display
	}
	setTime(12, 59, 0, 23, 7, 2016);

	unsigned char ConnectStr[] = { "Connecting.\0" };

	ResetScrollPos();
	int Len = LoadMessage(ConnectStr);
	while (WiFi.status() != WL_CONNECTED) {
		LoadDisplayBuffer(Len);
		delay(100);
	}
	ResetScrollPos();

	Serial.begin(115200);
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	Serial.println("Starting UDP");
	udp.begin(localPort);
	Serial.print("Local port: ");
	Serial.println(udp.localPort());

	setSyncProvider(getNtpTime);
}

void loop() {
	// put your main code here, to run repeatedly:
	UpdateTime();
	int Len = LoadMessage(scrollText);
	LoadDisplayBuffer(Len);
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

const int timeZone = 8 * SECS_PER_HOUR;     // PHT

time_t getNtpTime()
{
	IPAddress timeServerIP;

	while (udp.parsePacket() > 0); // discard any previously received packets
	Serial.println("Transmit NTP Request");
	WiFi.hostByName(ntpServerName, timeServerIP);
	sendNTPpacket(timeServerIP); // send an NTP packet to a time server
								 // wait to see if a reply is available
	uint32_t endWait = millis();
	uint32_t beginWait = endWait;
	while (endWait - beginWait < 1500) {
		int size = udp.parsePacket();
		if (size >= NTP_PACKET_SIZE) {
			Serial.println("Receive NTP Response");
			udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
			unsigned long secsSince1900;
			// convert four bytes starting at location 40 to a long integer
			secsSince1900 = (unsigned long)packetBuffer[40] << 24;
			secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
			secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
			secsSince1900 |= (unsigned long)packetBuffer[43];
			return secsSince1900 - 2208988800UL + timeZone + ((endWait - beginWait)/1000);
		}
		endWait = millis();
	}
	Serial.println("No NTP Response :-(");
	return 0; // return 0 if unable to get the time
}


// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
	Serial.println("sending NTP packet...");
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
							 // 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	udp.beginPacket(address, 123); //NTP requests are to port 123
	udp.write(packetBuffer, NTP_PACKET_SIZE);
	udp.endPacket();
}
