#include <NewPing.h> // Library for ultrasonic sensor

#define TRIGGER_PIN_1 2 // Pin for first ultrasonic sensor trigger
#define ECHO_PIN_1 3    // Pin for first ultrasonic sensor echo
#define TRIGGER_PIN_2 4 // Pin for second ultrasonic sensor trigger
#define ECHO_PIN_2 5    // Pin for second ultrasonic sensor echo
#define TRIGGER_PIN_3 6 // Pin for third ultrasonic sensor trigger
#define ECHO_PIN_3 7    // Pin for third ultrasonic sensor echo

#define MAX_DISTANCE 200 // Maximum distance (in cm) to measure

#define MOTOR_A_FORWARD 8   // Pin connected to motor A forward
#define MOTOR_A_BACKWARD 9  // Pin connected to motor A backward
#define MOTOR_B_FORWARD 10  // Pin connected to motor B forward
#define MOTOR_B_BACKWARD 11 // Pin connected to motor B backward

#define MAX_RPM 150 // Maximum RPM for the motors

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);

void setup() {
  pinMode(MOTOR_A_FORWARD, OUTPUT);
  pinMode(MOTOR_A_BACKWARD, OUTPUT);
  pinMode(MOTOR_B_FORWARD, OUTPUT);
  pinMode(MOTOR_B_BACKWARD, OUTPUT);
}

void loop() {
  int distance1 = sonar1.ping_cm();
  int distance2 = sonar2.ping_cm();
  int distance3 = sonar3.ping_cm();

  if (distance1 < MAX_DISTANCE && distance2 < MAX_DISTANCE && distance3 < MAX_DISTANCE) {
    // Stop if obstacles detected by all sensors
    stop();
  } else if (distance1 < MAX_DISTANCE) {
    // Turn right if obstacle detected by sensor 1
    turnRight();
  } else if (distance2 < MAX_DISTANCE) {
    // Turn left if obstacle detected by sensor 2
    turnLeft();
  } else if (distance3 < MAX_DISTANCE) {
    // Move backward if obstacle detected by sensor 3
    moveBackward();
  } else {
    // Move forward if no obstacles detected
    moveForward();
  }
}

void moveForward() {
  analogWrite(MOTOR_A_FORWARD, MAX_RPM);
  analogWrite(MOTOR_B_FORWARD, MAX_RPM);
  analogWrite(MOTOR_A_BACKWARD, 0);
  analogWrite(MOTOR_B_BACKWARD, 0);
}

void moveBackward() {
  analogWrite(MOTOR_A_FORWARD, 0);
  analogWrite(MOTOR_B_FORWARD, 0);
  analogWrite(MOTOR_A_BACKWARD, MAX_RPM);
  analogWrite(MOTOR_B_BACKWARD, MAX_RPM);
}

void turnLeft() {
  analogWrite(MOTOR_A_FORWARD, 0);
  analogWrite(MOTOR_B_FORWARD, MAX_RPM);
  analogWrite(MOTOR_A_BACKWARD, MAX_RPM);
  analogWrite(MOTOR_B_BACKWARD, 0);
}

void turnRight() {
  analogWrite(MOTOR_A_FORWARD, MAX_RPM);
  analogWrite(MOTOR_B_FORWARD, 0);
  analogWrite(MOTOR_A_BACKWARD, 0);
  analogWrite(MOTOR_B_BACKWARD, MAX_RPM);
}

void stop() {
  analogWrite(MOTOR_A_FORWARD, 0);
  analogWrite(MOTOR_B_FORWARD, 0);
  analogWrite(MOTOR_A_BACKWARD, 0);
  analogWrite(MOTOR_B_BACKWARD, 0);
}