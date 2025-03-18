//
// Created by Jason Cox on 3/17/25.
//

#ifndef RCCHANNEL_H
#define RCCHANNEL_H

#include <stdio.h>
#include <string>
class RCChannel
{
  int pin;
  protected:
    int pwmMin;
    int pwmMax;
    int zeroMin;
    int zeroMax;

  public:
    RCChannel(int pin);
    int raw();
    void calibrateZero();
    void calibrateExtremes();
    void setCalibration(int pwmMin, int pwmMax, int zeroMin, int zeroMax);
    std::string saveCalibration();
};

class ThrottleChannel : public RCChannel
{
  public:
    ThrottleChannel(int pin) : RCChannel(pin) { }
    /// read the PWM as a value between 0 and 1.
    double read();
};

class ToggleChannel : public RCChannel
{
  public:
    ToggleChannel(int pin) : RCChannel(pin) { }
    // read the PWM as HIGH or LOW
    bool isOn();
};

class AxisChannel : public RCChannel
{
  public:
    AxisChannel(int pin) : RCChannel(pin) { }
    /// Read the PWM as a value between -1 and 1;
    double read();
};




#endif //RCCHANNEL_H
