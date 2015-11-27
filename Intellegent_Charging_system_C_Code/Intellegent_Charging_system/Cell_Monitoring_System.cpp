

// Initial Arduino Mega Pins
#define CELL1 0   //Analog Pins 0-7 connected to each cell cathode
#define CELL2 1
#define CELL3 2
#define CELL4 3
#define CELL5 4 
#define CELL6 5
#define CELL7 6
#define CELL8 7


/******************** Initialization *****************/
void setup() {
  //Initailize variables
  int cellVoltage[8]= 0;  
  int dataNumber = 1;
  int cellNumber = 1;
  char input;
  
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
  serial.begin(9600);   //Start Serail Connection with Matlab
  serial.print("*\n");   // Tell matlab to begin with * command
  while(input != "*") {   // wait for handshake signal * from matlab to begin 
    input = serial.read();
  }
}



/************************ Main Loop Starts Here*********************/
void loop() {
  for(cellNumber = 0; cellNumber < 7; cellNumber++) { //reads 1 by 1, reads all 7 then moves on
    switch (cellNumber) {
      case 0:  
        cellVoltage[cellNumber] = analogRead(CELL1);
      case 1:
        cellVoltage[cellNumber] = analogRead(CELL2);
      case 2:
        cellVoltage[cellNumber] = analogRead(CELL3);
      case 3:
        cellVoltage[cellNumber] = analogRead(CELL4);
      case 4:
        cellVoltage[cellNumber] = analogRead(CELL5);
      case 5:
        cellVoltage[cellNumber] = analogRead(CELL6);
      case 6:
        cellVoltage[cellNumber] = analogRead(CELL7);
      case 7:
        cellVoltage[cellNumber] = analogRead(CELL8);
    }
  }
  
  for(i = 0; i < 7; i++) {
    serial.write(i); //cell #
    serial.write("*");
    serial.write(cellVoltage[i]); //cell voltage
    serial.write("*");
    serial.write(cellCurrent[i]); //cell voltage
    serial.write("*");
    serial.write(dataNumber); //
    serial.write("^");
  }
  
  dataNumber++;
  delay(1000); //1s
  cellNumber = 0;
 
  for(i = 0; i < 7; i++) {
    cellVoltage[i] = 0; 
  }
}

  
  
  
  
  