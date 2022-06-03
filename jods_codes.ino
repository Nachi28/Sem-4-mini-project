#include<NewPing.h>

//Motor setup
int sp_pinA = 9;  
int sp_pinB = 11;  
int MOTOR_A1 = 8; 
int MOTOR_A2 = 10;
int MOTOR_B1 = 12; 
int MOTOR_B2 = 13; 

//IR setup 
int IR_RIGHT = A0; 
int IR_LEFT = A1; 
int button = 12;

//change the initial and final posi as user wants
int ini_x_cordi = 0;
int final_x_cordi = 2; 


//Ultrasonic setup
#define TRIG A2
#define ECHO A3 
#define MAX_DISTANCE 200
int sp_valueA = 85;
int sp_valueB = 85;
int distance = 100;

//NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]);
NewPing sonar(TRIG, ECHO, MAX_DISTANCE); 

void setup() 
{
  
  Serial.begin(9600);  
  pinMode(sp_pinA, OUTPUT); 
  pinMode(sp_pinB, OUTPUT); 
  pinMode(MOTOR_A1, OUTPUT); 
  pinMode(MOTOR_A2, OUTPUT); 
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT); 
  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_LEFT, INPUT);
  
  //pullup is for button ie.continously checks values ig
  pinMode(button, INPUT_PULLUP);
  Serial.println("Initial X cordi =");
  Serial.println(ini_x_cordi);
  Serial.println("Final X cordi =");
  Serial.println(final_x_cordi);
  go();
}

void loop() {
//  Serial.println(analogRead(A0));
    sp_valueA = 85;
    sp_valueB = 85;
   
    //Acts like Stop function and counts crosses to reach final destination
    if (analogRead(A0)<200 && analogRead(A1)<200) 
    {
      Serial.println("X cordi =");
      ini_x_cordi ++;
      Serial.println(ini_x_cordi);
      delay(100);

      if (ini_x_cordi == final_x_cordi)
      {
        Stop();
        Serial.println("Reached");
        delay(1000);
        exit(0);
      }

      Stop();
    delay(300);
    }
    else if (analogRead(A0)<200 && analogRead(A1)>200) 
    {
    Serial.println("right");
    turnRight(); 
//  delay(200); 
      
    }
    else if (analogRead(A0)>200 && analogRead(A1)<200) 
    {
    Serial.println("left");
    turnLeft();
//  delay(200);
    }
    else if (analogRead(A0)>200 && analogRead(A1)>200) 
    { 
    Serial.println("forward");
    moveForward();
    delay(10); 
    Stop();
    delay(10);

    }
  
  sp_valueA = 85;
  sp_valueB = 85;
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  
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

    delay(100);
    Stop();
    delay(1000);
    
    turnLeft();//right or left...
    delay(1500);//check delay time practically
    Stop();
    Serial.println("Reached and avoided the obstacle");
    
    delay(1500);
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
  Serial.println("hi");
  while(analogRead(A0)>200 && analogRead(A1)>200)
  {
        
  Serial.println("backwards");
  analogWrite(sp_pinA, sp_valueA);
  analogWrite(sp_pinB, sp_valueB);
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, HIGH);
  }
  Serial.println("end");
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

void go(void)
{
  Serial.println("Starting in 3");
  delay(1000);
  Serial.println("Starting in 2");
  delay(1000);
  Serial.println("Starting in 1");
  delay(1000); 
  Serial.println("GOOOOO");
}
