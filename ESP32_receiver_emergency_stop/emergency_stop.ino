#include <WiFi.h>
#include <esp_now.h>

#define RIGHTMOTORS 25
#define LEFTMOTORS 26
#define DIRPIN 27
#define STOPPIN 21  // Pin connected to the emergency stop button or sensor

volatile bool isStopped = false;

int speed_sig = 0;
int speed_deci = 0;

typedef struct struct_message {
    int id;
    int us_data;
} struct_message;

struct_message myData;

void IRAM_ATTR toggleStop() {
    isStopped = !isStopped;  // Toggle the stop state
}

void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
    if (!isStopped) {
        memcpy(&myData, incomingData, sizeof(myData));
        speed_sig = myData.us_data;

        if (speed_sig < 20) {
            speed_sig = 20;
        }
        if (speed_sig > 80) {
            speed_sig = 80;
        }
        
        speed_deci = map(speed_sig, 20, 80, 0, 255);
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(RIGHTMOTORS, OUTPUT);
    pinMode(LEFTMOTORS, OUTPUT);
    pinMode(STOPPIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(STOPPIN), toggleStop, FALLING);

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    if (isStopped) {
        analogWrite(RIGHTMOTORS, 0);
        analogWrite(LEFTMOTORS, 0);
        Serial.println("System Stopped");
    } else {
        digitalWrite(DIRPIN, HIGH);
        analogWrite(RIGHTMOTORS, speed_deci);
        analogWrite(LEFTMOTORS, speed_deci);
        delay(100);
    }
}

