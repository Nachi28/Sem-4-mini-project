#include<NewPing.h>
#include <Servo.h>

//Motor setup
int sp_pinA = 9;  //sp_pinA connected to digital pin 3
int sp_pinB = 11;  //sp_pinB connected to digital pin 9
int MOTOR_A1 = 8; // MOTOR_A1 connected to digital pin 4
int MOTOR_A2 = 10; // MOTOR_A2 connected to digital pin 5
int MOTOR_B1 = 12; // MOTOR_B1 connected to digital pin 6
int MOTOR_B2 = 13; // MOTOR_B2 connected to digital pin 7
Servo servo;

//IR setup 
int IR_RIGHT = A0; // RIGHT sensor connected to analog pin A0
int IR_LEFT = A1;  // LEFT sensor connected to analog pin A1
int button = 12;

int ini_x_cordi = 0;
int final_x_cordi = 2; 


//Ultrasonic setup
#define TRIG A2 // TRIG PIN connected to analog pin A2
#define ECHO A3 // ECHO PIN connected to analog pin A3
#define MAX_DISTANCE 200 // Define Maximum Distance
int sp_valueA = 60;
int sp_valueB = 60;
int distance = 100;
NewPing sonar(TRIG, ECHO, MAX_DISTANCE); 

void setup() 
{
  
  Serial.begin(9600);  
  servo.attach(5);
  pinMode(sp_pinA, OUTPUT); // initialize sp_pinA pin as an output
  pinMode(sp_pinB, OUTPUT); // initialize sp_pinB pin as an output
  pinMode(MOTOR_A1, OUTPUT); // initialize MOTOR_A1 pin as an output
  pinMode(MOTOR_A2, OUTPUT); // initialize MOTOR_A2 pin as an output
  pinMode(MOTOR_B1, OUTPUT); // initialize MOTOR_B1 pin as an output
  pinMode(MOTOR_B2, OUTPUT); // initialize MOTOR_B2 pin as an output
  pinMode(IR_RIGHT, INPUT); // initialize RIGHT pin as an input
  pinMode(IR_LEFT, INPUT);  // initialize LEFT pin as an input
  pinMode(button, INPUT_PULLUP);
  servo.write(90);

  Serial.println("Initial X cordi =");
  Serial.println(ini_x_cordi);
  Serial.println("Final X cordi =");
  Serial.println(final_x_cordi);
  go();
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(button, LOW);
  if(digitalRead(button)){
//    Serial.println("high");
    sp_valueA = 80;
    sp_valueB = 80;
   
    //Stop function to reach final destination
    if (!digitalRead(IR_RIGHT) && !digitalRead(IR_LEFT)) 
    {
      Serial.println("X cordi =");
      ini_x_cordi ++;
      Serial.println(ini_x_cordi);
      delay(2000);

      if (ini_x_cordi == final_x_cordi)
      {
        Stop();
        Serial.println("Reached");
        delay(1000);
        exit(0);
      }

//      Stop();
//    delay(300);
    }
    else if (!digitalRead(IR_RIGHT) && digitalRead(IR_LEFT)) 
    {
    Serial.println("left");
    turnLeft();
//  delay(200);
      
    }
    else if (digitalRead(IR_RIGHT) && !digitalRead(IR_LEFT)) 
    {
    Serial.println("right");
    turnRight(); 
//  delay(200); 
    }
    else if (digitalRead(IR_RIGHT) && digitalRead(IR_LEFT)) 
    { 
    Serial.println("forward");
    moveForward();
    delay(10); 
    Stop();
    delay(10);

    }
  }
  else{
  Serial.println("low");
  sp_valueA = 80;
  sp_valueB = 80;
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  }
//  distance = readPing();
//  Serial.println(distance);

  if (distance <= 15)
  {
    Serial.println("object detected");
    Stop();
    Serial.println("Object at X=");
    Serial.println(ini_x_cordi);
    delay(1000);
    moveBackward();
    delay(1000);
    Stop();
    delay(1000);
    
    turnLeft();
    delay(3000);//check time practically
    Stop();
    Serial.println("Reached and avoided the obstacle");
    
    delay(1000);
    exit(0);
  }
  else
  {
    moveForward(); 
  }
   distance = readPing();
}


void Stop() {
//  Serial.println("s");
  analogWrite(sp_pinA, 0);
  analogWrite(sp_pinB, 0);
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);
}

void turnRight() {
//  Serial.println("r");
  analogWrite(sp_pinA, sp_valueA);
  analogWrite(sp_pinB, sp_valueB);
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite(MOTOR_B2, LOW);
  
}

void turnLeft() {
//  Serial.println("l");
  analogWrite(sp_pinA, sp_valueA);
  analogWrite(sp_pinB, sp_valueB);
  digitalWrite(MOTOR_A1, HIGH);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, HIGH);
}

void moveForward() {
//  Serial.println("f");
  analogWrite(sp_pinA, sp_valueA);
  analogWrite(sp_pinB, sp_valueB);
  digitalWrite(MOTOR_A1, HIGH);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite(MOTOR_B2, LOW);
}
void moveBackward() {
  while(digitalRead(IR_RIGHT) && digitalRead(IR_LEFT))
  {
  Serial.println("backwards");
  analogWrite(sp_pinA, sp_valueA);
  analogWrite(sp_pinB, sp_valueB);
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, HIGH);
  }
  
}

int readPing()
{
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void go()
{
  Serial.println("Starting in 3");
  delay(1000);
  Serial.println("Starting in 2");
  delay(1000);
  Serial.println("Starting in 1");
  delay(1000); 
  Serial.println("GOOOOO");
}


//remembaer void loop check one value then move on then starts a new loop...so previous values are gone
//can improve forward function for stepwise with while loop (tooez)
//calibrate motor speeds and all delay times
