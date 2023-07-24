#pragma once

#include <stdint.h>

class Sensor {
    public:
        float line_position_raw;
        float line_position;

        void update();
        void calibrate();

    private: 
        int sensor_pins[7];
        float sensor_values_raw[7];
        float sensor_values[7];

        uint16_t white_values[7];
        uint16_t line_values[7];
}
