/******************************************************/
// Battery Management System                          //
// Brad Moon, Sean Girard                             //
// 2016                                               //
/******************************************************/

//Included Libraries
#include <Wire.h>
#include <MCP3221.h>

// Pin Map 
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7
#define S8 8
#define S0 9
#define switchSpeed 50

// Initialize Global Variables 
int chargingCell = 0;
float voltCell = {0,0,0,0};
int activeCell = -1;
float DeltaV = 0;
const byte i2cAddress = 0x4E;  
const float currentThresh = 0.5;  // [A]
const int I2CadcVRef = 4880;
MCP3221 i2cADC(i2cAddress, I2CadcVRef);


/****************************** Initailize Setup *******************************/
/*******************************************************************************/
void setup() {
  // put your setup code here, to run once:
pinMode(S0, OUTPUT);
pinMode(S1, OUTPUT);
pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);
pinMode(S4, OUTPUT);
pinMode(S5, OUTPUT);
pinMode(S6, OUTPUT);
pinMode(S7, OUTPUT);
pinMode(S8, OUTPUT);

Wire.begin();

}


/****************************** Start Main Loop ********************************/
/*******************************************************************************/
void loop() {
  // put your main code here, to run repeatedly:

if (weakCell != -1) {
  DeltaV = Compare(weakCell, *voltCell);
  int activeCell = weakCell;  

  while ( (DeltaV > Vthresh) && (activeCell == weakCell) ) {
    chargeCell(weakCell);
    delay(charge_amount);
    voltCell = GetAllVolts(*voltCell);
    activeCell = FindWeak(*voltCell);
    DeltaV = Compare(weakCell, *voltCell)
  }
  ChargeCell(0);
  activeCell = -1;
}


}


/*************************** Current Measure Function ***************************/
/*******************************************************************************/
/* This function returns the current from the hall effect sensor ACS716 */
float PackCurrent() {
 float analogVoltage = analogRead(CurrentSensor)*5.000/1024.000;
 Serial.print("Analog Voltage: ");
 Serial.println(analogVoltage);
 current = (analogVoltage - 337.97) / 3.787;
 return current;
}


/*************************** Charge Cell Function ******************************/
/*******************************************************************************/
/* This function charges the argument cell. This function takes in a cell 
 * value of 1-4 for each cell and then 0 to turn off charging */
void ChargeCell(int cell) {
   SwitchToCell(cell);
  if (cell != 0) {
    ChargeEngage(true);
  else {
    ChargeEngage(false);
  }
    //Global Variable
    chargingCell = cell;
}

/*************************** Cell Voltage Function *****************************/
/*******************************************************************************/
/* This function returns the voltage of the given cell, It will record the cell 
 * voltage and then continue charging the cell that was previously charging prior 
 * to the voltage read. cell value can be 1-4 */
float CellVoltage(int cell) {
  ChargeEngage(false);
  SwitchToCell(cell);
  delay(switchSpeed);
  votage = ADCVoltage();
  
  // Check to see if a cell was charging
  if (chargingCell ~= 0) {
    SwitchToCell(chargingCell);
    ChargeEngage(true);
  }
  return voltage;
}



/***********************************************************************************/
/* Dont use these functions they are for inside the above functions that I will use*/
/***********************************************************************************/


/*************************** Charger Engage Function ***************************/
/*******************************************************************************/
/* This function takes in a boolean to charge or turn off charging to the cells
 *  It returns a boolean that is its state. This function effects switch S0 */
void ChargeEngage( boolean charging) {
  if (charging == true) {
      digitalWrite(S0, HIGH);
  } else {
    digitalWrite(S0, LOW);
  }
}

/*************************** Cell Switching Function ***************************/
/*******************************************************************************/
/* This Function will turn on or off the appropraite switches to access the given cell 
 * number. Switching to cell 1 will turn on switches S1 and S2 etc. Cell 0 turns 
 * off all cells */
void SwitchToCell(int cell) {
  switch (cell) {

    case 0:
      digitalWrite(S1, LOW);
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      digitalWrite(S4, LOW);
      digitalWrite(S5, LOW);
      digitalWrite(S6, LOW);
      digitalWrite(S7, LOW);
      digitalWrite(S8, LOW);
    break;

    case 1:
      digitalWrite(S3, LOW);
      digitalWrite(S4, LOW);
      digitalWrite(S5, LOW);
      digitalWrite(S6, LOW);
      digitalWrite(S7, LOW);
      digitalWrite(S8, LOW);
      
      delay(100);

      digitalWrite(S1, HIGH)
      digitalWrite(S2, HIGH);
    break;

    case 2:
      digitalWrite(S1, LOW);
      digitalWrite(S2, LOW);
      digitalWrite(S5, LOW);
      digitalWrite(S6, LOW);
      digitalWrite(S7, LOW);
      digitalWrite(S8, LOW);
      
      delay(100);

      digitalWrite(S3, HIGH)
      digitalWrite(S4, HIGH);
    break;
    
    case 3:
      digitalWrite(S1, LOW);
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      digitalWrite(S4, LOW);
      digitalWrite(S7, LOW);
      digitalWrite(S8, LOW);
      
      delay(100);

      digitalWrite(S5, HIGH)
      digitalWrite(S6, HIGH);
    break;
    
    case 4:
      digitalWrite(S1, LOW);
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      digitalWrite(S4, LOW);
      digitalWrite(S5, LOW);
      digitalWrite(S6, LOW);
      
      delay(100);

      digitalWrite(S7, HIGH)
      digitalWrite(S8, HIGH);
    break;
  }
} 


/*************************** Get ADC Voltage Reading ***************************/
/*******************************************************************************/
/* Retrieves the output from the ADC */

float ADCVoltage() {
 float voltage;

 int adcRaw = i2cADC.readI2CADC();

 // Convert reading to voltage
 voltage = adcRaw / 4096 * I2CadcVRef;
 return voltage;
}


/*************************** Find a Weak Cell **********************************/
/*******************************************************************************/
/* Looks for the cell with the lowest voltage, compared to the other cells.    */

int FindWeak(voltCell) {
  float DeltaVarray[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
  float maxDeltaV = 0;
  int iMax = 0;
  int jMax = 1;

  // Enumerate the DeltaVarray
  for (i = 0, i < 3, i = i + 1) {
    for (j = i + 1, j < 4, j = j + 1) {
      DeltaVaray[i][j] = voltCell[j] - voltCell[i]
    }
  }

  // Find the cell with the lowest voltage
  for (i = 0, i < 3, i = i + 1) {
    for (j = i +1, j < 4, j = j + 1) {
      if (abs(DeltaVarray[i][j]) > abs(DeltaVarray[iMax][jMax]) ) 
      {
        maxDeltaV = DeltaVarray[i][j];
        iMax = i;
        jMax = j;
      }
      else
      }
    }
    if(sign(DeltaVarray[iMax][jMax]) > 0) {
      weakCell = jMax;
    } else if(sign(DeltaVarray[iMax][jMax] < 0)) {
      weakCell = iMax;
    } else
    weakCell = -1;
  }


/*************************** Measures all Cell Voltages ************************/
/*******************************************************************************/
/* Measures the voltage of each cell and returns an array of voltages.         */

void GetAllVolts(float *voltCell) {
  int i = 0;

  for(i = 0, i < 4, i = i + 1) {
    voltCell[i-1] = cellVoltage[i];
  }
} 


/*************************** Compares Weak Cells to Average*********************/
/*******************************************************************************/
/* Given a weak cell. Finds the difference between the weak cell's voltage and  */
/* the average of the voltages of the other cells. */

float Compare (weakCell, voltCell) {
  float Vsum = 0;
  float Vavg = 0;
  float DeltaV = 0;

  for(i = 0, i < 4, i = i + 1) {
    if (i != weakCell) {
      Vsum = Vsum + voltCell[i];
    }
    else
  }
  Vavg = Vsum / 3;
  DeltaV = Vavg - voltCell[weakCell];
  return DeltaV;
}


