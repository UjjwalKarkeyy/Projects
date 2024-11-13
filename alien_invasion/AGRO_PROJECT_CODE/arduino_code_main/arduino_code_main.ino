#include "DHT.h"
#include <SoftwareSerial.h>

int soilpin = A0;     // Soil moisture sensor analog pin
int relaypin = 8;     // Relay pin
int dhtpin = 2;       // DHT sensor pin
int phSense = A1; 

int pharr[10],temp, average;    // pH sensor analog pin

#define DHTTYPE DHT11 // Describing what type of DHT is used

// Creating an instance of DHT
DHT dht(dhtpin, DHTTYPE);
SoftwareSerial espSerial(5, 6); // TX-5 and RX-6

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  
  pinMode(soilpin, INPUT);
  pinMode(relaypin, OUTPUT);
  pinMode(phSense, INPUT);

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Read soil moisture value
  int soilValue = analogRead(soilpin);

  for(int i = 0; i<10; i++)
  {
      // Read pH sensor value
      pharr[i] = analogRead(phSense);
      delay(10);
  }
  
  // Read humidity and temperature from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Print values to Serial Monitor
  Serial.print("Soil moisture value: ");
  Serial.println(soilValue);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Temperature: ");
  Serial.println(temperature);

  for(int i = 0; i < 9; i++)
  { 
    for(int j = i + 1; j < 10; j++)
    {
      if(pharr[i] > pharr[j])
      {
        temp = pharr[i];
        pharr[i] = pharr[j];
        pharr[j] = temp;
      }
    }
  }

  average = 0; 

  for(int i = 2; i<8; i++)
  {
    average+= pharr[i];
  }

  Serial.print("pH value: ");
  Serial.println((average) * (3.3 / 1023.0));

  // Send values via Software Serial to ESP8266 or other device

  espSerial.print("Humidity: ");
  espSerial.println(humidity);

  espSerial.print("Temperature: ");
  espSerial.println(temperature);

  espSerial.print("pH value: ");
  espSerial.println(average);

  espSerial.print("Soil moisture value: ");
  espSerial.println(soilValue);

  // // Control relay based on soil moisture value
  if (soilValue >= 450)
  {
    Serial.println("Relay ON - Watering");
    digitalWrite(relaypin, HIGH); // Activate relay (assuming LOW activates the relay)
  } 
  
  else if (soilValue <= 410) 
  {
    Serial.println("Relay OFF - Not Watering");
    digitalWrite(relaypin, LOW); // Deactivate relay (assuming HIGH deactivates the relay)
  }

  // Adding a delay of 2 seconds
  delay(6000);
}
