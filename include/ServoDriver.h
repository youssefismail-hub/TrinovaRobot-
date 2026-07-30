#ifndef TRINOVA_SERVO_DRIVER_H
#define TRINOVA_SERVO_DRIVER_H

#include "IRobotDriver.h"
#include "Pca9685Driver.h"

#define MAX_SERVOS 16 

class ServoDriver : public IRobotDriver {
public:
    ServoDriver();

    bool begin(const RobotConfig& config) override;

    void forward(uint8_t speed) override;
    void backward(uint8_t speed) override;
    void turnLeft(uint8_t speed) override;
    void turnRight(uint8_t speed) override;
    void stop() override;

    bool moveServo(uint8_t channel, uint8_t angle,uint16_t durationMs) override;

    void emergencyStop() override;
    void clearEmergencyStop() override;

    void update() override;

private:
    struct ServoState {
        uint8_t currentAngle = 90;
        uint8_t targetAngle = 90;
        uint32_t startTime = 0;
        uint16_t duration = 0;
        bool moving = false;
    };

    ServoState _servos[MAX_SERVOS];

    RobotConfig _config;
    
    bool _emergencyActive = false;

    Pca9685Driver _pca; 
    
    void writeAngle(uint8_t channel, uint8_t angle);
};

#endif