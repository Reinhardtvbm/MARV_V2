#include "sensor_array.h"

#include <Arduino.h>

SensorArray::SensorArray(float filter_constant, float filter_constant_pins, int* pins) {
    for (int i = 0; i < 7; i++) {
        sensors[i] = new Sensor(pins[i], filter_constant_pins);
    }

    this->filter_constant = filter_constant;
}
        
void SensorArray::calibrate() {
    uint32_t start = millis();

    while (millis() - start < 20000) {
        for (int i = 0; i < 7; i++) {
            sensors[i]->update();
            uint16_t value = sensors[i]->get_value();

            if (value > maxs[i]) {
                maxs[i] = value;
            } else if (value < mins[i]) {
                mins[i] = value;
            }
        }  

        for (int i = 0; i < 7; i++) {
            Serial.print(mins[i]);
            Serial.print('\t');
        }

        Serial.println(' ');

        for (int i = 0; i < 7; i++) {
            Serial.print(maxs[i]);
            Serial.print('\t');
        }

        Serial.println(' ');
        Serial.println((millis() - start) / 300);

    }

    Serial.println("Starting now...");
}

void SensorArray::update() {
    double sum = 0;
    double avg = 0;

    for (int i = 0; i < 7; i++) {
        sensors[i]->update();
        double value = (double)(sensors[i]->get_value());
        
        double cost = (value - mins[i]) / (maxs[i] - mins[i]);

        if (cost < 0) {
            cost = 1.0 + cost;
        } else {
            cost = 1.0 - cost;
        }

        cost *= cost;
        
        if (cost < 0.4) {
            cost = 0.0;
        }

        avg += cost * (i * 1000);
        sum += cost;
    }

    if (sum != 0) { 
        float raw_position = (float)(avg / sum); 
        position = filter_constant * position + ((1.0 - filter_constant) * raw_position);
    }
    
}

float SensorArray::get_position() {
    return position;
}