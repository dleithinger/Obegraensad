#ifndef PressureCurve_h
#define PressureCurve_h

#define DEFAULT_EXTRACTIONLENGTH 1000
#define DEFAULT_FRAMERATE 20

#include "Arduino.h"

class PressureCurve {
  public:
    PressureCurve(int extractionLength = DEFAULT_EXTRACTIONLENGTH, int frameRate = DEFAULT_FRAMERATE);
    void calculateDefaultPressureCurve(int id);
    
    void startExtraction(int startTime); // time in milliseconds since program started
    int getPressurePoint(int currentTime); // time in milliseconds since program started
    bool isExtractionFinished(int currentTime); // time in milliseconds since program started

    int _extractionLength; // extrationLength in frames
    int _pressurePointsArray[DEFAULT_EXTRACTIONLENGTH]; 
    int _frameRate;
    int _startTime;
  private:
    void calculatePressureCurve(int pressureKeyframes[DEFAULT_EXTRACTIONLENGTH][2], int numKeyframes); // each pressure keyframes has a pressure and a timestamp

};

#endif