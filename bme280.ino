#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)


//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

//unsigned long delayTime;


//void printValues() {
//    SerialUSB.print("Temperature = ");
//    SerialUSB.print(bme.readTemperature());
 //   SerialUSB.println(" *C");
//
 //   SerialUSB.print("Pressure = ");
//
  //  SerialUSB.print(bme.readPressure() / 100.0F);
  //  SerialUSB.println(" hPa");

   // SerialUSB.print("Approx. Altitude = ");
 //   SerialUSB.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
 //   SerialUSB.println(" m");

  //  SerialUSB.print("Humidity = ");
  //  SerialUSB.print(bme.readHumidity());
 //   SerialUSB.println(" %");

 //   SerialUSB.println();
//}
