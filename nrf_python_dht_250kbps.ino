//Send.ino
#include <LiquidCrystal.h>
const int rs = A5, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include<SPI.h>
#include<RF24.h>
#include "DHT.h"
#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); 
// ce, csn pins
RF24 radio(7, 8);
char thChar[32] = "";
String thString = "";
String temp = "Temp: ";
String hum = "Humidity: ";
void setup(void){
  Serial.begin(9600);
  dht.begin();
  radio.begin();
  //radio.printDetails();
  radio.setPALevel(RF24_PA_MIN);
  Serial.println("Hi");
  radio.setChannel(0x76);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();
  lcd.begin(16, 2);
}

void loop(void){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    t = 0.0;
    h = 0.0;
    return;
  }
  thString = String(t) + String(h);
  thString.toCharArray(thChar, 12);
  radio.write(thChar, sizeof(thChar));
  lcd.clear();
  lcd.print(temp+t);
  lcd.setCursor(0,2);
  lcd.print(hum+h);
  delay(100);

}
