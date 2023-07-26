#include "sensor.h"
#include <Encoder.h>

#define RIGHT_FORWARD 3
#define RIGHT_BACKWARD 5
#define LEFT_FORWARD 6
#define LEFT_BACKWARD 9

const int encoderPinA = 12;
const int encoderPinB = 11;

enum Side {
  Left,
  Right,
};

enum Direction {
  Forward,
  Backward,
};

Direction prev_direction = Forward;
Encoder encoder(encoderPinA, encoderPinB);

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  analogWrite(3, 0);

  pinMode(5, OUTPUT);
  analogWrite(5, 0);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  


  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  Serial.begin(115200);
}

Sensor sensor_0 = Sensor(A0, 0.90);
Sensor sensor_1 = Sensor(A1, 0.90);
Sensor sensor_2 = Sensor(A2, 0.90);  



void loop() {

  analogWrite(3, 100);
  // for (int i = 100; i < 256; i++) {
  //   analogWrite(3, i);
  //   for (int j = 0; j < 10; j++) {
  //     delay(5);
  //     uint32_t counts = encoder.read();
  //     Serial.println(counts);
  //   }
  //   encoder.write(0);
  // }
}

void set_motor(Side motor_side, Direction motor_direction, int motor_speed) {
  if (motor_direction == Forward) {
    if (motor_side == Right) {
      if (prev_direction == Backward) {
        analogWrite(RIGHT_BACKWARD, 0);
      }
      
      analogWrite(RIGHT_FORWARD, motor_speed);
    } else {
      if (prev_direction == Backward) {
        analogWrite(LEFT_BACKWARD, 0);
      }
      
      analogWrite(LEFT_FORWARD, motor_speed);
    }

    prev_direction = Forward;
  } else {
    if (motor_side == Right) {
      if (prev_direction == Forward) {
        analogWrite(RIGHT_FORWARD, 0);
      }
      
      analogWrite(RIGHT_BACKWARD, motor_speed);
    } else {
      if (prev_direction == Forward) {
        analogWrite(LEFT_FORWARD, 0);
      }
      
      analogWrite(LEFT_BACKWARD, motor_speed);
    }

    prev_direction = Backward;
  }
}
