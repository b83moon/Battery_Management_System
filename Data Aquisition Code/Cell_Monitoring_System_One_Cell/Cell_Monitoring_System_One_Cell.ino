#include <SoftwareSerial.h>

// Initial Arduino Mega Pins
#define CELL1 0   //Analog Pins 0 connected to cell cathode
#define CurrentSensor 3



//Initailize variables
int cellVoltage = 2;  
unsigned long time1 = millis();
int cellCurrent = 45;
char input = 'z';
int cellNumber = 1234;
  
/******************** Initialization ****************************/
void setup() {
  //Setup timer
  
  //Initialize pin modes
  pinMode(INPUT, CELL1);
  pinMode(CurrentSensor, INPUT);
  
  SerialLink();
  // TODO Implement timer////////////////
}


/************************ Main Loop Starts Here*********************/
void loop() {
//  cellVoltage = ReadVoltage();
  CurrentMeasure();
  time1 = millis();
 
  //Send serial data 
  Serial.print("&\n"); //send cell #
  Serial.println(cellVoltage); //
  Serial.println(cellCurrent); //cell voltage
  Serial.println(time1/1000);
  delay(1000); //TODO calculate delay
}


/************* Serial Connection Initailization *************/
int SerialLink() {
  Serial.begin(9600);   //Start Serail Connection with Matlab
  Serial.print("*\n");   // Tell matlab to begin with * command
  while(input != '*') {   // wait for handshake signal * from matlab to begin 
  input = Serial.read();
  }
}


int ReadVoltage() {
  return analogRead(CELL1);
}


float CurrentMeasure() { 
  float analogVoltage = 0;
  float current = 0;
  analogVoltage = analogRead(CurrentSensor)*5.000/1024.000;
  Serial.print("Analog Voltage: ");
  Serial.println(analogVoltage);
  current = (analogVoltage-337.97)/3.787;
  return current;
}

  
  
  
  
  
