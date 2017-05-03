
#if defined(ESP8266)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 14
#define BMP_MISO 12
#define BMP_MOSI 13 
#define BMP_CS 15

Adafruit_BMP280 bme; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
boolean Use_bmp280;
String bmp280_str;
float Temperature, Pressure, Altitude;
int T_samples, P_samples;

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <Time.h>
#include <TimeLib.h>

// Access point credentials
String ap_ssid("LED_Matrix");
const char *ap_password = "12345678";

String sta_ssid("BST");	//  your network SSID (name)
String sta_pass;		        // your network password

unsigned int localPort = 2390;      // local port to listen for UDP packets

const char* ntpServerName = "ntp.pagasa.dost.gov.ph";
IPAddress timeServerIP(121, 58, 193, 100);	//IP address of "ntp.pagasa.dost.gov.ph"

// NTP time stamp is in the first 48 bytes of the message
const int NTP_PACKET_SIZE = 48; 

//buffer to hold incoming and outgoing packets
byte packetBuffer[NTP_PACKET_SIZE]; 

//A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

const int numDevices = 4;      // number of MAX7219s used
const int SPI_CS = 12;
const int SPI_MOSI = 13;
const int SPI_CLK = 14;

char scrollText[] = "00:00:00am \0";
//                   01234567890

extern int LoadPos;

void InitMax7219();
void UpdateTime(void);
int LoadMessage(const char *message);
void ResetScrollPos(void);
int LoadDisplayBuffer(int BufferLen);
void sendNTPpacket(IPAddress& address);

void LoadDisplayBMP280(void);

/*///////////////////////////////////////////////////////////////////////////*/

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);

	IPAddress local_IP(192, 168, 25, 1);
	IPAddress gateway(192, 168, 25, 1);
	IPAddress subnet(255, 255, 255, 0);

	WiFi.softAPConfig(local_IP, gateway, subnet);

	String macAddr = WiFi.softAPmacAddress();
	ap_ssid += '_' + macAddr.substring(12, 14) + macAddr.substring(15);
	WiFi.softAP(ap_ssid.c_str(), ap_password);

	if (WiFi.SSID().length()>0)
	{
		sta_ssid = WiFi.SSID();
		sta_pass = WiFi.psk();
	}

	delay(1000);

	if (!bme.begin()) 
	{
		Serial.println("Could not find a valid BMP280 sensor, check wiring!");
		Use_bmp280 = false;
	}
	else
	{
		Temperature = bme.readTemperature();
		T_samples = 1;
		Pressure = bme.readPressure();
		P_samples = 1;
		Altitude = bme.readAltitude(SENSORS_PRESSURE_SEALEVELHPA);
		Use_bmp280 = true;
	}

	InitMax7219();

	DS3231_setup();

	String ConnectStr("Connecting... ");

	ResetScrollPos();
	int Len = LoadMessage(ConnectStr.c_str());
	for (int i=0; i<200; i++)
	{
		if (WiFi.status() == WL_CONNECTED)
		{
			Serial.println(F("WiFi connected"));
			Serial.println(F("IP address: "));
			Serial.println(WiFi.localIP());
			break;
		}
		LoadDisplayBuffer(LoadPos);
		delay(50);
	}
	InitMax7219();

	ResetScrollPos();

	Serial.println(F("Starting UDP"));
	udp.begin(localPort);
	Serial.print(F("Local port: "));
	Serial.println(udp.localPort());

	IPAddress addr;
	if (WiFi.hostByName(ntpServerName, addr))
	{
		timeServerIP = addr;
	}

	setSyncProvider(getNtpTime);

	webserver_setup();
}

void loop() {
	// put your main code here, to run repeatedly:
	UpdateTime();
	if (LogoOn())
	{
		String Timestr(scrollText);
		if (LoadDisplayBuffer(LoadPos) == 0)
		{
			LoadDisplayBMP280();
		}
		else
		{
			Temperature += bme.readTemperature();
			T_samples++;
			Pressure += bme.readPressure();
			P_samples++;
		}
		Timestr += bmp280_str;
		LoadMessage(Timestr.c_str());
		my_delay_ms(50);
	}
	else
	{
		LoadMessage(scrollText);
		LoadDisplayBuffer(LoadPos);
		my_delay_ms(50);
	}
}

/*///////////////////////////////////////////////////////////////////////////*/

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
	Serial.println(F("Transmit NTP Request"));
	sendNTPpacket(timeServerIP); // send an NTP packet to a time server

	return 0;
}

void my_delay_ms(int msec)
{
	uint32_t delay_val = msec;
	uint32_t endWait = millis();
	uint32_t beginWait = endWait;
	while (endWait - beginWait < delay_val) 
	{
		webserver_loop();

		int size = udp.parsePacket();
		if (packet_delay > 0)
		{
			if (size >= NTP_PACKET_SIZE)
			{
				Serial.println(F("Receive NTP Response"));
				udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
				unsigned long secsSince1900;
				// convert four bytes starting at location 40 to a long integer
				secsSince1900 = (unsigned long)packetBuffer[40] << 24;
				secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
				secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
				secsSince1900 |= (unsigned long)packetBuffer[43];

				time_t tm = secsSince1900 - 2208988800UL + timeZone;
				setTime(tm);
				DS3231_setTime(tm);
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
void sendNTPpacket(IPAddress& address)
{
	if (WiFi.status() == WL_CONNECTED)
	{
		Serial.println(F("sending NTP packet..."));
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

		packet_delay = 1500;		 // wait to see if a reply is available
	}
}


void LoadDisplayBMP280(void)
{
	if (Use_bmp280)
	{
		if (T_samples > 0)
		{
			bmp280_str = String(Temperature / T_samples, 1);
		}
		else
		{
			bmp280_str = String(bme.readTemperature(), 1);
		}
		Temperature = 0.0f;
		T_samples = 0;
		bmp280_str += String("C ");
		if (P_samples > 0)
		{
			bmp280_str += String(Pressure / (P_samples * 100), 2);
		}
		else
		{
			bmp280_str += String(bme.readPressure() / 100.0, 2);
		}
		Pressure = 0.0f;
		P_samples = 0;
		bmp280_str += String("hPa ");
	}
	else
	{
		bmp280_str = String(" No BMP280 detected! ");
	}
}
