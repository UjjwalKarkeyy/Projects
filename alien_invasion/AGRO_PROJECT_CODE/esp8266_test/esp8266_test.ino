#define BLYNK_TEMPLATE_ID "TMPL61WZgnrP1"
#define BLYNK_TEMPLATE_NAME "DHT 11"
#define BLYNK_AUTH_TOKEN "htvHW5JlaIb3nQj4V9NGbztTE4cg1Thd"

char ssid[] = "IOT@2.4";         // put your wifi name here same exactly
char pass[] = "12345678";        // put your wifi password here

#define BLYNK_PRINT Serial   
#include <ESP8266WiFi.h>     
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>

BlynkTimer timer;
int humidity = 0;

void sendSensorData() 
{
  int Temperature = 50;  // Your static temperature value

  Blynk.virtualWrite(V1, Temperature);
  Blynk.virtualWrite(V2, humidity);
  
  // Sending data to MySQL
  if (WiFi.status() == WL_CONNECTED) { // Check WiFi connection status
    HTTPClient http; // Declare an object of class HTTPClient

    String serverPath = "http://localhost:8000/insert_data.php";

    http.begin(serverPath.c_str()); // Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Specify content-type header

    // Prepare data
    String httpRequestData = "Humidity=" + String(humidity);
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString(); // Get the response to the request
      Serial.println(httpResponseCode);   // Print return code
      Serial.println(response);           // Print request answer
    }
    else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Close connection
  }
}

void setup() 
{
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
  }

  Blynk.run();
  timer.run();
}
