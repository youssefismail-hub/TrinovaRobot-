#ifndef TRINOVA_IROBOT_DRIVER_H
#define TRINOVA_IROBOT_DRIVER_H

#include "RobotTypes.h"


class IRobotDriver {
public:
    virtual ~IRobotDriver() = default;

    virtual bool begin(const RobotConfig& config) = 0;

    // Commandes moteurs 
    virtual void forward(uint8_t speed) = 0;
    virtual void backward(uint8_t speed) = 0;
    virtual void turnLeft(uint8_t speed) = 0;
    virtual void turnRight(uint8_t speed) = 0;
    virtual void stop() = 0;

    //Commande servo 
    virtual bool moveServo(uint8_t channel, uint8_t angle, uint16_t durationMs) = 0;

    // Sécurité
    virtual void emergencyStop() = 0;
    virtual void clearEmergencyStop() = 0;

    // Mise à jour non bloquante
    virtual void update() = 0;
};

#endif