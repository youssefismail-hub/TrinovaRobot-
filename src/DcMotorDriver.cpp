#include "DcMotorDriver.h"
#include <Arduino.h>

DcMotorDriver::DcMotorDriver() {}

bool DcMotorDriver::begin(const RobotConfig& config) {
    _config = config;

    
    Serial.println("DcMotorDriver Initialisation OK");
    return true;
}

void DcMotorDriver::forward(uint8_t speed) {
    if (_emergencyActive) return;
    Serial.printf("DcMotorDriver FORWARD speed=%d\n", speed);
}

void DcMotorDriver::backward(uint8_t speed) {
    if (_emergencyActive) return;
    Serial.printf("DcMotorDriver BACKWARD speed=%d\n", speed);
}

void DcMotorDriver::turnLeft(uint8_t speed) {
    if (_emergencyActive) return;
    Serial.printf("DcMotorDriver TURN_LEFT speed=%d\n", speed);
}

void DcMotorDriver::turnRight(uint8_t speed) {
    if (_emergencyActive) return;
    Serial.printf("DcMotorDriver TURN_RIGHT speed=%d\n", speed);
}

void DcMotorDriver::stop() {
    Serial.println("DcMotorDriver STOP");
}

bool DcMotorDriver::moveServo(uint8_t, uint8_t, uint16_t) {
    
    return false;
}

void DcMotorDriver::emergencyStop() {
    _emergencyActive = true;
    Serial.println("DcMotorDriver EMERGENCY STOP");
}

void DcMotorDriver::clearEmergencyStop() {
    _emergencyActive = false;
    Serial.println("DcMotorDriver EMERGENCY CLEARED");
}

void DcMotorDriver::update() {
    
}