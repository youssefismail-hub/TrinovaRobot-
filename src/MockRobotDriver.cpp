#include "MockRobotDriver.h"
#include <Arduino.h>

MockRobotDriver::MockRobotDriver() {}

bool MockRobotDriver::begin(const RobotConfig& config) {
    _config = config;
    Serial.println("[Mock Driver] Initialisation OK");
    return true;
}

void MockRobotDriver::forward(uint8_t speed) {
    if (_emergencyActive) return;

    _lastCommand = "FORWARD";
    _lastSpeed = speed;
    Serial.printf("[Mock Driver] FORWARD speed=%d\n", speed);
}

void MockRobotDriver::backward(uint8_t speed) {
    if (_emergencyActive) return;

    _lastCommand = "BACKWARD";
    _lastSpeed = speed;
    Serial.printf("[Mock Driver] BACKWARD speed=%d\n", speed);
}

void MockRobotDriver::turnLeft(uint8_t speed) {
    if (_emergencyActive) return;

    _lastCommand = "TURN_LEFT";
    _lastSpeed = speed;
    Serial.printf("[Mock Driver] TURN_LEFT speed=%d\n", speed);
}

void MockRobotDriver::turnRight(uint8_t speed) {
    if (_emergencyActive) return;

    _lastCommand = "TURN_RIGHT";
    _lastSpeed = speed;
    Serial.printf("[Mock Driver] TURN_RIGHT speed=%d\n", speed);
}

void MockRobotDriver::stop() {
    _lastCommand = "STOP";
    _lastSpeed = 0;
    Serial.println("[Mock Driver] STOP");
}

bool MockRobotDriver::moveServo(uint8_t channel, uint8_t angle, uint16_t durationMs) {
    if (_emergencyActive) return false;

    Serial.printf("[Mock Driver] SERVO channel=%d angle=%d duration=%d\n",
                  channel, angle, durationMs);

    return true;
}

void MockRobotDriver::emergencyStop() {
    _emergencyActive = true;
    Serial.println("[MockDriver] EMERGENCY STOP ACTIVATED");
}

void MockRobotDriver::clearEmergencyStop() {
    _emergencyActive = false;
    Serial.println("[Mock Driver] EMERGENCY STOP CLEARED");
}

void MockRobotDriver::update() {
    
}