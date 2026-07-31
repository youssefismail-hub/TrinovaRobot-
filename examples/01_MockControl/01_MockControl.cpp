#include <Arduino.h>
#include <TrinovaRobot.h>

TrinovaRobot robot;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println(" Mock Mode");

    if (!robot.begin(RobotMode::Mock)) {
        Serial.println("Initialization failed");
        return;
    }
}

void loop() {

    robot.forward(40);
    delay(800);

    robot.turnLeft(30);
    delay(400);

    robot.stop();
    delay(1500);

    robot.moveServo(0, 90, 500);
    delay(1500);

    robot.emergencyStop();
    delay(1000);

    robot.clearEmergencyStop();
    delay(1000);
}