#include "TrinovaRobot.h"
#include "MockRobotDriver.h"
#include "DcMotorDriver.h"
#include "ServoDriver.h"
#include "MotionSafety.h"

#include <Arduino.h>

TrinovaRobot::TrinovaRobot() {}

bool TrinovaRobot::begin(RobotMode mode) {

    _mode = mode;
    _state = RobotState::NotReady;
    _lastError = TrinovaError::None;


    _safety = new MotionSafety(_config);  // Création module sécurité

    // Sélection driver

    switch (mode) {
        case RobotMode::Mock:
            _driver = new MockRobotDriver();
            break;

        case RobotMode::DcMotors:
            _driver = new DcMotorDriver();
            break;

        case RobotMode::ServoRobot:
            _driver = new ServoDriver();
            break;

        default:
            _lastError = TrinovaError::NotInitialized;
            return false;
    }

    if (!_driver || !_driver->begin(_config)) {
        _state = RobotState::Error;

        if (mode == RobotMode::DcMotors)
            _lastError = TrinovaError::MotorDriverError;
        else if (mode == RobotMode::ServoRobot)
            _lastError = TrinovaError::ServoDriverError;

        return false;
    }

    //  R1.1 Initialisation sûre
    _driver->stop();

    _state = RobotState::Ready;
    _lastCommandTime = millis();

    return true;
}

void TrinovaRobot::update() {

    if (!_driver || !_safety)
        return;

    _driver->update();

    //  R1.7 Timeout
    if (_safety->checkTimeout(_state, _lastCommandTime)) {
        _driver->stop();
        _state = RobotState::Stopped;
        _lastError = TrinovaError::Timeout;
    }
}

void TrinovaRobot::forward(uint8_t speed) {

    if (_state == RobotState::EmergencyStop)
        return;

    speed = _safety->clampSpeed(speed);

    _driver->forward(speed);
    _state = RobotState::Moving;
    _lastCommandTime = millis();
}

void TrinovaRobot::backward(uint8_t speed) {

    if (_state == RobotState::EmergencyStop)
        return;

    speed = _safety->clampSpeed(speed);

    _driver->backward(speed);
    _state = RobotState::Moving;
    _lastCommandTime = millis();
}

void TrinovaRobot::turnLeft(uint8_t speed) {

    if (_state == RobotState::EmergencyStop)
        return;

    speed = _safety->clampSpeed(speed);

    _driver->turnLeft(speed);
    _state = RobotState::Moving;
    _lastCommandTime = millis();
}

void TrinovaRobot::turnRight(uint8_t speed) {

    if (_state == RobotState::EmergencyStop)
        return;

    speed = _safety->clampSpeed(speed);

    _driver->turnRight(speed);
    _state = RobotState::Moving;
    _lastCommandTime = millis();
}

void TrinovaRobot::stop() {

    if (!_driver)
        return;

    _driver->stop();
    _state = RobotState::Stopped;
}

bool TrinovaRobot::moveServo(uint8_t channel, uint8_t angle, uint16_t durationMs) {

    if (_state == RobotState::EmergencyStop)
        return false;

    if (!_driver || !_safety)
        return false;

    //  R1.8 Limites mécaniques
    angle = _safety->clampServoAngle(angle);

    bool result = _driver->moveServo(channel, angle, durationMs);

    if (result)
        _lastCommandTime = millis();

    return result;
}

void TrinovaRobot::emergencyStop() {

    if (_driver)
        _driver->emergencyStop();

    _state = RobotState::EmergencyStop;
}

bool TrinovaRobot::clearEmergencyStop() {

    if (_state != RobotState::EmergencyStop)
        return false;

    if (_driver)
        _driver->clearEmergencyStop();

    _state = RobotState::Ready;
    return true;
}

RobotState TrinovaRobot::state() const {
    return _state;
}

TrinovaError TrinovaRobot::lastError() const {
    return _lastError;
}