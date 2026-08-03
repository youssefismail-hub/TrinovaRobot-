#include <Arduino.h>
#include <TrinovaRobot.h>

TrinovaRobot robot;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Example:  Servo Control ");

    if (!robot.begin(RobotMode::ServoRobot)) {
        Serial.println("Servo driver error");
        return;
    }
}

void loop() {

    // Mouvement progressif 2 secondes
    robot.moveServo(0, 0, 2000);
    delay(3000);

    robot.moveServo(0, 180, 2000);
    delay(3000);

    robot.moveServo(0, 90, 2000);
    delay(3000);
}