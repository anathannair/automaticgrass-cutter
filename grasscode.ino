#include <Servo.h>
const int in1PinA = 5;
const int in2PinA = 4;
const int in3PinB = 6;
const int in4PinB = 7;
const int in5PinA = 10;
const int in6PinA = 9;
const int in7PinB = 11;
const int in8PinB = 8;
const int tripin = 2;
const int echo = 3;
const int SERVO_PIN = 12;
bool stats=true;
Servo myservo;
bool val = false, val1 = false, val2 = false;
void setup() {
  Serial.begin(9600);
  pinMode(in1PinA, OUTPUT);
  pinMode(in2PinA, OUTPUT);
  pinMode(in3PinB, OUTPUT);
  pinMode(in4PinB, OUTPUT);
  pinMode(in6PinA, OUTPUT);
  pinMode(in7PinB, OUTPUT);
  pinMode(in8PinB, OUTPUT);
  pinMode(in5PinA, OUTPUT);
  pinMode(tripin, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(A1, OUTPUT);
  pinMode(13, INPUT);
  pinMode(A0,INPUT);
  myservo.attach(SERVO_PIN);
  myservo.write(80);  // Center position
  delay(2000);
}

// Function to move both motors forward
void moveForward() {
  motorRun();
  digitalWrite(in1PinA, LOW);
  digitalWrite(in2PinA, HIGH);
  digitalWrite(in3PinB, HIGH);
  digitalWrite(in4PinB, LOW);
  digitalWrite(in5PinA, LOW);
  digitalWrite(in6PinA, HIGH);
  digitalWrite(in7PinB, LOW);
  digitalWrite(in8PinB, HIGH);
}
void moveBackward() {
  analogWrite(A1, 255);
  digitalWrite(13, LOW);
  digitalWrite(in1PinA, HIGH);
  digitalWrite(in2PinA, LOW);
  digitalWrite(in3PinB, LOW);
  digitalWrite(in4PinB, HIGH);
  digitalWrite(in5PinA, HIGH);
  digitalWrite(in6PinA, LOW);
  digitalWrite(in7PinB, HIGH);
  digitalWrite(in8PinB, LOW);
}
void stopMotors() {
  analogWrite(A1, 255);
  digitalWrite(13, LOW);
  digitalWrite(in1PinA, LOW);
  digitalWrite(in2PinA, LOW);
  digitalWrite(in3PinB, LOW);
  digitalWrite(in4PinB, LOW);
  digitalWrite(in5PinA, LOW);
  digitalWrite(in6PinA, LOW);
  digitalWrite(in7PinB, LOW);
  digitalWrite(in8PinB, LOW);
}

// Function to move both motors to the right
void moveLeft() {
  analogWrite(A1, 255);
  digitalWrite(13, LOW);
  digitalWrite(in1PinA, HIGH);
  digitalWrite(in2PinA, LOW);
  digitalWrite(in3PinB, HIGH);
  digitalWrite(in4PinB, LOW);
  digitalWrite(in5PinA, LOW);
  digitalWrite(in6PinA, HIGH);
  digitalWrite(in7PinB, HIGH);
  digitalWrite(in8PinB, LOW);
}

// Function to move both motors to the left
void moveRight() {
  analogWrite(A1, 255);
  digitalWrite(in1PinA, LOW);
  digitalWrite(in2PinA, HIGH);
  digitalWrite(in3PinB, LOW);
  digitalWrite(in4PinB, HIGH);
  digitalWrite(in5PinA, HIGH);
  digitalWrite(in6PinA, LOW);
  digitalWrite(in7PinB, LOW);
  digitalWrite(in8PinB, HIGH);
}
void motorRun()
{
  
  Serial.print("13 IR: ");
  Serial.println(digitalRead(13));
  Serial.print("A0 IR:");
  Serial.println(analogRead(A0));
  if (digitalRead(13)==0 || analogRead(A0)<50)
  {
    stats=false;
    Serial.println("grass detected");
    analogWrite(A1, 0);
    delay(10);
  }
  else
  {
    stats=true;
    analogWrite(A1, 255);
    delay(10);

  }
}
bool dist()
{
  digitalWrite(tripin, LOW);
  delayMicroseconds(2);
  digitalWrite(tripin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tripin, LOW);
  long duration = pulseIn(echo, HIGH);
  long distance = duration * 0.0343 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 30) {
    return true;
  }
  else
  {
    return false;
  }

}


void loop() {
  val = dist();
  if (!val) {
    Serial.println("moving forward");
    myservo.write(90);
    moveForward();
    delay(1000);
  }
  else {
    Serial.println("object in front");
    stopMotors();
    myservo.write(0);
    delay(2000);
    val1 = dist();
    if (!val1) {
      Serial.println("Turning Right");
      moveRight();
      delay(2000);
      myservo.write(90);
      moveForward();
      delay(2000);

    }
    else {
      Serial.println("object in Right");
      stopMotors();
      delay(1000);
      myservo.write(180);
      delay(2000);
      val2 = dist();

      if (!val2) {
        Serial.println("turing left");
        moveLeft();
        delay(2000);
        myservo.write(90);
        moveForward();
        delay(2000);

      }
      else {
        Serial.println("objectin Left");
        stopMotors();
        Serial.println("moving backing");
        moveBackward();
        delay(2000);
        stopMotors();
        delay(1000);
        myservo.write(0);
        delay(2000);
        val1 = dist();
        if (!val1) {
          Serial.println("Turning Right");
          moveRight();
          delay(2000);
          myservo.write(90);
          moveForward();
          delay(100);

        }  else {
          Serial.println("object in Right");
          stopMotors();
          myservo.write(180);
          delay(2000);
          val2 = dist();

          if (!val2) {
            Serial.println("turing left");
            moveLeft();
            delay(2000);
            myservo.write(90);
            moveForward();
            delay(2000);

          }
        }
      }
    }
  }
}
