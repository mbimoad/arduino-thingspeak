#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>
#include <ArduinoJson.h> // Libraries > Manage > ArduinoJson by Benoit Blanchon Versi 6.14.1
// SALIN LINK URL API THINGSPEAK
String URL="http://api.thingspeak.com/update?api_key=EHLDFR9TAVOUNOHF&field1=";

String data = ""; 
String dbms[3]; 
float x=0,y=0,z=0;

const char *namawifi = "mbimoad";
const char *password = "abcd123";

void KoneksiThingspeak() {
  WiFi.disconnect();
  delay(2000);
  Serial.print("Start connection");
  WiFi.begin(namawifi, password);
  while((!(WiFi.status()== WL_CONNECTED))){
      delay(200);
      Serial.print("..");
    }
  Serial.println("Connected");
}

void sendDataTS(float nilai1, float nilai2) {
  WiFiClient client;
  HTTPClient http;
  // URLnya sesuaikan. 
  String newUrl=URL+String(nilai1) + "&field2=" + String(nilai2);
  http.begin(client,newUrl);
  int responsecode=http.GET();
  String data=http.getString();
  Serial.println(data);
  http.end();  
}



void setup() {
  Serial.begin(9600); // Initialize serial communication
  KoneksiThingspeak();
}

void loop() {
  if (Serial.available() > 0) {
    char kata = Serial.read(); // Read the incoming character` 
    // Cek New Line
    if (kata != '\n') {
      data += kata; 
    } else {
      Serial.println(data); 
      split(data, ',',dbms,3);

      x = (dbms[0] == "") ? 0 : atof(dbms[0].c_str());
      y = (dbms[1] == "") ? 0 : atof(dbms[1].c_str());
      z = (dbms[2] == "") ? 0 : atof(dbms[2].c_str());

      Serial.println(x);
      Serial.println(y);
      Serial.println(z);
      sendDataTS(x,y);

      // Clear 
      data    = "";
      dbms[0] = ""; 
      dbms[1] = ""; 
      dbms[2] = ""; 
      
    } 
  }  
}
void split(String str, char delimiter, String parts[], int maxParts) {
  int partIndex = 0;
  int startIndex = 0;
  int endIndex = -1;
  
  while (partIndex < maxParts) {
    endIndex = str.indexOf(delimiter, startIndex);
    if (endIndex == -1) {
      endIndex = str.length();
    }
    
    parts[partIndex] = str.substring(startIndex, endIndex);
    
    startIndex = endIndex + 1;
    partIndex++;
    
    if (startIndex >= str.length()) {
      break;
    }
  }
}
