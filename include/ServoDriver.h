#ifndef TRINOVA_SERVO_DRIVER_H
#define TRINOVA_SERVO_DRIVER_H

#include "IRobotDriver.h"
#include "Pca9685Driver.h"

class ServoDriver : public IRobotDriver {
public:
    ServoDriver();

    bool begin(const RobotConfig& config) override;

    void forward(uint8_t speed) override;
    void backward(uint8_t speed) override;
    void turnLeft(uint8_t speed) override;
    void turnRight(uint8_t speed) override;
    void stop() override;

    bool moveServo(uint8_t channel, uint8_t angle, uint16_t durationMs) override;

    void emergencyStop() override;
    void clearEmergencyStop() override;

    void update() override;

private:
    RobotConfig _config;
    bool _emergencyActive = false;
    Pca9685Driver _pca; 
};

#endif