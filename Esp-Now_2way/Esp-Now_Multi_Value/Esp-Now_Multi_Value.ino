//ตัวส่ง-รับ ESP-Now หลายค่า By P'Noom เช่นเดิม
#include <esp_now.h>
#include <WiFi.h>

// แก้ไขค่า mac ตัวที่ต้องการส่งไปหา แก้ไขให้ตรงกับอีกบอร์ดนะจ๊ะ โดยคงตัว Ox ไว้เช่น Ox11 
 uint8_t broadcastAddress[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};

typedef struct struct_message { // สร้างตัวแปรแพ็จเกจแบบ struct จะได้ส่งได้หลายๆค่า
  char a[32]; //จองค่าว่าจะส่งไป32ตัวอักษรรวมเว้นวรรคหรือช่องว่างด้วย จำไว้ เกินได้แต่อย่าขาด​!!(เกินเยอะไปก็ไม่ดี)
  int b; 
  float c;
  bool d;
} struct_message;

struct_message myData; // ตัวแปรแพ็คเกจที่ต้องการส่งชื่อตัวแปรว่า myData

//เมื่อส่งข้อมูลมาทำฟังก์ชั่นนี้
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// เมื่อรับข้อมูลมา ให้ทำในฟังก์ชั่นนี้
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("Bool: ");
  Serial.println(myData.d);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  //ตั้งเป็นโหมด Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  
  // สั่งให้เริ่ม ESP-NOW เช็คว่า esp now ทำงานได้หรือไม่
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // เมื่อรับข้อมูลมา ให้ทำในฟังก์ชั่น OnDataRecv ที่เราสร้างไว้
  esp_now_register_recv_cb(OnDataRecv);

  //เมื่อส่งให้ทำฟังก์ชั่น OnDataSend ที่เราสร้างขึ้น
  esp_now_register_send_cb(OnDataSent);

  // Register peer กับอีกบอร์ด
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // เชื่อมต่ออุปกรณ์ที่ต้องการสื่อสารจ้า
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // เริ่มสร้างตัวแปรแพ็คเกจที่ต้องการส่งเลยจังหว๊ะนี้
  strcpy(myData.a, "Noom Hi!!!");
  myData.b = 10;
  myData.c = 20.5;
  myData.d = true;

  // สั่งให้ส่งข้อมูลไปอีกบอร์ดได้เลยโดยใช้คำสั่งนี้
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}