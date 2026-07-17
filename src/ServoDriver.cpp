#include "ServoDriver.h"
#include <Arduino.h>

ServoDriver::ServoDriver() : _pca(0x40) {}

bool ServoDriver::begin(const RobotConfig& config) {

    _config = config;

    if (!_pca.begin(50)) { // 50Hz pour servo
        return false;  // erreur ServoDriverError
    }

    Serial.println("[ServoDriver] PCA9685 initialized");
    return true;
}

bool ServoDriver::moveServo(uint8_t channel, uint8_t angle, uint16_t) {

    if (_emergencyActive)
        return false;

    if (channel > 15)
        return false;

    // Conversion angle -> PWM
    uint16_t pulseMin = 150;   
    uint16_t pulseMax = 600;

    uint16_t pulse = map(angle, 0, 180, pulseMin, pulseMax);

    _pca.setPWM(channel, 0, pulse);

    return true;
}

void ServoDriver::emergencyStop() {
    _emergencyActive = true;
}

void ServoDriver::clearEmergencyStop() {
    _emergencyActive = false;
}

void ServoDriver::update() {
    
}