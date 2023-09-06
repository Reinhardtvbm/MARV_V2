#define NUM_SENSORS 5

int sensor_pins[NUM_SENSORS] = {A0, A1, A2, A3, A4};
int16_t sensor_vals[NUM_SENSORS] = {0, 0, 0, 0, 0};


void setup() {
  pinMode(2, OUTPUT);
  analogWrite(2, 0);

  pinMode(3, OUTPUT);
  analogWrite(3, 0);

  pinMode(4, OUTPUT);
  analogWrite(4, 0);

  pinMode(5, OUTPUT);
  analogWrite(5, 0);

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(sensor_pins[i], INPUT);
    uint16_t raw_value = (uint16_t)analogRead(sensor_pins[i]); 
    sensor_vals[i] = raw_value;
  }

  Serial.begin(115200);
//  while (!Serial) {}
}



int16_t maxs[NUM_SENSORS] = {0, 0, 0, 0, 0};
int16_t mins[NUM_SENSORS] = {5000, 5000, 5000, 5000, 5000};

float sfilter_constant = 0.9;
float afilter_constant = 0.9;

float _position = 0;

float setpoint = 2000;
float error = 0;
const int const_speed = 70;
const int max_diff = 100;

float Kp = 1;
float Kd = 0.1;
float ki = 0.0;

int left_pwm;
int right_pwm;

void loop() {
    calibrate();

    uint32_t curr_time = micros();
    
    while (1) {
        float new_error = get_line_position();
        uint32_t new_time = micros();

        float dt = (float)(new_time - curr_time) / 1000000.0;
        
        float prop = Kp * line_pos;
        float der = Kd * (new_error - error) / dt;
        float integ = Ki * new_error * dt;

        float control_out = prop + der + integ;
        
        error = new_error;
        curr_time = new_time;
        
        float pwm = max_diff * ((setpoint - control_out) / setpoint);
        
        int lpwm = constrain(const_speed + (int)pwm, -255, 255);
        int rpwm = constrain(const_speed - (int)pwm, -255, 255);

        
        Serial.println(line_pos);
        Serial.print('\t');
        Serial.print(control_out);
        Serial.print('\t');
        Serial.print(dt, 6);
        delayMicroseconds(800);
        
        if (lpwm > 0) {
            analogWrite(2, 0);
            analogWrite(3, lpwm);
        } else {
            analogWrite(3, 0);
            analogWrite(2, abs(lpwm));
        }

        if (rpwm > 0) {
            analogWrite(4, 0);
            analogWrite(5, rpwm);
        } else {
            analogWrite(5, 0);
            analogWrite(4, abs(rpwm));
        }
    }
}

void calibrate() {
    uint32_t start = millis();
    
    while (millis() - start < 10000) {
        for (int i = 0; i < NUM_SENSORS; i++) {
            Serial.print(maxs[i]);
            Serial.print('\t');
        }

        Serial.println(' ');
    
        for (int i = 0; i < NUM_SENSORS; i++) {
            Serial.print(mins[i]);
            Serial.print('\t');
        }

        Serial.println(' ');
        for (int i = 0; i < NUM_SENSORS; i++) {
            
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

float get_line_position() {
    float avg = 0;
    float sum = 0;
    
    for (int i = 0; i < NUM_SENSORS; i++) {
        update_sensor(i);
        float value = (float)sensor_vals[i];

        float cost = constrain((value - mins[i]) / (maxs[i] - mins[i]), 0.0, 1.0);

        if (cost < 0.45) {
            cost = 0.0;
        }

        cost *= cost;
        
        avg += cost * (i * 1000);
        sum += cost;

        Serial.print(cost);
        Serial.print('\t');
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
