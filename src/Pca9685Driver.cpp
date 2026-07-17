#include "Pca9685Driver.h"

#define MODE1 0x00
#define PRESCALE 0xFE
#define LED0_ON_L 0x06

Pca9685Driver::Pca9685Driver(uint8_t address)
    : _address(address) {}

bool Pca9685Driver::begin(uint16_t pwmFrequency) {

    Wire.begin();

    Wire.beginTransmission(_address);
    if (Wire.endTransmission() != 0) {
        return false; // PCA9685 absent
    }

    writeRegister(MODE1, 0x10); // sleep

    uint8_t prescale = (25000000 / (4096 * pwmFrequency)) - 1;
    writeRegister(PRESCALE, prescale);

    writeRegister(MODE1, 0x00); // wake

    delay(5);

    return true;
}

void Pca9685Driver::setPWM(uint8_t channel, uint16_t on, uint16_t off) {

    Wire.beginTransmission(_address);
    Wire.write(LED0_ON_L + 4 * channel);
    Wire.write(on & 0xFF);
    Wire.write(on >> 8);
    Wire.write(off & 0xFF);
    Wire.write(off >> 8);
    Wire.endTransmission();
}

void Pca9685Driver::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t Pca9685Driver::readRegister(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(_address, (uint8_t)1);
    return Wire.read();
}