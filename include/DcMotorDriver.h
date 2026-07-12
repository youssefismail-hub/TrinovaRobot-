#ifndef TRINOVA_DC_MOTOR_DRIVER_H
#define TRINOVA_DC_MOTOR_DRIVER_H

#include "IRobotDriver.h"

class DcMotorDriver : public IRobotDriver {
public:
    DcMotorDriver();

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
};

#endif