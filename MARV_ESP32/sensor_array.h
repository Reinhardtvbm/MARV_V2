#pragma once

#include "sensor.h"
#include <Arduino.h>

/// One sensor in the sensor array
class SensorArray {
    public:
        SensorArray(float filter_constant, float filter_constant_pins, int* pins); 
        
<<<<<<< HEAD
        void calibrate();
        void _update();
        float get_position();

    private: 
        float _position, filter_constant;
        Sensor** sensors = NULL;
        float* mins = NULL;
        float* maxs = NULL;
=======
        void calibrate(Motor* motor_left, Motor* motor_right);
        void update();
        float get_position();

    private: 
        float position, filter_constant;
        Sensor* sensors[7];
        double mins[7] = {3000,3000,3000,3000,3000,3000,3000};
        double maxs[7] = {0,0,0,0,0,0,0};
>>>>>>> 2fec36058834f2fc45ccc9976220dbed31b8e519
};
