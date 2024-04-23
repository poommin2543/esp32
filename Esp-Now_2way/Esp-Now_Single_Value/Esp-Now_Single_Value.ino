#include <esp_now.h>
#include <WiFi.h>

//Send Data
uint8_t PinVal = 0;
//Recieve Data
uint8_t InputValue = 0;

// replace with the MAC address of the receiving ESP32 board
uint8_t broadcastAddress[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};
esp_now_peer_info_t peerInfo;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&InputValue, incomingData, sizeof(InputValue)); 
  Serial.print(" -- Data Recieved -- : ");
  Serial.println(InputValue);
}


void setup() {
  Serial.begin(115200);  // Init Serial Monitor
  WiFi.mode(WIFI_STA); // Set device as a Wi-Fi Station

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Callback On Data Receive 
  esp_now_register_recv_cb(OnDataRecv);

}

void loop() {
  PinVal = 1;
  esp_err_t result = esp_now_send(broadcastAddress, &PinVal, sizeof(PinVal));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
    }
  else {
    Serial.println("Error sending the data");
    }
  delay(2000);
        

}
