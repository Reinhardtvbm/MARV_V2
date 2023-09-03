#pragma once 

#include <Arduino.h>
#include <stdint.h>

/// One motor, including its encoder and controller
class Motor {
    public:
        Motor(int encoder_pin_A, int encoder_pin_B, int motor_pin_1, int motor_pin_2);
        void set_speed(int speed);
        float speed();
        void encoder_interrupt();        

    private:
        long counts, prev_counts, time;
        float motor_speed;
        int encoder_pin_A, encoder_pin_B, motor_pin_1, motor_pin_2, num_speeds;
};
