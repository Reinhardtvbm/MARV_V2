
<<<<<<< HEAD
int sensor_pins[7] = {A0, A1, A2, A3, A4, A5, A6};
uint16_t sensor_vals[7] = {0, 0, 0, 0, 0, 0, 0};
=======
WiFiUDP udp;

boolean connected = false;
const char* ssid = "RPC";
const char* password = "boopboop";
const char* server_ip = "192.168.137.1";
const int port = 3000;

int pins[7] = {A0, A1, A2, A3, A4, A5, A6};
SensorArray sensor(0.99, 0.9, pins);
>>>>>>> 2fec36058834f2fc45ccc9976220dbed31b8e519

int motor_left_pin1 = 2, motor_left_pin2 = 3, motor_right_pin1 = 4, motor_right_pin2 = 5;

Motor left_motor(0, 0, motor_left_pin1, motor_left_pin2);
Motor right_motor(0, 0, motor_right_pin1, motor_right_pin2);

void setup() {
  pinMode(2, OUTPUT);
  analogWrite(2, 0);

  pinMode(3, OUTPUT);
  analogWrite(3, 0);

  pinMode(4, OUTPUT);
  analogWrite(4, 0);

  pinMode(5, OUTPUT);
  analogWrite(5, 0);

  for (int i = 0; i < 7; i++) {
    pinMode(sensor_pins[i], INPUT);
    uint16_t raw_value = (uint16_t)analogRead(sensor_pins[i]); 
    sensor_vals[i] = raw_value;
  }

  Serial.begin(115200);
}



float maxs[7] = {0, 0, 0, 0, 0, 0, 0};
float mins[7] = {3000, 3000, 3000, 3000, 3000, 3000, 3000};

float sfilter_constant = 0.9;
float afilter_constant = 0.9;

float _position = 0.0;

float setpoint = 3000.0;
const int const_speed = 45;
const int max_diff = 210;

int left_pwm;
int right_pwm;

void loop() {
    calibrate();

    while (1) {
        float line_pos = get_line_position();

        float pwm = 205.0 * ((3000.0 - line_pos) / 3000.0);

        int lpwm = constrain(150 - pwm, -255, 255);
        int rpwm = constrain(150 + pwm, -255, 255);

        Serial.print(lpwm);
        Serial.print('\t');
        Serial.print(rpwm);
        Serial.print('\t');
        Serial.println(line_pos);
        delayMicroseconds(800);
        
        if (lpwm > 0) {
            analogWrite(2, 0);
            analogWrite(3, lpwm);
        } else {
            analogWrite(3, 0);
            analogWrite(2, abs(lpwm));
        }

        if (rpwm > 0) {
            analogWrite(5, 0);
            analogWrite(4, rpwm);
        } else {
            analogWrite(4, 0);
            analogWrite(5, abs(rpwm));
        }
    }
}

void calibrate() {
    for (int i = 0; i < 10000; i++) {
        for (int i = 0; i < 7; i++) {
            Serial.print(maxs[i]);
            Serial.print('\t');
        }

        Serial.println(' ');
    
        for (int i = 0; i < 7; i++) {
            Serial.print(mins[i]);
            Serial.print('\t');
        }

        Serial.println(' ');
        for (int i = 0; i < 7; i++) {
            
            update_sensor(i);
            float value = (float)sensor_vals[i];
            
            if (value > maxs[i]) {
                maxs[i] = value;
            }
            if (value < mins[i]) {
                mins[i] = value;
            }
        }    
    }  

    
    digitalWrite(15, LOW);
}
<<<<<<< HEAD

float get_line_position() {
    float avg = 0;
    float sum = 0;
    
    for (int i = 0; i < 7; i++) {
        update_sensor(i);
        float value = (float)sensor_vals[i];
//        
            

        float cost = (value - mins[i]) / (maxs[i] - mins[i]);

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

//        Serial.print(value);
//        Serial.print('\t');
    }

    
    if (sum != 0) { 
        float raw_position = (float)(avg / sum); 
        _position = afilter_constant * _position + ((1.0 - afilter_constant) * raw_position);
    }

//    Serial.println(' ');
    return _position;
}

void update_sensor(int index) {
  uint16_t raw_value = (uint16_t)analogRead(sensor_pins[index]); 
  sensor_vals[index] = (uint16_t)((sfilter_constant * sensor_vals[index]) + ((1 - sfilter_constant) * raw_value) + 0.5); // 0.5 for rounding
}
=======
>>>>>>> 2fec36058834f2fc45ccc9976220dbed31b8e519
