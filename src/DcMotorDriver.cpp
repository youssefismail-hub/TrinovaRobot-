#include "DcMotorDriver.h"
#include <Arduino.h>

DcMotorDriver::DcMotorDriver() {}

bool DcMotorDriver::begin(const RobotConfig& config) {

    _config = config;

    pinMode(_dir1L, OUTPUT);
    pinMode(_dir2L, OUTPUT);
    pinMode(_pwmL, OUTPUT);

    pinMode(_dir1R, OUTPUT);
    pinMode(_dir2R, OUTPUT);
    pinMode(_pwmR, OUTPUT);

    stop(); //  Initialisation sûre

    Serial.println("[DcMotorDriver] Hardware initialized");
    return true;
}

uint8_t DcMotorDriver::speedToPwm(uint8_t speed) {
    return map(speed, 0, 100, 0, 255);
}

void DcMotorDriver::setMotorLeft(bool forward, uint8_t speed) {

    digitalWrite(_dir1L, forward);
    digitalWrite(_dir2L, !forward);
    analogWrite(_pwmL, speedToPwm(speed));
}

void DcMotorDriver::setMotorRight(bool forward, uint8_t speed) {

    digitalWrite(_dir1R, forward);
    digitalWrite(_dir2R, !forward);
    analogWrite(_pwmR, speedToPwm(speed));
}

void DcMotorDriver::forward(uint8_t speed) {

    if (_emergencyActive) return;

    setMotorLeft(true, speed);
    setMotorRight(true, speed);
}

void DcMotorDriver::backward(uint8_t speed) {

    if (_emergencyActive) return;

    setMotorLeft(false, speed);
    setMotorRight(false, speed);
}

void DcMotorDriver::turnLeft(uint8_t speed) {

    if (_emergencyActive) return;

    
    setMotorLeft(false, 0);
    setMotorRight(true, speed);
}

void DcMotorDriver::turnRight(uint8_t speed) {

    if (_emergencyActive) return;

    setMotorLeft(true, speed);
    setMotorRight(false, 0);
}

void DcMotorDriver::stop() {


    if (_brakeMode) {
        //  Freinage actif 
        digitalWrite(_dir1L, HIGH);
        digitalWrite(_dir2L, HIGH);
        digitalWrite(_dir1R, HIGH);
        digitalWrite(_dir2R, HIGH);
    }

    analogWrite(_pwmL, 0);
    analogWrite(_pwmR, 0);
}

bool DcMotorDriver::moveServo(uint8_t, uint8_t, uint16_t) {
    return false;
}

void DcMotorDriver::emergencyStop() {
    _emergencyActive = true;
    stop();
}

void DcMotorDriver::clearEmergencyStop() {
    _emergencyActive = false;
}

void DcMotorDriver::update() {
    
}