#include <Arduino.h>
#include <Servo.h>

Servo ser;

double sign(double x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
}

struct Result {
    bool isValid;
    double value;
};

Result f(double x0, double xt, double vMax1, double aMax, double t) {
    
    if (vMax1 <= 0 || aMax <=0 || t < 0) {
        return {false, 0};
    }
    
    double s = sign(xt - x0);
    double vMax = s * min(sqrt(aMax * abs(xt - x0)), vMax1);
    double t1 = abs(vMax) / aMax;
    double x1 = x0 + s * aMax * t1 * t1 / 2;
    double t2 = (xt + x0 - 2 * x1) / vMax + t1;
    double x2 = x1 + vMax * (t2 - t1);
    double t3 = t1 + t2;
    
    // Serial.println(t1);
    // Serial.println(x1);
    // Serial.println(t2);
    // Serial.println(x2);
    // Serial.println(t3);
    
    if (0 < t && t <= t1) {
        Serial.print("Speeding up: ");
        return {true, x0 + s * aMax * t * t / 2};
    }
    
    if (t1 < t && t < t2) {
        Serial.print("Going: ");
        return {true, x1 + vMax * (t - t1)};
    }
    
    if (t2 < t && t <= t3) {
        Serial.print("Slowing down: ");
        return {true, x2 + vMax * (t - t2) - s * aMax * (t - t2) * (t - t2) / 2};
    }
    
    return {false, 0};
}

double T = 0;
int xt = 170;

void go(int xt) {
    int x0 = ser.read();
    while(ser.read() != xt) {
        Result r = f(x0, xt, 60, 30, millis() / 1000.0 - T);
        if (!r.isValid) {
            Serial.println("Something went wrong");
            continue;
        }
        Serial.print("Time: ");
        Serial.print(millis() / 1000.0 - T);
        Serial.print("; target: ");
        Serial.print(xt);
        Serial.print("; current: ");
        Serial.print(ser.read());
        Serial.print("; requested: ");
        Serial.println(round(r.value));
        ser.write(round(r.value));
        
        
        if(round(r.value) == xt) continue;
        
    }
    // delay(1000);
    T = millis() / 1000.0;
    Serial.println("Reached target");
}

void setup() {
    Serial.begin(9600);
    ser.attach(9);
    ser.write(0);
    delay(500);
    T = millis() / 1000;
}


void loop() {
    go(175);
    go(5);
}