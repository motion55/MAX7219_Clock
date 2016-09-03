
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <Time.h>
#include <TimeLib.h>

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

const int numDevices = 4;      // number of MAX7219s used
const int SPI_MOSI = 13;
const int SPI_CLK = 14;
const int SPI_CS = 15;

unsigned char scrollText[] =
{ "00:00:00am \0" };
// 01234567890

void InitMax7219();
void UpdateTime(void);
int LoadMessage(unsigned char * message);
void ResetScrollPos(void);
int LoadDisplayBuffer(int BufferLen);

void setup() {
	// put your setup code here, to run once:
	InitMax7219();

	setTime(12, 59, 0, 23, 7, 2016);

	unsigned char ConnectStr[] = { "Connecting.\0" };

	WiFi.begin(ssid, pass);

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
	my_delay_ms(100);
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
int packet_delay = 0;

time_t getNtpTime()
{
	IPAddress timeServerIP;

	Serial.println("Transmit NTP Request");
	WiFi.hostByName(ntpServerName, timeServerIP);
	sendNTPpacket(timeServerIP); // send an NTP packet to a time server
	packet_delay = 1500;		 // wait to see if a reply is available

	return 0;
}

void my_delay_ms(int msec)
{
	uint32_t delay_val = msec;
	uint32_t endWait = millis();
	uint32_t beginWait = endWait;
	while (endWait - beginWait < delay_val) 
	{
		int size = udp.parsePacket();
		if (packet_delay > 0)
		{
			if (size >= NTP_PACKET_SIZE)
			{
				Serial.println("Receive NTP Response");
				udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
				unsigned long secsSince1900;
				// convert four bytes starting at location 40 to a long integer
				secsSince1900 = (unsigned long)packetBuffer[40] << 24;
				secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
				secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
				secsSince1900 |= (unsigned long)packetBuffer[43];

				time_t tm = secsSince1900 - 2208988800UL + timeZone;
				setTime(tm);
				packet_delay = 0;
			}
		}
		delay(1);
		endWait = millis();
	}
	if (packet_delay > 0) 
		packet_delay -= msec;
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
