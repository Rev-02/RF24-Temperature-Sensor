#include<SPI.h>
#include<RF24.h>
#include "DHT.h"
#define DHTPIN A3
#define DHTTYPE DHT11
#define THERMPIN A0
#define LDRPIN A1
DHT dht(DHTPIN, DHTTYPE);
RF24 radio(7, 8);
char packetChar[32] = "";
String thString = "";
String temp = "Temp: ";
String hum = "Humidity: ";

void setupSensors(){
   
  dht.begin();
}

void configRadio(){
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();
}

void setup(void){
  Serial.begin(9600);
  setupSensors();
  configRadio();
}

int readThermistor(int pin){
  int reading;
  reading = analogRead(pin);
  reading = (1023 / reading)  - 1;     // (1023/ADC - 1) 
  reading = 10000 / reading;
  return reading;
}

int readLDR(int pin){
  int reading;
  reading = analogRead(pin);
  return reading;
}

String readTh(){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    t = 0.0;
    h = 0.0;
    return;
  }
  thString = String(t) + String(h);
  return thString;
}

void loop(void){
  String tAndH;
  tAndH = readTh();
  int therm = readThermistor(THERMPIN);
  int lDR = readLDR(LDRPIN);
  if ((tAndH.length()) != 0){
    // serialize data and send
    String result = tAndH+';'+therm+';'+lDR;
    result.toCharArray(packetChar, 32);
    radio.write(packetChar, sizeof(packetChar)); 
  }
  else{
    Serial.println('HI');
  }
  delay(100);
}
