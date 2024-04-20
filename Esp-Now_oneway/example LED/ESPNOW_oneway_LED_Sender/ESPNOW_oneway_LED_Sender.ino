#include <esp_now.h>
#include <WiFi.h>

#define BUTTON_PIN 4 // the pin the push button is connected to
uint8_t PinVal = 0;

// replace with the MAC address of the receiving ESP32 board
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
esp_now_peer_info_t peerInfo;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);

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
}

void loop() {
  PinVal = digitalRead(BUTTON_PIN);
  
  esp_err_t result = esp_now_send(broadcastAddress, &PinVal, sizeof(PinVal));
  delay(200);
}





