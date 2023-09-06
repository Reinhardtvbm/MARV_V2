#include "sensor.h"



Sensor::Sensor(int pin, float filter_constant) {
    this->pin = pin;
    this->filter_constant = filter_constant;

    this->raw_value = 0;
    this->value = 0;

    this->green = 0;
    this->cost = 0;

    pinMode(pin, INPUT);
}

void Sensor::calibrate() {
    this->green = 1024;
    
    for (int i = 0; i < 1000; i++) {
        this->update_sensor(); 
        uint16_t value = this->get_value();

        if (this->green > value) {
            this->green = value;
        }
    }
}

void Sensor::update_sensor() {
    this->raw_value = (uint16_t)analogRead(this->pin); 
    this->value = (uint16_t)((this->filter_constant * this->value) + ((1 - this->filter_constant) * this->raw_value) + 0.5); // 0.5 for rounding
}

uint16_t Sensor::get_value() {
    return this->value;
}

uint16_t Sensor::get_raw_value() {
    return this->raw_value;
}
