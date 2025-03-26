#include "Arduino.h"
#include "PressureCurve.h"

PressureCurve::PressureCurve(int extractionLength, int frameRate) {
  //_pressurePointsArray = new int[extractionLength];
  for (int i=0; i<extractionLength; i++) {
    _pressurePointsArray[i] = 0;
  }
  _extractionLength = extractionLength;
  _frameRate = frameRate;
  calculateDefaultPressureCurve();
}

void PressureCurve::calculatePressureCurve(int pressureKeyframes[3000][2], int numKeyframes) {
}

// need to make this better later. right now, it just creates a reasonably good enough pressure curve. 
void PressureCurve::calculateDefaultPressureCurve(int id = 0) {

if (id == 0) {}
  // populate the pressure data array
  for (int i = 0; i < _extractionLength; i++) {
    if (i < 5 * _frameRate) { // 5 sec
      _pressurePointsArray[i] = map(i, 0, 5 * _frameRate, 0, 30); //
    } else if (i < 10 * _frameRate) { // 
      _pressurePointsArray[i] = map(i, 5 * _frameRate, 10 * _frameRate, 30, 90); // 
    } else if (i < 18 * _frameRate) { // 
      _pressurePointsArray[i] = map(i, 10 * _frameRate, 18 * _frameRate, 90, 90); // 
    } else if (i < 35 * _frameRate) { 
      _pressurePointsArray[i] = map(i, 18 * _frameRate, 35 * _frameRate, 90, 0); //
    } else {
      _pressurePointsArray[i] = 0; // Remainder with 0
    }
  }
}

if (id == 1)
  // populate the pressure data array
  for (int i = 0; i < _extractionLength; i++) {
    if (i < 4 * _frameRate) { // 5 sec
      _pressurePointsArray[i] = map(i, 0, 4 * _frameRate, 0, 100); //
    } else if (i < 30 * _frameRate) { // 
      _pressurePointsArray[i] = map(i, 4 * _frameRate, 30 * _frameRate, 100, 0); // 
    } else {
      _pressurePointsArray[i] = 0; // Remainder with 0
    }
  }
}

void PressureCurve::startExtraction(int startTime) {
  _startTime = startTime;
}

bool PressureCurve::isExtractionFinished(int currentTime) {
  int totalExtractionDuration = _extractionLength * 1000 / _frameRate;
  if(currentTime - _startTime > totalExtractionDuration)
    return true;
  else
    return false;
}

int PressureCurve::getPressurePoint(int currentTime) {
  // calculate arrayIndex;
  int elapsedTime = currentTime - _startTime; // elapsed time in milliseconds
  int frame = elapsedTime * _frameRate / 1000; 

  if (frame >= 0 && frame < _extractionLength) {
    return _pressurePointsArray[frame];
  }
  else {
    return 0;
  }
  
}