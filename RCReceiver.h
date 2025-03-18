#ifndef RCRECIEVER_LIBRARY_H
#define RCRECIEVER_LIBRARY_H

#include "RCChannel.h"
#include <string>
#include <stdio.h>

class RCReceiver
{
    ThrottleChannel*     thro;
    AxisChannel*         aile;
    AxisChannel*         elev;
    AxisChannel*         rudd;
    ToggleChannel*       gear;
    ToggleChannel*       aux1;

public:
    RCReceiver(int throPin, int ailePin, int elevPin, int ruddPin, int gearPin, int aux1Pin);
    ~RCReceiver();

    double getThro();
    double getAile();
    double getElev();
    double getRudd();
    bool getGear();
    bool getAux1();

    void calibrateExtremes();
    void calibrateZero();

    int getThroRaw() { if(thro == nullptr) return 0; else return thro->raw(); };
    int getAileRaw() { if(aile == nullptr) return 0; else return aile->raw(); };
    int getElevRaw() { if(elev == nullptr) return 0; else return elev->raw(); };
    int getRuddRaw() { if(rudd == nullptr) return 0; else return rudd->raw(); };
    int getAux1Raw() { if(aux1 == nullptr) return 0; else return aux1->raw(); };
    int getGearRaw() { if(gear == nullptr) return 0; else return gear->raw(); };

    std::string saveCalibration();
};

#endif //RCRECIEVER_LIBRARY_H