#include <NewPing.h>

#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define ENA 8  //right
#define ENB 9  //left

#define cenTrig 49
#define cenEcho 48
#define cenRightTrig 51
#define cenRightEcho 50
#define cenLeftTrig 47
#define cenLeftEcho 46
#define revTrig 53
#define revEcho 52

NewPing cen(cenTrig, cenEcho, 400);
NewPing cenR(cenRightTrig, cenRightEcho, 400);  //issue
NewPing cenL(cenLeftTrig, cenLeftEcho, 400);
NewPing rev(revTrig, revEcho, 400);

int motorASpeed = 150;
int motorBSpeed = 180;

void setup() {
  Serial.begin(115200);

  int motorPins[] = { IN1,
                      IN2,
                      IN3,
                      IN4,
                      ENA,
                      ENB };

  for (int i = 0; i < 6; i++) {
    pinMode(motorPins, OUTPUT);
  }

  analogWrite(ENA, motorASpeed);
  analogWrite(ENB, motorBSpeed);
}

void loop() {
  int frontDist = cen.ping_cm();
  int frontLDist = cenL.ping_cm();
  int frontRDist = cenR.ping_cm();
  int backDist = rev.ping_cm();
  if (frontDist > 30) {
    forward();
  } else if (frontLDist > 30) {
    left();
    delay(1000);
  } else if (frontRDist > 30) {
    right();
    delay(1000);
  } else {
    stop();
    delay(1000);
    reverse();
    delay(1000);
  }
}

void forward() {
  //right
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //left
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  setSpeed();
}

void left() {
  //right
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //left
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  setSpeed();
}

void right() {
  //right
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  //left
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  setSpeed();
}

void reverse() {
  //right
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //left
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  setSpeed();
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setSpeed() {
  if (motorASpeed > 80) motorASpeed--;
  if (motorBSpeed > 110) motorBSpeed--;
  analogWrite(ENA, motorASpeed);
  analogWrite(ENB, motorBSpeed);
}
