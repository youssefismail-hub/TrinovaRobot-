#ifndef TRINOVA_ROBOT_H
#define TRINOVA_ROBOT_H

#include "RobotTypes.h"
#include "IRobotDriver.h"
#include "MotionSafety.h"

class TrinovaRobot {
public:
    TrinovaRobot();

    bool begin(RobotMode mode);
    void update();

    void forward(uint8_t speed);
    void backward(uint8_t speed);
    void turnLeft(uint8_t speed);
    void turnRight(uint8_t speed);
    void stop();

    bool moveServo(uint8_t channel, uint8_t angle, uint16_t durationMs = 0);

    void emergencyStop();
    bool clearEmergencyStop();

    RobotState state() const;
    TrinovaError lastError() const;

private:
    RobotMode _mode = RobotMode::Mock;
    RobotState _state = RobotState::NotReady;
    TrinovaError _lastError = TrinovaError::None;

    RobotConfig _config;
    IRobotDriver* _driver = nullptr;

    uint32_t _lastCommandTime = 0;
    
    MotionSafety* _safety = nullptr; 

    uint8_t clampSpeed(uint8_t speed);
    void checkTimeout();
};

#endif