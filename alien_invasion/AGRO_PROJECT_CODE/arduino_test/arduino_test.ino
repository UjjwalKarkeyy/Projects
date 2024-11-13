#include "DHT.h"
#include<SoftwareSerial.h>

int soilpin = A0, relaypin = 8, dhtpin = 2, phsense = A1;

#define DHTTYPE DHT11 //Describing what type of DHT is used

//Creating an instance of DHT
DHT dht(dhtpin, DHTTYPE);
SoftwareSerial espSerial(5,6); //TX-5 and RX-6

void setup()
{
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(soilpin, INPUT);
  pinMode(relaypin, OUTPUT);
  pinMode(phsense, INPUT);

  //Instance equivelent of saying pinMode(dhtpin, INPUT)
  dht.begin();
}

void loop()
{
  int value = analogRead(soilpin);
  
  //As DHT reads both humidity and temperature, using attributes of object to read them
  int h = dht.readHumidity();
  float t = dht.readTemperature(); 
  float ph = analogRead(phsense);


  Serial.print("Soil moisture value: ");
  Serial.print(value);
  Serial.println();
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println();
  
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println();

  Serial.print("Ph Value: ");
  Serial.print(ph);
  Serial.println();


  //Connecting water pump with some threshold value i.e., 500 right now
  // if(value >= 500)
  // {
  //   Serial.print("Working");
  //   Serial.println();
  //   digitalWrite(relaypin,LOW);
  // }

  // else if(value < 500)
  // {
    
  //   Serial.print("not Working");
  //   Serial.println();
  //   digitalWrite(relaypin,HIGH);
  // }  

  espSerial.print("Humidity: ");
  espSerial.println(h);
  espSerial.println(t);

  //Adding a delay of 5 sec
  delay(6000); 

}

