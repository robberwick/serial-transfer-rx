#include <Arduino.h>
#include <SerialTransfer.h>
#include <SoftwareSerial.h>

struct MotorSpeeds {
  int8_t left;
  int8_t right;
} motorSpeeds;

struct SensorData {
  float x;
  float y;
  float z;
} sensorData;

SerialTransfer myTransfer;
SoftwareSerial Serial1(10, 11); // RX, TX

float getRandom() {
  return (random(1, 2000000) - 1000000) / 100.0;
}

void setup()
{
  Serial.begin(115200);
  Serial1.begin(57600);
  myTransfer.begin(Serial1);
  
}

void loop()
{
  sensorData.x = getRandom();
  sensorData.y = getRandom();
  sensorData.z = getRandom();

  // use this variable to keep track of how many
  // bytes we're stuffing in the transmit buffer
  uint16_t sendSize = 0;

  ///////////////////////////////////////// Stuff buffer with struct
  myTransfer.txObj(sensorData, sizeof(sensorData), sendSize);
  sendSize += sizeof(sensorData);

  ///////////////////////////////////////// Send buffer
  myTransfer.sendData(sendSize);
  delay(100);

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