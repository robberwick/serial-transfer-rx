#include <Arduino.h>
#include <SerialTransfer.h>
#include <SoftwareSerial.h>

struct MotorSpeeds {
  uint8_t left;
  uint8_t right;
} motorSpeeds;

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
    uint8_t recSize = 0;
    myTransfer.rxObj(motorSpeeds, sizeof(motorSpeeds), recSize);
    Serial.print(motorSpeeds.left);
    Serial.print(' ');
    Serial.print(motorSpeeds.right);
    Serial.println();
  }
  else if(myTransfer.status < 0)
  {
    Serial.print("ERROR: ");
    Serial.println(myTransfer.status);
  }
}