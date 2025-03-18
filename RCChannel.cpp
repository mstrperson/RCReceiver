//
// Created by Jason Cox on 3/17/25.
//

#include "RCChannel.h"
#include <Arduino.h>
#include <string>
#include <ostream>
#include <sstream>
#include <stdio.h>

RCChannel::RCChannel(int pin)
{
  pinMode(pin, INPUT);
  this->pin = pin;
  this->pwmMin = 2000;
  this->pwmMax = 0;
  this->zeroMin = 2000;
  this->zeroMax = 0;
}

int RCChannel::raw()
{
  int reading = pulseIn(pin, HIGH, 25000);
  return reading;
}

void RCChannel::calibrateZero()
{
  int val = raw();
  if(val > zeroMax) zeroMax = val;
  if(val < zeroMin) zeroMin = val;
}

void RCChannel::calibrateExtremes()
{
  int val = raw();
  if(val > pwmMax) pwmMax = val;
  if(val < pwmMin) pwmMin = val;
}

void RCChannel::setCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax)
{
  this->zeroMin = zeroMin;
  this->zeroMax = zeroMax;
  this->pwmMin = pwmMin;
  this->pwmMax = pwmMax;
}

double ThrottleChannel::read()
{
  double pwm = this->raw();
  if(pwm <= this->zeroMax) return 0.0;

  return map(pwm, pwmMin, pwmMax, 0, 1024) / 1024.0;
}

bool ToggleChannel::isOn()
{
  return this->raw() > this->zeroMax;
}

double AxisChannel::read()
{
  double pwm = this->raw();
  if(pwm >= this-> zeroMin && pwm <= this->zeroMax)
    return 0.0;

  return map(pwm, pwmMin, pwmMax, -512, 512) / 512.0;
}

std::string RCChannel::saveCalibration()
{
  std::stringstream output;
  output  << "{\"pwmMin\":" << this->pwmMin << ","
          << "\"pwmMax\":" << this->pwmMax << ","
          << "\"zeroMin\":" << this->zeroMin << ","
          << "\"zeroMax\":" << this->zeroMax << "}";
  return output.str();
}