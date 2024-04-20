#include <esp_now.h>
#include <WiFi.h>

int LedPin =2;
uint8_t PinValue = 0;
int count = 0;
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&PinValue, incomingData, sizeof(PinValue));
  if(PinValue>=1){
    count++; // count=count+1;
    Serial.println(PinValue);
    if (count==1){

    }
    else if (count==2){

    }
    else if (count==3){
      count=0;

    }

    digitalWrite(LedPin,HIGH);
  }
  else{
    digitalWrite(LedPin,LOW);
  }
}
 
void setup() {
  pinMode(LedPin,OUTPUT); // Set LED pin
  Serial.begin(115200); // Initialize Serial Monitor
  WiFi.mode(WIFI_STA); // Set device as a Wi-Fi Station

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Callback On Data Receive 
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  
}


int noom=0;
noom++;
noom+=1;
noom = noom+1

Serial.println(noom);


if(PinValue==1){

}






