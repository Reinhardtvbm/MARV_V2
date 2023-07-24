#include "sensor.h"
#include <Arduino.h>

void Sensor::update() {
    float sum = 0.0;
    float weighted = 0.0;

    for (int i = 0; i < 7; i++) {
        sensor_values_raw[i] = (float)analogRead(self.sensor_pins[i]);
        sensor_values[i] += 0.8 * sensor_values[i] + 0.2 * sensor_values_raw[i];

        sum += sensor_values[i];
        weighted += sensor_values[i] * i * 1000.0;
    }

    self.line_position_raw = avg / sum;
    self.line_posision = 0.5 * self.line_posision + 0.5 * self.line_position_raw;
}

void Sensor::calibrate() {
    float sensor_values[7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    for (int sample = 0; sample < 100; sample++) { 
        for (int i = 0; i < 7; i++) {
            sensor_values[i] = (float)analogRead(self.sensor_pins[i]);

            if (self.white_values[i] < sensor_values[i]) {
                self.white_values[i] = sensor_values[i];
            }

            if (self.line_values[i] > sensor_values[i]) {
                self.line_values[i] = sensor_values[i];
            }
        }
    }
}
