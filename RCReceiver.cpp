#include "RCReceiver.h"
#include <Arduino.h>

double RCReceiver::defaultMap(int pwm)
{
    if (1500 <= pwm && pwm <= 1600)
        return 0;
    return (pwm - 1550.0) / 1550.0;
}

RCReceiver::RCReceiver(int pwmPins[], int channelCount)
{
    this->pwmPins = pwmPins;
    this->channelCount = channelCount;
    for (int i = 0; i < this->channelCount; i++) {
        pinMode(pwmPins[i], INPUT);
    }
}

RCReceiver::~RCReceiver() {
    delete[] pwmPins;
}

int RCReceiver::readPWMRaw(int channel) {
    int reading = pulseIn(pwmPins[channel], HIGH, 25000);
    return reading;
}

double RCReceiver::readChannel(int channel){
    int reading = readPWMRaw(channel);

    if (MapPWMOutput != nullptr)
        return MapPWMOutput(reading);

    return defaultMap(reading);
}

void RCReceiver::setMap(double(*mappingFunction)(int)) {
    MapPWMOutput = mappingFunction;
}

