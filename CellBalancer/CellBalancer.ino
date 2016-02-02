
/******************************************************/
// Cell Balancing System                              //
// Based on measured current, controls DCDC Converter //
// Jan 11, 2016                                       //
// Sean Girard                                        //
/******************************************************/


#define Current_Sensor 3
#define DC_Converter 10
#define LED 13

float Current_thresh = 0.5; // [A]
float analogCurrent = 0;
float current = 0;
float sensitivity = 0.0185; // [V/A]
int IterationNumber = 0;
float rawADC = 0;


void setup() {
  
  // Set up pins
  pinMode(Current_Sensor, INPUT);
  pinMode(DC_Converter, OUTPUT);
  pinMode(LED, OUTPUT);

  // Set up Serial Connection
  Serial.begin(9600);
  Serial.println("Setup Complete.");

  // Enable DCDC Converter
  digitalWrite(DC_Converter, HIGH);
  digitalWrite(LED, HIGH);

  // Allow time for DC_Converter to turn on
  delay(5000);
  Serial.println("DC_Converter ON");
  Serial.println("");
}



void loop() {

  // To measure the current, first note the following:
  //  1. Arduino measures 0 to 1024 (only up to 675.84 is utilized)
  //  2. Current Sensor outputs 0 to 3.3V
  //  3. Current Sensor reading of 1.65V, corresponds to 0A measured
  //  4. Current Sensor has 18.5mv/A Sensitivity (0.0185 V/A)
  //
  // |--------------|--------------|                [Current]
  // -75A           0A             75A
  //
  // |--------------|--------------|                [Current Sensor Output]
  // 0             1.65V          3.3V
  // 
  // |--------------|--------------|-----------|    [Arduino Analog input]
  // 0           337.92          675.84       1024
  //
  // Example: analogRead measures 400
  //  1. 400 / 675.84 = 0.59
  //  2. 3.3 * 0.59 = 1.95V is the Current Sensor output (0 - 3.3V)
  //  3. 1.95V - 1.65V = 0.3V above the 0A point on Current Sensor scale
  //  4. 0.3V / 0.0185 V/A = 16A is the current

  current = CurrentMeasure();
  
  // Disable DC_Converter when current falls below cut-off
  if (current < Current_thresh) {
    IterationNumber++;
    delay(250);
    Serial.print("Current Threshold Reached : ");
    Serial.print(IterationNumber);
    Serial.println(" times.");
      if (IterationNumber == 3){
      digitalWrite(DC_Converter, LOW);
      digitalWrite(LED, LOW);
      Serial.println("Current cut-off point reached.");
      Serial.println("DC Converter OFF");
      while (true);
    }
  } else {
    IterationNumber = 0;
  }
}


float CurrentMeasure() { 
 //   Read & print ADC output
  int rawADC = analogRead(Current_Sensor);
  Serial.print("ADC: ");
  Serial.print(rawADC);
  Serial.println("/1024.");

  // Calculate & print current
  float current = (rawADC/1024)*5.0000000000000000000;
  Serial.print("Current: ");
  Serial.print(current, 8);
  Serial.println(" A.");
  Serial.println();
  return current;
}

// End of file.
