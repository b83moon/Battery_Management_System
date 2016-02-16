
/******************************************************/
// Cell Balancing System                              //
// Based on measured current, controls DCDC Converter //
// Jan 11, 2016                                       //
// Sean Girard, Brad Moon                             //
/******************************************************/

#include <Wire.h>
#include <MCP3221.h>
#define MOSFET 10
#define LED 13

// Define Importanct Variables
const byte i2cAddress = 0x4E;  
const float currentThresh = 0.5; // [A]
int IterationNumber = 0;
const int I2CadcVRef = 4880;
MCP3221 i2cADC(i2cAddress, I2CadcVRef);




/*************************** Initailize Setup **********************************/
/*******************************************************************************/
void setup() {
    
  // Set up pins
  pinMode(MOSFET, OUTPUT);
  pinMode(LED, OUTPUT);

  // Set up Serial Connection
  Serial.begin(9600);
  Serial.println("Setup Complete.");

  // Setup I2C Connection
  Wire.begin();

  // Enable MOSFET for main Circuit Loop
  digitalWrite(MOSFET, HIGH);
  digitalWrite(LED, HIGH);

  // Allow time for DC_Converter to turn on
  delay(2000);
  Serial.println("DC_Converter ON");
  Serial.println("");

  //Initailize Loop

}


/*************************** Start Main Loop ***********************************/
/*******************************************************************************/

void loop() {
  int current = CurrentMeasure();
  delay(2000);
  
  // Disable DC_Converter when current falls below cut-off
  if (avgCurrent < currentThresh) {
    IterationNumber++;
    Serial.print("Current Threshold Reached : ");
    Serial.print(IterationNumber);
    Serial.println(" times.");
    if (IterationNumber == 3){
      digitalWrite(MOSFET, LOW);
      digitalWrite(LED, LOW);
      Serial.println("Current cut-off point reached.");
      Serial.println("Cut off Circuit Loop");
      while (true){
        int currentMeasure();
        if (current > 0.00001 ) {
          Serial.println("Warning! MOSFET Failed to turn off circuit!");
          delay(1000);
        } else {
          Serial.println("MOSFET Porperly Turned off Circuit :)");
          while (true);
        }
      }
    }
  } else {
    IterationNumber = 0;
  } 
}


/*************************** Current Mesure Function ***************************/
/*******************************************************************************/
float CurrentMeasure() { 
  // Define Variables
  float avgCurrent = 0;
  int avgAdcRaw = 0;
  float avgVoltage = 0;
  float current = 0;
  int adcRaw = 0;
  float voltage = 0;
  // Read & print ADC output
   adcRaw = i2cADC.readI2CADC();
   avgAdcRaw = i2cADC.calcRollingAVG(); 
  Serial.print("ADC: ");
  Serial.print(adcRaw);
  Serial.println("/4096.");

  // Calculate & print current
  //Average
  avgVoltage = (avgAdcRaw/4096.0)*I2CadcVRef/1000.0;
  Serial.print("Average Voltage: ");
  Serial.print(avgVoltage, 8);
  Serial.println(" V.");
  avgCurrent = avgVoltage/0.3;
  Serial.print("Average Current: ");
  Serial.print(avgCurrent, 8);
  Serial.println(" A.");
  //Instantaneous
  voltage = (adcRaw/4096.0)*I2CadcVRef/1000.0;
  Serial.print("Voltage: ");
  Serial.print(voltage, 8);
  Serial.println(" V.");
  current = voltage/0.3;
  Serial.print("Current: ");
  Serial.print(current, 8);
  Serial.println(" A.");
  Serial.println();
  return current;
}
