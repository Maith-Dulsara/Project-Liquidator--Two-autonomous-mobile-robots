#include <Arduino.h>

// Pin definitions
const int lineSensorPin = A0;
const int yellowObstaclePin = 2;
const int colorSensorPin = A1;
const int clawPin = 3;

// Constants
const int junctionThreshold = 500;
const int checkpointThreshold = 1000;
const int forwardSpeed = 100;
const int turnSpeed = 50;
const int clawDelay = 1000;

// Global variables
int checkpointCount = 0;
int lastError = 0;
bool assistSignalReceived = false;
bool colorMatched = false;

// Functions
void forward() {
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  analogWrite(6, forwardSpeed);
}

void backward() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  analogWrite(6, forwardSpeed);
}

void stop() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  analogWrite(6, 0);
}

void turnLeft() {
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(9, turnSpeed);
}

void turnRight() {
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(9, turnSpeed);
}

void clawActivate() {
  digitalWrite(clawPin, HIGH);
  delay(clawDelay);
  digitalWrite(clawPin, LOW);
}

int getLineSensorValue() {
  return analogRead(lineSensorPin);
}

int getColorSensorValue() {
  return analogRead(colorSensorPin);
}

bool isJunction() {
  int sensorValue = getLineSensorValue();
  return sensorValue < junctionThreshold;
}

bool isObstacleDetected() {
  return digitalRead(yellowObstaclePin) == HIGH;
}

bool isLineEnding() {
  int sensorValue = getLineSensorValue();
  return abs(sensorValue - lastError) > 100;
}

void moveToStartSquare() {
  while (!isLineEnding()) {
    forward();
  }
  stop();
}

void followPath1() {
  while (true) {
    if (!isJunction()) {
      int sensorValue = getLineSensorValue();
      int error = sensorValue - 512;
      int correction = error / 4;
      analogWrite(6, forwardSpeed - correction);
    } else {
      stop();
      turnLeft();
      while (!isLineEnding()) {
        forward();
      }
      stop();
      if (!isLineEnding()) {
        break;
      }
      turnRight();
    }
    lastError = getLineSensorValue() - 512;
  }
}

void followPath2() {
  turnLeft();
  while (!isLineEnding()) {
    forward();
  }
  stop();
  turnRight();
}

void waitForYellowObstacle() {
  while (isObstacleDetected()) {
    stop();
  }
}

void turnAround() {
  turnRight();
  delay(500);
  while (!isLineEnding()) {
    forward();
  }
  stop();
  turnRight();
}

void followPath3() {
  while (true) {
    if (checkpointCount == 1 && assistSignalReceived && colorMatched) {
      clawActivate();
      break;
    }
    if (!isJunction()) {
      int sensorValue = getLineSensorValue();
      int error = sensorValue - 512;
      int correction = error / 4;
      analogWrite(6, forwardSpeed - correction);
    } else {
      stop();
      turnLeft();
      while (!isLineEnding()) {
        forward();
      }
      stop();
      if (isObstacleDetected()) {
        turnAround();
        continue;
      }
      turnRight();
      if (checkpointCount == 0) {
        if (isLineEnding()) {
          checkpointCount++;
        }
      } else if (checkpointCount == 1) {
        if (isLineEnding()) {
          checkpointCount++;
        } else {
          waitForYellowObstacle();
        }
      }
    }
    lastError = getLineSensorValue() - 512;
  }
}

void followPath4() {
  while (true) {
    if (!isJunction()) {
      int sensorValue = getLineSensorValue();
      int error = sensorValue - 512;
      int correction = error / 4;
      analogWrite(6, forwardSpeed - correction);
    } else {
      stop();
      turnRight();
      if (isObstacleDetected()) {
        stop();
        break;
      }
      forward();
      while (!isJunction()) {
        forward();
      }
      stop();
      turnRight();
      forward();
    }
    lastError = getLineSensorValue() - 512;
  }
}

void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(yellowObstaclePin, INPUT);
  pinMode(colorSensorPin, INPUT);
  pinMode(clawPin, OUTPUT);
}

void loop() {
  // Turn on the robot
  // Attach the assistant robot
  // Move forward until the robot is on the start square
  moveToStartSquare();

  // Follow path 1 until checkpoint-1 is reached
  while (checkpointCount < 1) {
    followPath1();
    if (isLineEnding()) {
      checkpointCount++;
    }
  }

  // Follow path 2 until checkpoint-2 is reached
  while (checkpointCount < 2) {
    followPath2();
    if (isLineEnding()) {
      checkpointCount++;
    }
  }

  // Follow path 3 until the finishing squares are reached
  followPath3();

  // Follow path 4 to unload the box
  followPath4();

  // Turn around and move forward to reach the starting position
  turnAround();
  forward();
  while (checkpointCount > 0) {
    if (isLineEnding()) {
      checkpointCount--;
    }
    forward();
  }
  stop();
}