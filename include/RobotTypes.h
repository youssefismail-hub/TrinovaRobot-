#ifndef TRINOVA_ROBOT_TYPES_H
#define TRINOVA_ROBOT_TYPES_H

#include <Arduino.h>




enum class RobotMode {
    Mock,           //   Mock       : Aucun matériel requis, simulation des commandes.
    DcMotors,       //   DcMotors   : Contrôle uniquement des deux moteurs DC.
    ServoRobot      //   ServoRobot : Contrôle moteurs + servomoteurs via PCA9685.
};


enum class RobotState {
    NotReady,        // Avant appel à begin()
    Ready,           // Initialisé et prêt
    Moving,          // En mouvement
    Stopped,         // Arrêt volontaire
    EmergencyStop,   // Arrêt d'urgence actif
    Error            // Erreur interne ou matérielle
};


enum class TrinovaError {
    None,
    NotInitialized,
    MotorDriverError,
    ServoDriverError,
    InvalidSpeed,
    InvalidServoChannel,
    InvalidServoAngle,
    EmergencyActive,
    Timeout
};


struct RobotConfig {
    uint8_t defaultSpeed = 40;          // Vitesse par défaut (0-100)
    uint32_t commandTimeoutMs = 1500;   // Timeout automatique moteur
    uint16_t pwmFrequency = 20000;      // Fréquence PWM moteurs DC
};

// Constantes de Sécurité

constexpr uint8_t MIN_SPEED = 0;
constexpr uint8_t MAX_SPEED = 100;

constexpr uint8_t MIN_SERVO_CHANNEL = 0;
constexpr uint8_t MAX_SERVO_CHANNEL = 15;   // PCA9685 = 16 canaux

constexpr uint8_t DEFAULT_SERVO_MIN_ANGLE = 0;
constexpr uint8_t DEFAULT_SERVO_MAX_ANGLE = 180;

#endif 