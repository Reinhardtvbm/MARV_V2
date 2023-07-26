#pragma once

#include <stdint.h>

/// One sensor in the sensor array
class Sensor {
    public:
        Sensor(int pin, float filter_constant); 
        
        void calibrate();
        void update();
        uint16_t get_value();
        uint16_t get_raw_value();

    private: 
        int pin;
        uint16_t value, raw_value, green, cost;
        float filter_constant;
};
