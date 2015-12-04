#include <SerialSoftware.h>

// Initial Arduino Mega Pins
#define CELL1 0   //Analog Pins 0-7 connected to each cell cathode
#define CELL2 1
#define CELL3 2
#define CELL4 3
#define CELL5 4 
#define CELL6 5
#define CELL7 6
#define CELL8 7

  int cellVoltage[8] = {0,0,0,0,0,0,0,0};  
  int dataNumber = 1;
  char input = 'z';
  int cellNumber = 0;
  
/******************** Initialization *****************/
void setup() {
  //Initailize variables

  
  //Initialize pin modes
  pinMode(INPUT, CELL1);
  pinMode(INPUT, CELL2);
  pinMode(INPUT, CELL3);
  pinMode(INPUT, CELL4);
  pinMode(INPUT, CELL5);
  pinMode(INPUT, CELL6);
  pinMode(INPUT, CELL7);
  pinMode(INPUT, CELL8); 


  /************* Serial Connection Initailization ******/
  Serial.begin(9600);   //Start Serail Connection with Matlab
  Serial.print("*\n");   // Tell matlab to begin with * command
  while(input != '*') {   // wait for handshake signal * from matlab to begin 
  input = Serial.read();
  }
}



/************************ Main Loop Starts Here*********************/
void loop() {
  for(cellNumber; cellNumber < 8; cellNumber++) { //reads 1 by 1, reads all 7 then moves on
    switch (cellNumber) {
      case 0:  
        cellVoltage[cellNumber] = analogRead(CELL1);
         break;
      case 1:
        cellVoltage[cellNumber] = analogRead(CELL2);
         break;
      case 2:
        cellVoltage[cellNumber] = analogRead(CELL3);
         break;
      case 3:
        cellVoltage[cellNumber] = analogRead(CELL4);
         break;
      case 4:
        cellVoltage[cellNumber] = analogRead(CELL5);
        Serial.println(cellVoltage[cellNumber]);
         break;
      case 5:
        cellVoltage[cellNumber] = analogRead(CELL6);
         break;
      case 6:
        cellVoltage[cellNumber] = analogRead(CELL7);
         break;
      case 7:
        cellVoltage[cellNumber] = analogRead(CELL8);
        break;
    }
  }
  
  for(int i = 0; i < 7; i++) {
    Serial.print(i); //cell #
    Serial.print("*");
    Serial.print(cellVoltage[i]); //cell voltage
    Serial.print("*");
    Serial.print(dataNumber); //
    Serial.print("^");
  }
  Serial.print("%");
  
  dataNumber++;
  delay(1000); //1s
  cellNumber = 0;
 
  for(int i = 0; i < 7; i++) {
    cellVoltage[i] = 0; 
  }
}

  
  
  
  
  
