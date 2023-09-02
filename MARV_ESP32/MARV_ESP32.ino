#include "sensor.h"
#include "motor.h"
#include "sensor_array.h"
#include <Encoder.h>
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

boolean connected = false;
const char* ssid = "RPC";
const char* password = "boopboop";
const char* server_ip = "192.168.137.1";
const int port = 3000;

int pins[7] = {A0, A1, A2, A3, A4, A5, A6};
SensorArray sensor(0.99, 0.9, pins);

int motor_left_pin1 = 2, motor_left_pin2 = 3, motor_right_pin1 = 4, motor_right_pin2 = 5;

Motor left_motor(0, 0, motor_left_pin1, motor_left_pin2);
Motor right_motor(0, 0, motor_right_pin1, motor_right_pin2);

void setup() {
  pinMode(2, OUTPUT);
  analogWrite(2, 0);

  pinMode(15, OUTPUT);
  analogWrite(15, 0);

  Serial.begin(19200);
  while (!Serial) delay(10);

  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);

  while (!connected) {
      Serial.print(".");
      delay(100);
  }

  udp.begin(WiFi.localIP(), port);

  sensor.calibrate();
}

void loop() {
    sensor.update();
    float line_position = sensor.get_position();

    Serial.print("Position:\t");
    Serial.println(line_position);
}


void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case ARDUINO_EVENT_WIFI_STA_GOT_IP:
          connected = true;
          Serial.println("Connected to server :)");
          break;
      case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
      default: break;
    }
}

void send_udp(uint8_t* packet, int len) {
  if (connected) {
    udp.beginPacket(server_ip, port);
    udp.write(packet, len);
    udp.endPacket();
  }
}
