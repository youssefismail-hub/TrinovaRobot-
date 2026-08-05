#include <Arduino.h>
#include <TrinovaRobot.h>

TrinovaRobot robot;

void testSpeedClamp() {
    robot.forward(150);  // >100
    if (robot.lastError() == TrinovaError::InvalidSpeed) {
        Serial.println(" Speed clamp OK");
    } else {
        Serial.println(" Speed clamp FAILED"); 
    }
}

void testEmergencyStop() {
    robot.emergencyStop();
    robot.forward(40);

    if (robot.state() == RobotState::EmergencyStop) {
        Serial.println(" EmergencyStop OK");
    } else {
        Serial.println(" EmergencyStop FAILED");
    }

    robot.clearEmergencyStop();
}

void testTimeout() {
    robot.forward(40);
    delay(2000);
    robot.update();

    if (robot.state() == RobotState::Stopped) {
        Serial.println(" Timeout OK" );
    } else {
        Serial.println(" Timeout FAILED ");
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println(" TEST VALIDATION ");

    robot.begin(RobotMode::Mock);

    testSpeedClamp();
    testEmergencyStop();
    testTimeout();
}

void loop() {}