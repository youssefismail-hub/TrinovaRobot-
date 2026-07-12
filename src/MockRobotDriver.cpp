#include "MockRobotDriver.h"
#include <Arduino.h>

MockRobotDriver::MockRobotDriver() {}

bool MockRobotDriver::begin(const RobotConfig& config) {
    _config = config;
    Serial.println("[MockDriver] Initialisation OK");
    return true;
}

void MockRobotDriver::forward(uint8_t speed) {
    if (_emergencyActive) return;

    _lastCommand = "FORWARD";
    _lastSpeed = speed;
    Serial.printf("[MockDriver] FORWARD speed=%d\n", speed);
}

void MockRobotDriver::backward(uint8_t speed) {
    if (_emergencyActive) return;

    _lastCommand = "BACKWARD";
    _lastSpeed = speed;
    Serial.printf("[MockDriver] BACKWARD speed=%d\n", speed);
}

void MockRobotDriver::turnLeft(uint8_t speed) {
    if (_emergencyActive) return;

    _lastCommand = "TURN_LEFT";
    _lastSpeed = speed;
    Serial.printf("[MockDriver] TURN_LEFT speed=%d\n", speed);
}

void MockRobotDriver::turnRight(uint8_t speed) {
    if (_emergencyActive) return;

    _lastCommand = "TURN_RIGHT";
    _lastSpeed = speed;
    Serial.printf("[MockDriver] TURN_RIGHT speed=%d\n", speed);
}

void MockRobotDriver::stop() {
    _lastCommand = "STOP";
    _lastSpeed = 0;
    Serial.println("[MockDriver] STOP");
}

bool MockRobotDriver::moveServo(uint8_t channel, uint8_t angle, uint16_t durationMs) {
    if (_emergencyActive) return false;

    Serial.printf("[MockDriver] SERVO channel=%d angle=%d duration=%d\n",
                  channel, angle, durationMs);

    return true;
}

void MockRobotDriver::emergencyStop() {
    _emergencyActive = true;
    Serial.println("[MockDriver] EMERGENCY STOP ACTIVATED");
}

void MockRobotDriver::clearEmergencyStop() {
    _emergencyActive = false;
    Serial.println("[MockDriver] EMERGENCY STOP CLEARED");
}

void MockRobotDriver::update() {
    // Rien à faire pour le mock (non bloquant)
}