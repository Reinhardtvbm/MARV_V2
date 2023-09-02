#pragma once

#include <stdint.h>
#include "sensor.h"

/// One sensor in the sensor array
class SensorArray {
    public:
        SensorArray(float filter_constant, float filter_constant_pins, int* pins); 
        
        void calibrate();
        void update();
        float get_position();

    private: 
        float position, filter_constant;
        Sensor* sensors[7];
        double mins[7] = {3000,3000,3000,3000,3000,3000,3000};
        double maxs[7] = {0,0,0,0,0,0,0};
};