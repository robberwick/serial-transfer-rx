#include <Arduino.h>
#include <SerialTransfer.h>
#include <SoftwareSerial.h>

SerialTransfer myTransfer;
SoftwareSerial Serial1(10, 11); // RX, TX

void setup()
{
  Serial.begin(115200);
  Serial1.begin(57600);
  myTransfer.begin(Serial1);
}

void loop()
{
  if(myTransfer.available())
  {
    Serial.println("New Data");
    for(byte i = 0; i < myTransfer.bytesRead; i++)
      Serial.write(myTransfer.rxBuff[i]);
    Serial.println();
  }
  else if(myTransfer.status < 0)
  {
    Serial.print("ERROR: ");
    Serial.println(myTransfer.status);
  }
}