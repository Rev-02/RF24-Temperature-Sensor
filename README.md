# RF24-Temperature-Sensor
Arduino with dht11 sensor - nrf24 - Raspberry Pi publishing to adafruit.io
# Guide
## Initial Tests
#Use RF24/examples_linux/pingpair_dyn.py to test initial connections
#Use pingpair_dyn with `radio.printDetails()` commented out
### Wiring - Pi (Test only)
* GND - Pin1
* 3v - Pin2
* GPIO 22 - Pin3
* GPIO 08 - Pin4
* SCK - SCK
* MOSI - MOSI
* MISO - MISO
### Wiring - Arduino
* GND - Pin1
* 3v - Pin2
* 7 - Pin3
* 8 - Pin4
* SCK - SCK
* MOSI - MOSI
* MISO - MISO

## Adafruit IO Code
### Wiring - Pi
* GND - Pin1
* 3v - Pin2
* GPIO 17 - Pin3
* GPIO 08 - Pin4
* SCK - SCK
* MOSI - MOSI
* MISO - MISO
### Wiring - Arduino
* GND - Pin1
* 3v - Pin2
* 7 - Pin3
* 8 - Pin4
* SCK - SCK
* MOSI - MOSI
* MISO - MISO
