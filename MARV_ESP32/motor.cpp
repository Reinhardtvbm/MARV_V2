#include "motor.h"

Motor::Motor(int encoder_pin_A, int encoder_pin_B, int motor_pin_1, int motor_pin_2) : encoder(encoder_pin_A, encoder_pin_B) {
    this->encoder_pin_A = encoder_pin_A;
    this->encoder_pin_B = encoder_pin_B;

    pinMode(encoder_pin_A, OUTPUT);
    pinMode(encoder_pin_B, OUTPUT);

    this->motor_pin_1 = motor_pin_1;
    this->motor_pin_2 = motor_pin_2;

    analogWrite(this->motor_pin_1, 0);
    analogWrite(this->motor_pin_2, 0);

    this->time = micros();
    this->counts = 0;
    this->prev_counts = 0;
}

void Motor::set_speed(int speed) {
  analogWrite(this->motor_pin_1, speed);
}

// 60 encoder counts per revoltion
// rpm -> rad/s : *(2pi/60)
float Motor::speed() {
  long prev_time = this->time;
  this->time = micros();

  long elapsed = this->time - prev_time;

  // float speed = ((float)(this->counts - this->prev_counts) / 6.0) * ((2.0 * PI)/ (60.0 * (elapsed / 1000000.0)));
  float new_speed = 60.0 * ((float)(this->counts) / 6.0) / ((float)elapsed / 1000000.0);
  this->counts = 0;
  this->motor_speed = 0.9*this->motor_speed + 0.1*new_speed;

  return this->motor_speed;
}

void Motor::encoder_interrupt() {
  this->counts++;
}