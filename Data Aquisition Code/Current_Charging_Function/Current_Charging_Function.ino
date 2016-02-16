
/*****************************************************/
// Current Measure Function
// Tests the functionality of the ACS716 Current Sensor
// Dec 5, 2015
/*****************************************************/


#define CurrentSensor 3
float analogVoltage = 0;
float current = 0;


void setup() {
  pinMode(CurrentSensor, INPUT);
  Serial.begin(9600);
}


void loop() {
  CurrentMeasure();
  delay(1000);
  Serial.println(current);
}


float CurrentMeasure() { 
 analogVoltage = analogRead(CurrentSensor)*5.000/1024.000;
 Serial.print("Analog Voltage: ");
 Serial.println(analogVoltage);
 current = (analogVoltage-337.97)/3.787;
 return current;
}
