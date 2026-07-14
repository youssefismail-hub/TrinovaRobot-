#ifndef TRINOVA_MOTION_SAFETY_H
#define TRINOVA_MOTION_SAFETY_H

#include "RobotTypes.h"

class MotionSafety {
public:
    MotionSafety(const RobotConfig& config);

    uint8_t clampSpeed(uint8_t speed);
    bool checkTimeout(RobotState state, uint32_t lastCommandTime);
    uint8_t clampServoAngle(uint8_t angle);

private:
    RobotConfig _config;
};

#endif