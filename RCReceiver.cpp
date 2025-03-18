#include "RCReceiver.h"
#include <Arduino.h>
#include <stdio.h>
#include <ostream>
#include <sstream>
#include <string>

RCReceiver::RCReceiver(int throPin, int ailePin, int elevPin, int ruddPin, int gearPin, int aux1Pin)
{
  if(throPin != -1)
    thro = new ThrottleChannel(throPin);
  if(ailePin != -1)
    aile = new AxisChannel(ailePin);
  if(elevPin != -1)
    elev = new AxisChannel(elevPin);
  if(ruddPin != -1)
    rudd = new AxisChannel(ruddPin);
  if(gearPin != -1)
    gear = new ToggleChannel(gearPin);
  if(aux1Pin != -1)
    aux1 = new ToggleChannel(aux1Pin);
}

RCReceiver::~RCReceiver() {
    delete thro;
    delete aile;
    delete elev;
    delete rudd;
    delete gear;
    delete aux1;
}

double RCReceiver::getThro()
{
  if(thro == nullptr)
    return 0;
  return thro->read();
}

double RCReceiver::getAile()
{
  if(aile == nullptr)
    return 0;
  return aile->read();
}

double RCReceiver::getElev()
{
  if(elev == nullptr)
    return 0;
  return elev->read();
}

double RCReceiver::getRudd()
{
  if(rudd == nullptr)
    return 0;
  return rudd->read();
}

bool RCReceiver::getGear()
{
  if(gear == nullptr)
    return false;
  return gear->isOn();
}

bool RCReceiver::getAux1()
{
  if(aux1 == nullptr)
    return false;
  return aux1->isOn();
}

void RCReceiver::calibrateZero()
{
  if(thro != nullptr)
    thro->calibrateZero();
  if(aile != nullptr)
    aile->calibrateZero();
  if(elev != nullptr)
    elev->calibrateZero();
  if(rudd != nullptr)
    rudd->calibrateZero();
  if(gear != nullptr)
    gear->calibrateZero();
  if(aux1 != nullptr)
    aux1->calibrateZero();
}

void RCReceiver::calibrateExtremes()
{
  if(thro != nullptr)
    thro->calibrateExtremes();
  if(aile != nullptr)
    aile->calibrateExtremes();
  if(elev != nullptr)
    elev->calibrateExtremes();
  if(rudd != nullptr)
    rudd->calibrateExtremes();
  if(gear != nullptr)
    gear->calibrateExtremes();
  if(aux1 != nullptr)
    aux1->calibrateExtremes();
}

std::string RCReceiver::saveCalibration()
{
  std::stringstream output;
  output << "{" << std::endl
         << "\"thro\":" << (thro == nullptr ? "null" : thro->saveCalibration()) << "," << std::endl
         << "\"aile\":" << (aile == nullptr ? "null" : aile->saveCalibration()) << "," << std::endl
         << "\"elev\":" << (elev == nullptr ? "null" : elev->saveCalibration()) << "," << std::endl
         << "\"rudd\":" << (rudd == nullptr ? "null" : rudd->saveCalibration()) << "," << std::endl
         << "\"gear\":" << (gear == nullptr ? "null" : gear->saveCalibration()) << "," << std::endl
         << "\"aux1\":" << (aux1 == nullptr ? "null" : aux1->saveCalibration()) << "," << std::endl
         << "}";
  return output.str();
}

void RCReceiver::setThroCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(thro == nullptr) return;
  thro->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}
void RCReceiver::setAileCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(aile == nullptr) return;
  aile->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}
void RCReceiver::setElevCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(elev == nullptr) return;
  elev->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}
void RCReceiver::setRuddCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(rudd == nullptr) return;
  rudd->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}
void RCReceiver::setGearCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(gear == nullptr) return;
  gear->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}
void RCReceiver::setAux1Calibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(aux1 == nullptr) return;
  aux1->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}