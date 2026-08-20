#include "ServoDriver.h"
#include <Arduino.h>

ServoDriver::ServoDriver() : _pca(0x40) {}

bool ServoDriver::begin(const RobotConfig& config) {

    _config = config;

    if (!_pca.begin(50)) { // 50Hz pour servo
        return false;  // erreur ServoDriverError
    }

    // Position neutre : 
    for (int i = 0; i < MAX_SERVOS; i++) {
        writeAngle(i, 90);
        _servos[i].currentAngle = 90;
    }


    Serial.println("ServoDriver PCA9685 initialized with interpolation ");
    return true;
}

bool ServoDriver::moveServo(uint8_t channel, uint8_t angle,uint16_t durationMs) {

    if (_emergencyActive)
        return false;

    if (channel >= MAX_SERVOS)
        return false;


    if (durationMs == 0) {
        writeAngle(channel, angle);
        _servos[channel].currentAngle = angle;
        return true;
    }

    _servos[channel].targetAngle = angle;
    _servos[channel].startTime = millis();
    _servos[channel].duration = durationMs;
    _servos[channel].moving = true;

    return true;
}


void ServoDriver::writeAngle(uint8_t channel, uint8_t angle) {

    uint16_t pulseMin = 150;
    uint16_t pulseMax = 600;

    uint16_t pulse = map(angle, 0, 180, pulseMin, pulseMax);

    _pca.setPWM(channel, 0, pulse);
}

void ServoDriver::emergencyStop() {
    _emergencyActive = true;
}

void ServoDriver::clearEmergencyStop() {
    _emergencyActive = false;
}

void ServoDriver::forward(uint8_t speed) {}
void ServoDriver::backward(uint8_t speed) {}
void ServoDriver::turnLeft(uint8_t speed) {}
void ServoDriver::turnRight(uint8_t speed) {}
void ServoDriver::stop() {}




void ServoDriver::update() {
    
    if (_emergencyActive)
        return;

    uint32_t now = millis();

    for (int i = 0; i < MAX_SERVOS; i++) {

        if (!_servos[i].moving)
            continue;

        uint32_t elapsed = now - _servos[i].startTime;

        if (elapsed >= _servos[i].duration) {
            writeAngle(i, _servos[i].targetAngle);
            _servos[i].currentAngle = _servos[i].targetAngle;
            _servos[i].moving = false;
            continue;
        }

        float progress = (float)elapsed / _servos[i].duration;

        int newAngle = _servos[i].currentAngle +
            (int)((_servos[i].targetAngle - _servos[i].currentAngle) * progress);

        writeAngle(i, newAngle);
    }
    
}