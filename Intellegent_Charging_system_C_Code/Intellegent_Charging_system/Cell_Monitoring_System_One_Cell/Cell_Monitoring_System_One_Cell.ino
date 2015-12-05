#include <SoftwareSerial.h>
#include <Timer.h>

#define CELL1 0   //Analog Pins 0 connected to cell cathode

//Initailize variables
int cellVoltage = 0;  
int cellCurrent = 0;
int dataNumber = 1;
char input = 'z';
int cellNumber = 0;
int time = 0;
boolean comLink = false;
  
/******************** Initialization ****************************/
void setup() {
  //Setup timer

  //Initialize pin modes
  pinMode(INPUT, CELL1);
  comLink = SerialLink();
  // TODO Implement timer////////////////
}


/************************ Main Loop Starts Here*********************/
void loop() {
  cellVoltage = ReadVoltage();
  cellCurrent = ReadCurrent();
  //time = timervalue() or something TOSODO
 
  //Send serial data 
  Serial.print(5); //send time
  Serial.print("*"); //
  Serial.print(6); //cell voltage
  Serial.print("*");
  Serial.print(7); // cell current
  Serial.print("^");
  
  delay(1000); //TODO calculate delay
}


/************* Serial Connection Initailization *************/
boolean SerialLink() {
  Serial.begin(9600);   //Start Serail Connection with Matlab
  Serial.print("*\n");   // Tell matlab to begin with * command
  while(input != '*') {   // wait for handshake signal * from matlab to begin 
  input = Serial.read();
  return true;
  }
}


float ReadVoltage() {
  float voltage = analogRead(CELL1);
  return voltage;
}


int ReadCurrent() {
  // TODO Implement read current
  int current = 0;
  return current;
}


  
  
  
  
  
