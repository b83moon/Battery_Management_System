/******************************************************/
// Battery Management System                          //
// Brad Moon, Sean Girard                             //
/******************************************************/

//Included Libraries


// Pin Map 


// Initialize Global Variables 
int chargingCell = 0;


/****************************** Initailize Setup *******************************/
/*******************************************************************************/
void setup() {
  // put your setup code here, to run once:

}


/****************************** Start Main Loop ********************************/
/*******************************************************************************/
void loop() {
  // put your main code here, to run repeatedly:

}



/*************************** Current Mesure Function ***************************/
/*******************************************************************************/
/* This function returns the current from the hall effect sensor */
float PackCurrent() {
  return current;
}

/*************************** Charge Cell Function ******************************/
/*******************************************************************************/
/* This function charges the arguement cell. This function takes in a cell 
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
  votage = ADCVoltage();
  
  // Check to see if cell was charging
  if (chargingCell ~= 0) {
    SwitchToCell(chargingCell);
    ChargeEngage(true);
  }
  return voltage;
}







/***********************************************************************************/
/**Dont use these functions they are for inside the above fucntions that I will use*/
/***********************************************************************************/


/*************************** Charger Engage Function ***************************/
/*******************************************************************************/
/* This function takes in a boolean to charge or turn off charging to the cells
 *  It returns a boolean that is its state. This function effects switch S0 */
boolean ChargerEngage( boolean charging) {
  return charging;
}

/*************************** Cell Switching Function ***************************/
/*******************************************************************************/
/* This Function will turn on or off the appropraite switches to access the given cell 
 * number. Switching to cell 1 will turn on switches S1 and S2 etc. Cell 0 turns 
 * off all cells */
void SwitchToCell(int cell) {
}

