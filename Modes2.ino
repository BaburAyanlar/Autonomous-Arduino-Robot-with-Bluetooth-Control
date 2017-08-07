/* Declare included libraries*/
#include <AFMotor.h>
#include <LiquidCrystal.h>
/*Declare Motor objects*/
AF_DCMotor motorleft(4);
AF_DCMotor motorright(1);
LiquidCrystal lcd(26, 27, 28, 29, 30, 31);
/*Declare variables for storing the last time robot turned*/
long timesinceturnedleft = 0;
long timesinceturnedright = 0;
long timesince = 0;

int distancelimit = 20; //Change this variable to change the sensitivity of detetcting obstacles
/*left sensor pins*/
const int trigPinl = 47;
const int echoPinl = 46;

int speeed = 180;
/*right sensor pins*/
const int trigPinr = 24;
const int echoPinr = 25;
/*front sensor pins*/
const int trigPinb = 41;
const int echoPinb = 40;

long oldtime = 0;
/*boolean variable setup for mode selection*/
boolean Manual = false;
boolean Auto = false;
boolean Both = false;
/*bluetooth commands will be stored in these character variables*/
char command;
char commandreset;

void setup()
{
lcd.begin(16,2);
Serial.begin(9600); //Serial comm with cable for debugging, not necessary for robot
Serial1.begin(9600); // Starts the serial communication over bluetooth
Serial.println("Set mode now");
pinMode(trigPinl, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPinl, INPUT); // Sets the echoPin as an Input
pinMode(trigPinr, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPinr, INPUT); // Sets the echoPin as an Input
pinMode(trigPinb, OUTPUT);
pinMode(echoPinb, INPUT);
delay(1000);
lcd.print("Set Mode");
Serial1.print("Input 'M' for Manual, 'A' for Auto and 'B' for both");
while (!Serial1.available())
{
   ;//do nothing when no bluetooth communication is available
}
command = char(Serial1.read()); //Read character sent over bluetooth for setting initial mode

switch (command)
{
  case 'M':
  {
  Manual = true;// Manual Mode on
  lcd.clear();
  lcd.print("M");
  Serial.print("M");
  break;
  }
  case 'A':
  {
  Auto = true; //Autonomous mode on
  lcd.clear();
  lcd.print("A");
  Serial.print("A");
  break;
  }
  case 'B':
  {
  Both = true; //Autonomous mode + manual inputs on
  lcd.clear();
  lcd.print("B");
  Serial.print("B");
  break;
  }
  default:
  {
  Serial1.print("Try again");
  lcd.print(":(");
  }
}
}
void loop()
{ 
  motorleft.setSpeed(speeed);
  motorright.setSpeed(speeed);
  //following while loop determines what the robot will do if there IS an available bluetooth connection
  while (Serial1.available()>0)
  {
    command = Serial1.read();
    if (Manual == true)
    {
      switch (command)
      {
        case 'f':
       go();
       break;
     case 'b':
        back();
       break;
     case 'l':
       left();
       break;
     case 'r':
       right();
       break;
     case 's':
       stopp();
       case 'u':
       speeed += 20;
       case 'd':
       speeed -= 0;
       case 'x':
       Reset();
      }
    }
    else if (Both == true)
    {
      switch (command)
      {
        case 'f':
       go();
       delay(2500);
       break;
     case 'b':
        back();
        delay(2500);
       break;
     case 'l':
       left();
       delay(2500);
       break;
     case 'r':
       right();
       delay(2500);
       break;
     case 's':
       stopp();
       delay(2500);
       case 'u':
       speeed += 20;
       case 'd':
       speeed -= 0;
       case 'x':
       Reset();
      }
    }
    else if (Auto == true) //For autonomous mode, the only bluetooth commands we accept are for increasing speed, decreasing speed or reseting mode
    {
      switch (command)
      {
        case 'u': speeed += 20;
        case 'd': speeed -= 20;
        case 'x': Reset();
      }
   
    }
  }
  //following while loop determines what the robot will do if there is NO bluetooth connection
  while (Serial1.available() == 0)
  {
    if( Auto == true || Both == true)
    {
      go();
     if(distanceDetect(trigPinl, echoPinl)<distancelimit){
     if (millis()<timesinceturnedleft + 2500){
       lcd.print("Turning right long");
       motorright.run(BACKWARD);
       motorleft.run(BACKWARD);
       delay(1500);
       motorright.run(BACKWARD);
       motorleft.run(FORWARD);
       delay(2000);
     }
     else{
       lcd.print("Turning right short");
       motorright.run(BACKWARD);
       motorleft.run(FORWARD);
       delay(500);
     }
       timesinceturnedright = millis();
     }


     if(distanceDetect(trigPinr, echoPinr)<distancelimit){
       if(millis()<timesinceturnedright + 2500){
         lcd.print("Turning left long");
         motorright.run(BACKWARD);
         motorleft.run(BACKWARD);
         delay(1500);
         motorright.run(FORWARD);
         motorleft.run(BACKWARD);
         delay(2000);
     }
     else{
       lcd.print("Turning left short");
       motorright.run(FORWARD);
       motorleft.run(BACKWARD);
       delay(500);
     }
       timesinceturnedleft = millis();
     }
     if(distanceDetect(trigPinb, echoPinb)<distancelimit)
     {
       lcd.print("Going back");
       motorright.run(BACKWARD);
       motorleft.run(BACKWARD);
       delay(2500);
       stopp();
     }
  }
  else if (Manual == true)
  {
    //Manual mode can't do anything if there is no bluetooth connection
    }
  }
}

int distanceDetect (int trig, int echo)
{
    long duration;
    int distance;          //Variable to store distance from an object

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echo, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    return distance;
}
void go()
{
  motorright.run(FORWARD);
  motorleft.run(FORWARD);
}
void stopp()
{
  motorleft.run(RELEASE);
  motorright.run(RELEASE);
}
void left()
{
  motorright.run(FORWARD);
  motorleft.run(BACKWARD);
}
void right()
{
  motorright.run(BACKWARD);
  motorleft.run(FORWARD);
}
void back()
{
  motorright.run(BACKWARD);
  motorleft.run(BACKWARD);
}
void Reset()
{
  motorright.run(RELEASE);
  motorleft.run(RELEASE);
  Manual = false;
  Auto = false;
  Both = false;
  lcd.print("reset mode now");
  Serial.print("reset mode now");
  if (Serial1.available())
  {
    command = Serial1.read();
    switch(command)
    {
      case 'M': Manual = true;
      case 'A': Auto = true;
      case 'B': Both = true;
    }
  }
}

