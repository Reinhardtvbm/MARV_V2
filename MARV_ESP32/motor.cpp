#include "motor.h"
#include <Arduino.h>

Motor::Motor(int encoder_pin_A, int encoder_pin_B) {
    this->encoder_pin_A = encoder_pin_A;
    this->encoder_pin_B = encoder_pin_B;

    this->encoder = Encoder(this->encoder_pin_A, this->encoder_pin_B);
}

void Motor::set_speed() {

}
