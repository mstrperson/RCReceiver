#include "RCReceiver.h"
#include <string>

#define THRO 14
#define AILE 17
#define ELEV 21
#define RUDD 24
#define GEAR 29
#define AUX1 32

RCReceiver* receiver;

void setup()
{
  Serial.begin(9600);
  receiver = new RCReceiver(THRO, AILE, ELEV, RUDD, GEAR, AUX1);
  delay(10000);
  calibrate();
}

void calibrate()
{
  Serial.println("Calibrating Zeros...");
  int startMillis = millis();
  while(millis() - startMillis < 10000)
  {
    receiver->calibrateZero();
    if(millis() % 50 == 0)
      Serial.print(".");
  }

  Serial.println("Zeros calibrated");
  Serial.println("Calibrating Extremes...");
  startMillis = millis();
  while(millis() - startMillis < 10000)
  {
    receiver->calibrateExtremes();
    if(millis() % 50 == 0)
      Serial.print(".");
  }
  Serial.println("Extremes calibrated");
  Serial.println("Calibration complete");

  Serial.println(receiver->saveCalibration().c_str());
  delay(25000);
}

double thro = 0,
       aile = 0,
       elev = 0,
       rudd = 0;

bool gear = false,
     aux1 = false;


void loop()
{
  thro = receiver->getThro();
  aile = receiver->getAile();
  elev = receiver->getElev();
  rudd = receiver->getRudd();
  gear = receiver->getGear();
  aux1 = receiver->getAux1();

  if(aux1)
    calibrate();

  Serial.print("Thro: ");
  Serial.print(thro);
  Serial.print(" Aile: ");
  Serial.print(aile);
  Serial.print(" Elev: ");
  Serial.print(elev);
  Serial.print(" Rudd: ");
  Serial.print(rudd);
  Serial.println();
  delay(5000);
}