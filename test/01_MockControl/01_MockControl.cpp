#include <Arduino.h>
#include <TrinovaRobot.h>

TrinovaRobot robot;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("=== TEST MOCK MODE ===");

    if (!robot.begin(RobotMode::Mock)) {
        Serial.println("Begin failed!");
        return;
    }

    robot.forward(40);
    delay(1000);

    robot.turnLeft(30);
    delay(1000);

    robot.stop();
    delay(1000);

    robot.moveServo(0, 90, 500);
    delay(1000);

    robot.emergencyStop();
    robot.forward(50);  // doit être ignoré
    delay(1000);

    robot.clearEmergencyStop();
    robot.forward(50);
}

void loop() {
    robot.update();
}