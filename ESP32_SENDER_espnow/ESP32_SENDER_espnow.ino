
#define TRIGPIN 26
#define ECHOPIN 25
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

#include <esp_now.h>
#include <WiFi.h>

long duration;
float distanceCm;


uint8_t broadcastAddress[] = {0xcc, 0xdb, 0xa7, 0x2f, 0x1b, 0x28};


typedef struct struct_message {
//  char a[32];z
  int id;
  int us_data;
} 
struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }


  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
     
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  myData.id = 1;
  myData.us_data = readUltrasonic();

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(500);
}

int readUltrasonic(){

  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distanceCm = duration * SOUND_VELOCITY/2;

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  int dist = (int)distanceCm;
  if(dist> 200){
    dist =200;
  }
  int speed_val = map(dist,1,200,0,255);
  speed_val = int(speed_val);
  return speed_val;
  }
