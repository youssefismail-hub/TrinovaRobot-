#include <Arduino.h>
#include <TrinovaRobot.h>

TrinovaRobot robot;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println(" DC Motors ");

    if (!robot.begin(RobotMode::DcMotors)) {
        Serial.println("Motor driver error");
        return;
    }
}

void loop() {

    robot.forward(50);
    delay(2000);

    robot.turnLeft(40);
    delay(1500);

    robot.turnRight(40);
    delay(1500);

    robot.backward(50);
    delay(2000);

    robot.stop();
    delay(3000);
}