#include <DHT.h>
float dbms[3];
float hums, temp;
float pirs=0;
DHT dht(2, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // KELEMBAPAN
  dbms[0] = dht.readHumidity();
  // SUHU
  dbms[1] = dht.readTemperature();
  // PIR 
  dbms[2] = analogRead(A0);
  // KIRIM KE NODEMCU
  Serial.println(toString(dbms,3));
  delay(1000);  
}

String toString(float arr[], int length) {
  String str = "";
  for (int i = 0; i < length; i++) {
    str += String(arr[i]);
    if (i < length - 1) str += ",";
  }
  return str;
}