#include "TrinovaRobot.h"
#include "MockRobotDriver.h"
#include "DcMotorDriver.h"
#include "ServoDriver.h"

TrinovaRobot::TrinovaRobot() {}

bool TrinovaRobot::begin(RobotMode mode) {
    _mode = mode;
    _state = RobotState::NotReady;
    _lastError = TrinovaError::None;

    // Sélection du driver
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
        return false;
    }

    _state = RobotState::Ready;
    _lastCommandTime = millis();
    return true;
}

void TrinovaRobot::update() {
    if (_driver) {
        _driver->update();
    }
    checkTimeout();
}

uint8_t TrinovaRobot::clampSpeed(uint8_t speed) {
    if (speed > MAX_SPEED) {
        _lastError = TrinovaError::InvalidSpeed;
        return MAX_SPEED;
    }
    return speed;
}

void TrinovaRobot::forward(uint8_t speed) {
    if (_state == RobotState::EmergencyStop) return;

    speed = clampSpeed(speed);
    _driver->forward(speed);
    _state = RobotState::Moving;
    _lastCommandTime = millis();
}

void TrinovaRobot::backward(uint8_t speed) {
    if (_state == RobotState::EmergencyStop) return;

    speed = clampSpeed(speed);
    _driver->backward(speed);
    _state = RobotState::Moving;
    _lastCommandTime = millis();
}

void TrinovaRobot::turnLeft(uint8_t speed) {
    if (_state == RobotState::EmergencyStop) return;

    speed = clampSpeed(speed);
    _driver->turnLeft(speed);
    _state = RobotState::Moving;
    _lastCommandTime = millis();
}

void TrinovaRobot::turnRight(uint8_t speed) {
    if (_state == RobotState::EmergencyStop) return;

    speed = clampSpeed(speed);
    _driver->turnRight(speed);
    _state = RobotState::Moving;
    _lastCommandTime = millis();
}

void TrinovaRobot::stop() {
    if (_driver) {
        _driver->stop();
        _state = RobotState::Stopped;
    }
}

bool TrinovaRobot::moveServo(uint8_t channel, uint8_t angle, uint16_t durationMs) {
    if (_state == RobotState::EmergencyStop) return false;

    bool result = _driver->moveServo(channel, angle, durationMs);
    if (result) {
        _lastCommandTime = millis();
    }
    return result;
}

void TrinovaRobot::emergencyStop() {
    if (_driver) {
        _driver->emergencyStop();
    }
    _state = RobotState::EmergencyStop;
}

bool TrinovaRobot::clearEmergencyStop() {
    if (_state != RobotState::EmergencyStop) return false;

    if (_driver) {
        _driver->clearEmergencyStop();
    }

    _state = RobotState::Ready;
    return true;
}

RobotState TrinovaRobot::state() const {
    return _state;
}

TrinovaError TrinovaRobot::lastError() const {
    return _lastError;
}

void TrinovaRobot::checkTimeout() {
    if (_state == RobotState::Moving &&
        millis() - _lastCommandTime > _config.commandTimeoutMs) {

        if (_driver) {
            _driver->stop();
        }

        _state = RobotState::Stopped;
        _lastError = TrinovaError::Timeout;
    }
}