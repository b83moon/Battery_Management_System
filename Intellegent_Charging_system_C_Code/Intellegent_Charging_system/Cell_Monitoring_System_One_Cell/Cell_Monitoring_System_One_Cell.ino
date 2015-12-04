#include <SerialSoftware.h>
#include <Timer.h>
// Initial Arduino Mega Pins
#define CELL1 0   //Analog Pins 0 connected to cell cathode

//Initailize variables
int cellVoltage = 0;  
int cellCurrent = 0;
int dataNumber = 1;
char input = 'z';
int cellNumber = 0;
int time = 0;
  
/******************** Initialization ****************************/
void setup() {
  //Setup timer
  
  //Initialize pin modes
  pinMode(INPUT, CELL1);
  SerialLink();
  // TODO Implement timer////////////////
}


/************************ Main Loop Starts Here*********************/
void loop() {
  cellVoltage = ReadVoltage();
  cellCurrent = ReadCurrent();
  //time = timervalue() or something TOSODO
 
  //Send serial data 
  Serial.print(time); //send cell #
  Serial.print("*"); //
  Serial.print(cellVoltage); //cell voltage
  Serial.print("*");
  Serial.print(cellCurrent); //
  Serial.print("^");
  
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

int ReadCurrent() {
  // TODO Implement read current
  int current = 0;
  
  
  return current;
}


  
  
  
  
  
