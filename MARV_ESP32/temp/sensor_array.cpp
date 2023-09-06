#include "sensor_array.h"
#include "motor.h"

SensorArray::SensorArray(float filter_constant, float filter_constant_pins, int* pins) {
    maxs = new float[7];
    mins = new float[7];
    
    sensors = new Sensor*[7];
//    for (int i = 0; i < 7; i++) {
//        sensors[i] = new Sensor(pins[i], filter_constant_pins);
//    }

    this->filter_constant = filter_constant;
}
        
void SensorArray::calibrate() {
//    uint32_t start = millis();
//
    for (int i = 0; i < 5000; i++) {
        for (int i = 0; i < 7; i++) {
//            sensors[i]->update_sensor();
//            uint16_t value = sensors[i]->get_value();
            float value = 3;

            
//            if (value > maxs[i]) {
//                *(this->maxs + i) = value;
//            }
            if (value < *(mins + i)) {
                *(mins + i) = value;
            }
        }  
    }
}

void SensorArray::_update() {
//    double sum = 0;
//    double avg = 0;
//
//    for (int i = 0; i < 7; i++) {
//        sensors[i]->update_sensor();
//        double value = (double)(sensors[i]->get_value());
//        
//        double cost = (value - mins[i]) / (maxs[i] - mins[i]);
//
//        if (cost < 0) {
//            cost = 1.0 + cost;
//        } else {
//            cost = 1.0 - cost;
//        }
//
//        cost *= cost;
//        
//        if (cost < 0.4) {
//            cost = 0.0;
//        }
//
//        avg += cost * (i * 1000);
//        sum += cost;
//    }
//
//    if (sum != 0) { 
//        float raw_position = (float)(avg / sum); 
//        _position = filter_constant * _position + ((1.0 - filter_constant) * raw_position);
//    }
    
}

float SensorArray::get_position() {
<<<<<<< HEAD
    return _position;
=======
    return position;
>>>>>>> 2fec36058834f2fc45ccc9976220dbed31b8e519
}
