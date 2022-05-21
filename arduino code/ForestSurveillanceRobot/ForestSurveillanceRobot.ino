
//*****************************************************************************************************************
//        FOREST SURVEILLANCE ROBOT                                                                               **
//        |-->  PROTOTYPE 1                                                                                        ***
//                                                                                                                ****
//                                                                                                                ***
//                                                                                                                **
//*****************************************************************************************************************
/*to do list
  -ADD REQUIRED VARIABLES
  -CHANGE COMPASS VARIABLES
  -ADD SETUP FUNCTIONS
  -CHECK FLOW FOR EVERY STATE
*/
#include <StateMachine.h>
#include "Wire.h"                                                 // Used by I2C
//#include "I2Cdev.h"                                             // I2C Communications Library (used for compass)
#include "MPU9250.h"                                             // Library for the accelerometer & gyro
//#include <Servo.h>                                                // Servo library to control Servo arm for metal detector
//#include <SoftwareSerial.h>                                       // Software Serial for Serial Communications - not used
#include <TinyGPS++.h>
#include "DHT.h"

//******************************************************************************************************
// Compass Variables & Setup (CHANGE COMPASS VALUES)
int16_t mx, my, mz;                                                // variables to store x,y,z axis from compass (HMC5883L)
int desired_heading;                                               // initialize variable - stores value for the new desired heading
int compass_heading;                                               // initialize variable - stores value calculated from compass readings
int compass_dev = 5;                                               // the amount of deviation that is allowed in the compass heading - Adjust as Needed
                                                                   // setting this variable too low will cause the robot to continuously pivot left and right setting this variable too high will cause the robot to veer off course
int Heading_A;                                                     // variable to store compass heading
int Heading_B;                                                     // variable to store compass heading in Opposite direction
int pass = 0;                                                      // variable to store which pass the robot is on
//*********/*********************************************************************************************
int trigL = 24;
int echoL = 25;
int trigR = 23;
int echoR = 22;

int durationL = 0;
int distanceL = 0;
int durationR = 0;
int distanceR = 0;

//******************************************************************************************************
#define DHTTYPE DHT11
#define DHTPIN 26
DHT dht(DHTPIN, DHTTYPE);
//******************************************************************************************************
//SoftwareSerial Serial2(2, 3); // RX, TX of GPS
MPU9250 mpu;
//******************************************************************************************************                                                                  
// GPS Variables & Setup

int GPS_Course;                                                    // variable to hold the gps's determined course to destination
int Number_of_SATS;                                                // variable to hold the number of satellites acquired
TinyGPSPlus gps;                                                   // gps = instance of TinyGPS 
                                                                   // pin 17 (blue)   is connected to the TX on the GPS
                                                                   // pin 16 (yellow) is connected to the RX on the GPS
//*****************************************************************************************************
// GPS Locations
unsigned long Distance_To_Home;                                    // variable for storing the distance to destination
int ac =0;                                                         // GPS array counter
int wpCount = 0;                                                   // GPS waypoint counter
double Home_LATarray[50]={19.183426, 19.182836};                                          // variable for storing the destination Latitude - ENTER LAT, LONG HERE
double Home_LONarray[50]={72.993357, 72.993865};                                          // variable for storing the destination Longitude - up to 50 waypoints
//*****************************************************************************************************
//state machine pointers for linked list
StateMachine machine = StateMachine();
State* S11 = machine.addState(&rest);
State* S5 =machine.addState(&traveller);
State* S6 = machine.addState(&scan);
State* S7 = machine.addState(&followme);
State* S8 =machine.addState(&rth);
State* S9 =machine.addState(&firefighter);
State* S10 = machine.addState(&manual);
State* S12 = machine.addState(&obsavoid);
//*****************************************************************************************************
int pwmR = 10;
int pwmL = 11;
int enR = 12;
int enL = 13;
int forwardD= 500;
int pin1 = 5;
int pin2 = 6;
int pin3 = 7;
int pin4 = 8;
int val[4];
int comm;
int increment = 0;
int obs=0;
int fire_flag=1;


void setup() {                                                            //add stuff
Serial.begin(115200);
Serial2.begin(9600);                                             // Serial 2 is for GPS communication at 9600 baud - DO NOT MODIFY - Ublox Neo 6m 
pinMode(pwmR, OUTPUT);
pinMode(pwmL, OUTPUT);
pinMode(enR, OUTPUT);
pinMode(enL, OUTPUT);
pinMode(pin1, INPUT);
pinMode(pin2, INPUT);
pinMode(pin3, INPUT);
pinMode(pin4, INPUT);
pinMode(4, OUTPUT);

//state management setup

S11->addTransition(&transitionS11S5,S5);
S11->addTransition(&transitionS11S6,S6);
S11->addTransition(&transitionS11S7,S7);
S11->addTransition(&transitionS11S8,S8);
S11->addTransition(&transitionS11S9,S9);
S11->addTransition(&transitionS11S10,S10);
//S11->addTransition(&transitionS11,S11);
S5->addTransition(&transitionS5S11,S11);
S5->addTransition(&transitionS5S12,S12);                          //FOR OBSTACLE AVOIDANCE MODE
S6->addTransition(&transitionS6S11,S11);
S7->addTransition(&transitionS7S11,S11);
S8->addTransition(&transitionS8S11,S11);
S9->addTransition(&transitionS9S11,S11);
S9->addTransition(&transitionS9S10,S10);
S10->addTransition(&transitionS10S11,S11);
S10->addTransition(&transitionS10S9,S9);
S12->addTransition(&transitionS12S5,S5);

MPUSetup();
dht.begin();
//Startup();                                                       // Run the Startup procedure on power-up one time
}

//transition conditions-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool transitionS11S5(){
  if(comm == 5){
    return true;
  }
  return false;
  }

bool transitionS9S10(){
  if(comm == 10){
    return true;
  }
  return false;
  }
  
bool transitionS11S6(){
  if(comm == 6){
    return true;
  }
  return false;
  }
bool transitionS11S7(){
  if(comm == 7){
    return true;
  }
  return false;
  }
bool transitionS11S8(){
  if(comm == 8){
    return true;
  }
  return false;
  }
bool transitionS11S9(){
  if(comm == 9){
    return true;
  }
  return false;
  }
bool transitionS11S10(){
  if(comm == 10){
    return true;
  }
  return false;
  }
bool transitionS5S11(){
  if(comm == 11 || comm==15 ){
    return true;
  }
  return false;
  }
bool transitionS5S12(){
  if(obs == 1  ){
    return true;
  }
  return false;
  }
bool transitionS6S11(){
  if(comm == 11 || comm==15 ){
    return true;
  }
  return false;
  }
bool transitionS10S9(){
  if(comm == 9  ){
    return true;
  }
  return false;
  }  
bool transitionS7S11(){
  if(comm == 11 || comm==15){
    return true;
  }
  return false;
  }
bool transitionS8S11(){
  if(comm == 11 || comm==15){
    return true;
  }
  return false;
  }
bool transitionS9S11(){
  if(comm == 11 || comm==15){
    return true;
  }
  return false;
  }
bool transitionS10S11(){
  if(comm == 11 || comm==15){
    return true;
  }
  return false;
  }
bool transitionS11(){
  if(comm == 11){
    return true;
  }
  return false;
  }
bool transitionS12S5(){
  if(obs == 0  ){
    return true;
  }
  return false;
  }
  
void controls(int com){
  switch(com) {
  case 1:
    leftscan(175,100); 
    break;
  case 2:
    rightscan(175,100);
    break;
  case 3:
    backward();
    break;
  case 4:
    Forward(150, 100);
  break;
  default:
  Serial.println("DEF");
  StopCar();
}
}

//the states are mentioned below --------------------------------------------------------------------------------------------------------------------------------
//REST
void rest(){
  Serial.println("rest");
  StopCar();
  }
  
void scan(){
int i=0;
Serial.println("scan");
for(int i=0; i<2; i++){
Forward(150, 100);
delay(forwardD);
rightscan(200, 700);
Forward(150, 100);
delay(forwardD);
rightscan(200, 700);
Forward(150, 100);
delay(forwardD);
leftscan(200,700);
Forward(150, 100);
delay(forwardD);
leftscan(200,700);
}
StopCar();
}

//MANUAL
void manual(){
  Serial.println("manual");
  controls(comm);

//getDHT();
if(fire_flag==1 && comm==13)
{
  comm=9;
  }
  }

//FOLLOWME
void followme(){
  Serial.println("followme");
  controls(comm);
  }

//TRAVELLER
void traveller(){
  Serial.println("traveller");
  Startup(); 
  Ping();
  getGPS();                                                        // Update the GPS location
  getCompass();                                                    // Update the Compass Heading
  goWaypoint();
}

void obsavoid(){
  Serial.println("avoiding obstacle");
  obstacleavoidance(distanceL, distanceR);
}

void rth(){
Serial.println("return to home");
}
void firefighter(){
  beep(9);
Serial.println("fire fighter");
//getDHT();
digitalWrite(4, HIGH);
delay(2000);
digitalWrite(4, LOW);
}

//Function to read comms
int ReadComm()
{
val[0] = digitalRead(pin1);
val[1] = digitalRead(pin2);
val[2] = digitalRead(pin3);
val[3] = digitalRead(pin4);
for(int i=0; i<4;i++)
{
Serial.print( val[i] );
}
comm= bi2dec(val);
Serial.println(' ');
Serial.print("comm:");
Serial.println(comm);
delay(500);
return comm;
}

//Function to convert Binary (input from Raspberry Pi) to Decimal--------------------------------------------------------------------------------------------------------------------------
int bi2dec(int val[]) {
int c;
c=val[0]+(2*val[1])+(4*val[2])+(8*val[3]);
return c;
}

//the loop--------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
 comm=ReadComm();
 machine.run();
}


void beep(int com){
  for(int i=0; i<com;i++){
  digitalWrite(4, HIGH);
  delay(200);
  digitalWrite(4, LOW);
  delay(200);
  }
  }
