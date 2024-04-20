#define LDR 35    //ประกาศตัวแปร LDR
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  Serial.print("LUX Meter : ");
  Serial.print(lux_meter());   //เรียกใช้ฟังก์ชั่น lux_meter()
  Serial.println(" lux"); 
  delay(1000);
}
int lux_meter(){    //ฟังก์ชั่นแปลงค่าดิจิทัลเป็นค่า Lux
  int LDR_Val = analogRead(LDR);
  float Vout = float(LDR_Val) * (3.3 / float(4096));
  float RLDR = (10000 * (3.3 - Vout))/Vout; 
  int lux = 500/(RLDR/1000); 
  return lux;
}