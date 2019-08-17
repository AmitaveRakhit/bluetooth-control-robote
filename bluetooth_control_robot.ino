#include <SoftwareSerial.h>
SoftwareSerial android(7, 8);
char command ;
int motorR1 = 3;
int motorR2 = 5;
int motorL1 = 6;
int motorL2 = 11;
int trigPin = 9;
int echoPin = 10;
long duration;
int distance;
int data;
void setup() {
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  android.begin(9600);// Starts the serial communication
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println("CM");

  if (android.available())
  {
    command = android.read();
    android.println(command);
    Serial.println(command);
  }

  // for bluetooth

  analogWrite(motorR1, 0);
  analogWrite(motorR2, 0);
  analogWrite(motorL1, 0);
  analogWrite(motorL2, 0);

  if (distance >= 10)
  {

    if (command == '1') //forward
    {
      analogWrite(motorR1, 50);
      analogWrite(motorR2, 0);
      analogWrite(motorL1, 50);
      analogWrite(motorL2, 0);

    }

    else if (command == '3') //Left
    {
      analogWrite(motorR1, 80);
      analogWrite(motorR2, 0);
      analogWrite(motorL1, 20);
      analogWrite(motorL2, 0);

    }
    else if (command == '4') //Right
    {
      analogWrite(motorR1, 20);
      analogWrite(motorR2, 0);
      analogWrite(motorL1, 80);
      analogWrite(motorL2, 0);

    }
    else if (command == 'E') //stop
    {
      analogWrite(motorR1, 0);
      analogWrite(motorR2, 0);
      analogWrite(motorL1, 0);
      analogWrite(motorL2, 0);

    }
  }
  if (distance < 15)//all motor off
  {
    analogWrite(motorR1, 0);
    analogWrite(motorR2, 0);
    analogWrite(motorL1, 0);
    analogWrite(motorL2, 0);
    // digitalWrite(spker, HIGH);
  }
  if (command == '2') //Reverse
  {
    analogWrite(motorR1, 0);
    analogWrite(motorR2, 50);
    analogWrite(motorL1, 0);
    analogWrite(motorL2, 50);
    //digitalWrite(spker, LOW);
  }

  //command = 's';

}

