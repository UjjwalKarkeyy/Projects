#define BLYNK_TEMPLATE_ID "TMPL61WZgnrP1"
#define BLYNK_TEMPLATE_NAME "DHT 11"
#define BLYNK_AUTH_TOKEN "htvHW5JlaIb3nQj4V9NGbztTE4cg1Thd"

char ssid[] = "IOT@2.4";         // put your wifi name here same exactly
char pass[] = "12345678";        // put your wifi password here

#define BLYNK_PRINT Serial   
#include <ESP8266WiFi.h>     
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;
int humidity = 0;
int temperature = 0;
int soilsense = 0;
int phsense = 0;

void sendSensorData() {

  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, soilsense);
  Blynk.virtualWrite(V4, phsense);
}

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi CONNECTED!");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Set up a timer to send sensor data every second
  timer.setInterval(1000L, sendSensorData);
}

void loop() 
{


  if (Serial.available()) {
    // Read the received data
    String data = Serial.readStringUntil('\n');

    // Process the data (extract humidity value)
    if (data.startsWith("Humidity: ")) {
      humidity = data.substring(10).toInt();
    }

    if (data.startsWith("Temperature: ")) {
      temperature = data.substring(13).toInt();
    }

    if (data.startsWith("pH value: ")) {
      phsense = data.substring(10).toInt();
    }

    if (data.startsWith("Soil moisture value: ")) {
      soilsense = data.substring(21).toInt();
    }

  }

    Blynk.run();
    timer.run();
}
