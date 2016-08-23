
#include <Time.h>
#include <TimeLib.h>

#include <LedControl.h>

const int numDevices = 4;      // number of MAX7219s used
LedControl lc = LedControl(12,11,10,numDevices);

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

void loop() {
  // put your main code here, to run repeatedly:
  UpdateTime();
  LoadMessage(scrollText);
  LoadDisplayBuffer();
  SendDisplayBuffer();
  delay(100);
}

void UpdateTime()
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


