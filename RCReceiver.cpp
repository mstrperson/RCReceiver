#include "RCReceiver.h"
#include <Arduino.h>
#include <stdio.h>
#include <ostream>
#include <sstream>
#include <string>

/// Initialize an RCReciever with up to 6 channels
/// if any channel is not needed, pass -1 to its parameter.
/// @param throPin ThrottleChannel - left stick Y position
/// @param ailePin AxisChannel - right stick X axis
/// @param elevPin AxisChannel - right stick Y axis
/// @param ruddPin AxisChannel - left stick X axis
/// @param gearPin ToggleChannel
/// @param aux1Pin ToggleChannel
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

/// de-allocate memory for each of the RCChannels
RCReceiver::~RCReceiver() {
    delete thro;
    delete aile;
    delete elev;
    delete rudd;
    delete gear;
    delete aux1;
}

/// Get the Throttle value as a double [0, 1]
double RCReceiver::getThro()
{
  if(thro == nullptr)
    return 0;
  return thro->read();
}

/// Get the right stick x-axis value as a double [-1, 1]
double RCReceiver::getAile()
{
  if(aile == nullptr)
    return 0;
  return aile->read();
}

/// Get the right stick y-axis value as a double [-1, 1]
double RCReceiver::getElev()
{
  if(elev == nullptr)
    return 0;
  return elev->read();
}

/// Get the left stick x-axis value as a double [-1, 1]
double RCReceiver::getRudd()
{
  if(rudd == nullptr)
    return 0;
  return rudd->read();
}

/// Get the gear toggle as a boolean
bool RCReceiver::getGear()
{
  if(gear == nullptr)
    return false;
  return gear->isOn();
}

/// Get the Aux1 toggle as a boolean
bool RCReceiver::getAux1()
{
  if(aux1 == nullptr)
    return false;
  return aux1->isOn();
}

/// Take one reading used to Calibrate the zero input for each initialized Channel.
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

/// Take one reading used to Calibrate the extremes of each initialized Channel
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

/// Get the currently configured Calibration in JSON format.
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

/// Manually set the ThrottleChannel calibration for left stick y-axis.
/// Theoretically, zeroMin and pwmMin should be equal for this axis.
/// @param pwmMin minimum value for PWM duty cycle that this channel reports.
/// @param pwmMax maximum value for PWM duty cycle that this channel reports.
/// @param zeroMin minimum value for PWM duty cycle that corresponds to zero input.
/// @param zeroMax maximum value for PWM duty cycle that corresponds to zero input.
void RCReceiver::setThroCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(thro == nullptr) return;
  thro->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}

/// Manually set the AxisChannel calibration for right stick x-axis.
/// @param pwmMin minimum value for PWM duty cycle that this channel reports.
/// @param pwmMax maximum value for PWM duty cycle that this channel reports.
/// @param zeroMin minimum value for PWM duty cycle that corresponds to zero input.
/// @param zeroMax maximum value for PWM duty cycle that corresponds to zero input.
void RCReceiver::setAileCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(aile == nullptr) return;
  aile->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}

/// Manually set the AxisChannel calibration for right stick y-axis.
/// @param pwmMin minimum value for PWM duty cycle that this channel reports.
/// @param pwmMax maximum value for PWM duty cycle that this channel reports.
/// @param zeroMin minimum value for PWM duty cycle that corresponds to zero input.
/// @param zeroMax maximum value for PWM duty cycle that corresponds to zero input.
void RCReceiver::setElevCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(elev == nullptr) return;
  elev->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}

/// Manually set the AxisChannel calibration for left stick x-axis.
/// @param pwmMin minimum value for PWM duty cycle that this channel reports.
/// @param pwmMax maximum value for PWM duty cycle that this channel reports.
/// @param zeroMin minimum value for PWM duty cycle that corresponds to zero input.
/// @param zeroMax maximum value for PWM duty cycle that corresponds to zero input.
void RCReceiver::setRuddCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(rudd == nullptr) return;
  rudd->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}

/// Manually set the ToggleChannel calibration for Gear switch.
/// Theoretically zeroMin should equal pwmMin, and zeroMax can be anything less than pwmMax.
/// @param pwmMin minimum value for PWM duty cycle that this channel reports.
/// @param pwmMax maximum value for PWM duty cycle that this channel reports.
/// @param zeroMin minimum value for PWM duty cycle that corresponds to zero input.
/// @param zeroMax maximum value for PWM duty cycle that corresponds to zero input.
void RCReceiver::setGearCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(gear == nullptr) return;
  gear->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}

/// Manually set the ToggleChannel calibration for Aux1 switch.
/// Theoretically zeroMin should equal pwmMin, and zeroMax can be anything less than pwmMax.
///@param pwmMin minimum value for PWM duty cycle that this channel reports.
///@param pwmMax maximum value for PWM duty cycle that this channel reports.
///@param zeroMin minimum value for PWM duty cycle that corresponds to zero input.
///@param zeroMax maximum value for PWM duty cycle that corresponds to zero input.
void RCReceiver::setAux1Calibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  if(aux1 == nullptr) return;
  aux1->setCalibration(pwmMin, pwmMax, zeroMin, zeroMax);
}