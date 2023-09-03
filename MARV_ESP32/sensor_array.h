#pragma once

#include "sensor.h"
#include <Arduino.h>

/// One sensor in the sensor array
class SensorArray {
    public:
        SensorArray(float filter_constant, float filter_constant_pins, int* pins); 
        
        void calibrate();
        void _update();
        float get_position();

    private: 
        float _position, filter_constant;
        Sensor** sensors = NULL;
        float* mins = NULL;
        float* maxs = NULL;
};
