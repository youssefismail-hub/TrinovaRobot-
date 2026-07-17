#ifndef TRINOVA_PCA9685_DRIVER_H
#define TRINOVA_PCA9685_DRIVER_H

#include <Arduino.h>
#include <Wire.h>

class Pca9685Driver {
public:
    Pca9685Driver(uint8_t address = 0x40);

    bool begin(uint16_t pwmFrequency);
    void setPWM(uint8_t channel, uint16_t on, uint16_t off);

private:
    uint8_t _address;

    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
};

#endif