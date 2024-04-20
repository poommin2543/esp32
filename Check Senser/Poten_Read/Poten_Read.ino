int PotenPin =34;
int PotenValue = 0;
float Voltage = 0.00;

void setup() {
  Serial.begin(9600);
  analogReadResolution(12); // Set Analog Read Resolution to 12 Bits
 
}

void loop() {
  PotenValue = analogRead(PotenPin); //Min = 0, Max = 4095
  Voltage = PotenValue*3300/4095;// in MiliVolt
  Serial.print("Poten Value = ");
  Serial.print(PotenValue);
  Serial.print(",");
  Serial.print("Milivoltage Value = ");
  Serial.println(Voltage,3);
  delay(500);


  
}
