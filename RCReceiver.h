#ifndef RCRECIEVER_LIBRARY_H
#define RCRECIEVER_LIBRARY_H

class RCReceiver
{
    int* pwmPins;
    int channelCount;
    double (*MapPWMOutput)(int);

    double defaultMap(int pwm);

public:
    explicit RCReceiver(int pwmPins[], int channelCount);
    ~RCReceiver();

    [[nodiscard]] int getChannelCount() const { return channelCount; }
    int readPWMRaw(int channel);
    double readChannel(int channel);
    void setPWMZeroRange(int start, int end);
    void setMap(double (*mappingFunction)(int));
};

#endif //RCRECIEVER_LIBRARY_H