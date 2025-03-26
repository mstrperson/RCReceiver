//
// Created by Jason Cox on 3/17/25.
//

#include "RCChannel.h"
#include <Arduino.h>
#include <string>
#include <ostream>
#include <sstream>
#include <stdio.h>

/// Constructor for the Abstract RCChannel class
/// @param pin PWM enabled digital pin that this channel is connected to.
RCChannel::RCChannel(int pin)
{
  pinMode(pin, INPUT);
  this->pin = pin;
  this->pwmMin = 2000;
  this->pwmMax = 0;
  this->zeroMin = 2000;
  this->zeroMax = 0;
}

/// use `pulseIn(pin, HIGH, 25000)` to read the raw PWM duty-cycle on this channel
int RCChannel::raw()
{
  int reading = pulseIn(pin, HIGH, 25000);
  return reading;
}

/// update the current `zeroMin` and `zeroMax` fields if the current raw PWM duty cycle does not fall within that range.
void RCChannel::calibrateZero()
{
  int val = raw();
  if(val > zeroMax) zeroMax = val;
  if(val < zeroMin) zeroMin = val;
}

/// update the current `pwmMin` and `pwmMax` fields if the current raw PWM duty cycle does not fall within that range.
void RCChannel::calibrateExtremes()
{
  int val = raw();
  if(val > pwmMax) pwmMax = val;
  if(val < pwmMin) pwmMin = val;
}

/// manually set the PWM calibration fields of this channel
///@param pwmMin minimum value for PWM duty cycle that this channel reports.
///@param pwmMax maximum value for PWM duty cycle that this channel reports.
///@param zeroMin minimum value for PWM duty cycle that corresponds to zero input.
///@param zeroMax maximum value for PWM duty cycle that corresponds to zero input.
void RCChannel::setCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  this->zeroMin = zeroMin;
  this->zeroMax = zeroMax;
  this->pwmMin = pwmMin;
  this->pwmMax = pwmMax;
}

/// take the raw PWM duty cycle read from this Channel
/// if the value is less than `zeroMax` then return 0.0
/// otherwise map the PWM from the calibrated range int the interval [0, 1024]
/// then return that value divided by 1024.0.
double ThrottleChannel::read()
{
  double pwm = this->raw();
  if(pwm <= this->zeroMax) return 0.0;

  return map(pwm, pwmMin, pwmMax, 0, 1024) / 1024.0;
}

/// Is the raw PWM duty cycle of this Channel larger than `zeroMax`?
bool ToggleChannel::isOn()
{
  return this->raw() > this->zeroMax;
}

/// take the raw PWM duty cycle read from this Channel
/// if the value is in the intervale [`zeroMin`, `zeroMax`] then return 0.0
/// otherwise map the PWM from the calibrated range int the interval [-512, 512]
/// then return that value divided by 512.0.
double AxisChannel::read()
{
  double pwm = this->raw();
  if(pwm >= this-> zeroMin && pwm <= this->zeroMax)
    return 0.0;

  return map(pwm, pwmMin, pwmMax, -512, 512) / 512.0;
}

/// get this channel's calibration data in JSON format.
std::string RCChannel::saveCalibration()
{
  std::stringstream output;
  output  << "{\"pwmMin\":" << this->pwmMin << ","
          << "\"pwmMax\":" << this->pwmMax << ","
          << "\"zeroMin\":" << this->zeroMin << ","
          << "\"zeroMax\":" << this->zeroMax << "}";
  return output.str();
}