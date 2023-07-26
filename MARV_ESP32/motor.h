#pragma once 

#include <stdint.h>
#include <Encoder.h>

/// One motor, including its encoder and controller
class Motor {
    public:
        Motor(int encoder_pin_A, int encoder_pin_B);
        void set_speed();

    private:
        int encoder_pin_A, encoder_pin_B;
        uint32_t encoder_counts;
        Encoder encoder;

        uint16_t speed();

};
