#include "sensor.h"
#include "motor.h"
#include <Encoder.h>

#define RIGHT_FORWARD 10
#define RIGHT_BACKWARD 11
#define LEFT_FORWARD 6
#define LEFT_BACKWARD 9

const int encoderPinA = 2;
const int encoderPinB = 3;

void encoder_interrupt_main() {
  motor1.encoder_interrupt();
}

void setup() {
  pinMode(2, OUTPUT);
  analogWrite(2, 0);

  pinMode(15, OUTPUT);
  analogWrite(15, 0);

  Serial.begin(19200);
}
 
void loop() {
  Serial.println(motor1.speed());
  motor1.set_speed(speed_set);

  if (delay_count == 99) {
    speed_set += 10;
  }
  
  delay_count = (delay_count + 1) % 100;

  if (speed_set == 260) {
    speed_set = 0;
  }

  delay(5);
}


