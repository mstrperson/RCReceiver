#include "RCReceiver.h"

RCReceiver* receiver;

void setup()
{
  Serial.begin(9600);
  receiver = new RCReceiver(new int[6] { 3, 5, 6, 9, 10, 11 });
}

void loop()
{
  for(int i = 0; i < 6; i++)
  {
    Serial.print(receiver->readPWMRaw(i));
    Serial.print(",");
  }

  Serial.println();
}