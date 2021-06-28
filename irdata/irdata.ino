#include <FirebaseArduino.h>   
#include <ESP8266WiFi.h>

#define WIFI_SSID "RRR"
#define WIFI_PASSWORD "rrrplaza"
#define FIREBASE_HOST "door-1e073-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "x2ZzXr4htd3UAANF68PdbjBTOC1H4yrna5LQNicO"

int DoorStatus = 13;                   
int Count = 14;      
int f=0;

void setup() {
  Serial.begin(115200);
  Serial.print("Start");
  pinMode(DoorStatus, INPUT);
  pinMode(Count, INPUT);
  // connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

    int Entry = digitalRead(Count);
    int door = digitalRead(DoorStatus);
    if (door == LOW) {
      Serial.println("Door is open" ); 
      Firebase.setString( "Door","Open");
      if (Entry == LOW) {
        f++;
        Serial.print("People in the room = " ); 
        Serial.println(f);
        Firebase.setFloat("Counter",f);
      if(Firebase.error()){
        Serial.println("F error");
      }
        delay(1000);
      }
    }
    else if(door == HIGH){
      Serial.println("Door is closed");
      Firebase.setString( "Door", "Closed");
      if(Firebase.error()){
        Serial.println("F error");
      }
      delay(2000);
    }
    else{
      Serial.println("NNN");
    }
}
