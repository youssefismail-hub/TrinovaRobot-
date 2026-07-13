#include "ServoDriver.h"
#include <Arduino.h>

ServoDriver::ServoDriver() {}

bool ServoDriver::begin(const RobotConfig& config) {
    _config = config;

    Serial.println("[Servo Driver] Initialisation OK (stub)");
    return true;
}

void ServoDriver::forward(uint8_t) {}
void ServoDriver::backward(uint8_t) {}
void ServoDriver::turnLeft(uint8_t) {}
void ServoDriver::turnRight(uint8_t) {}
void ServoDriver::stop() {}

bool ServoDriver::moveServo(uint8_t channel, uint8_t angle, uint16_t durationMs) {
    if (_emergencyActive) return false;

    Serial.printf("[Servo Driver] MOVE channel=%d angle=%d duration=%d\n",
                  channel, angle, durationMs);
    return true;
}

void ServoDriver::emergencyStop() {
    _emergencyActive = true;
    Serial.println("[Servo Driver] EMERGENCY STOP");
}

void ServoDriver::clearEmergencyStop() {
    _emergencyActive = false;
    Serial.println("[Servo Driver] EMERGENCY CLEARED");
}

void ServoDriver::update() {
    
}