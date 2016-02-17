

#define CELLALL 0
#define CELL1 1
#define CELL2 2
#define CELL3 3
#define CELL4 4
asint voltage1, voltage2, voltage3, voltage4, voltageAll = 0;

void setup () {
  
  pinMode(CELL1, INPUT);
  pinMode(CELL2, INPUT);
  pinMode(CELL3, INPUT);
  pinMode(CELL4, INPUT);
  // pinMode(CELLALL, INPUT);
  

  Serial.begin(9600);
}


void loop () {
  
  // Measure voltages
  
  voltage1 = (5/1023) * analogRead(CELL1);
  voltage2 = (5/1023) * analogRead(CELL2);
  voltage3 = (5/1023) * analogRead(CELL3);
  voltage4 = (5/1023) * analogRead(CELL4);
  voltageAll = voltage1 + voltage2 + voltage3 + voltage4;
  
  // Send data over serial connection
  Serial.print(voltage1);
  Serial.print("*");
  Serial.print(voltage2);
  Serial.print("*");
  Serial.print(voltage3);
  Serial.print("*");
  Serial.print(voltage4);
  Serial.print("*");
  Serial.print(voltageAll);
  Serial.println("");

  
  
}

void ChargeCell(int cellNumber) {
  
  
}

int CellVoltage() {
  
}

boolean LogData() {
  
}
