#include "MotionSafety.h"
#include <Arduino.h>

MotionSafety::MotionSafety(const RobotConfig& config)
    : _config(config) {}

uint8_t MotionSafety::clampSpeed(uint8_t speed) {
    if (speed > MAX_SPEED) {
        return MAX_SPEED;
    }
    return speed;
}

bool MotionSafety::checkTimeout(RobotState state, uint32_t lastCommandTime) {
    if (state == RobotState::Moving &&
        millis() - lastCommandTime > _config.commandTimeoutMs) {
        return true;
    }
    return false;
}

uint8_t MotionSafety::clampServoAngle(uint8_t angle) {
    if (angle < DEFAULT_SERVO_MIN_ANGLE)
        return DEFAULT_SERVO_MIN_ANGLE;

    if (angle > DEFAULT_SERVO_MAX_ANGLE)
        return DEFAULT_SERVO_MAX_ANGLE;

    return angle;
}