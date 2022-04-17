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

unsigned long delayTime;




#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

#include <DueTimer.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

int Button1 = 2;
int Button2 = 4;
int Button3 = 5;
int Button4 = 30;
int Button5 = 33;
int Button6 = 32;

int L_D1 = 24;
int L_D2 = 31;
int L_D3 = 26;
int L_D4 = 25;
int L_D5 = 22;
int L_D6 = 23;

int kB_BL = 3;

char testbuffer[50];

#define BLUETOOTH_SERIAL Serial1

Adafruit_BME280 bme; // I2C

extern char HC05NAME[64];
extern char HC05MAC[64];
//#define DEBUG

int d = 0;

unsigned long count;

#define ESP_PIN 53

unsigned int avRef = 3000;    // Analog voltage reference in mV

int S1_LED_RD = 9;        // Status Led S1
int S2_LED_YE = 8;        // Status Led S2
int S3_LED_GR = 7;        // Status Led S3
int S4_LED_BL = 6;        // Status Led S4

int K0 = 13;        // Status Led S1
int K1 = 12;        // Status Led S2
int K2 = 11;        // Status Led S3
int K3 = 10;        // Status Led S4

static unsigned long lastTimeUpdateMillis = 0;

unsigned char canMessage;
unsigned char linMessage;
unsigned char nrfMessage;

bool processCANMessage;
bool processLINMessage;
bool processNRFMessage;
bool setDS3231ClockMessage;
bool saveConfigurationMessage;

bool ledOn = false;
bool bespPin = false;



void BlinkLeds() {

  count += 1;

  d += 1;
  if (d == 4)
    d = 0;

  switch (d)
  {
    case 0:
      {
        digitalWrite(S1_LED_RD, HIGH);
        digitalWrite(S2_LED_YE, LOW);
        digitalWrite(S3_LED_GR, LOW);
        digitalWrite(S4_LED_BL, LOW);
      }
      break;
    case 1:
      {
        digitalWrite(S1_LED_RD, LOW);
        digitalWrite(S2_LED_YE, HIGH);
        digitalWrite(S3_LED_GR, LOW);
        digitalWrite(S4_LED_BL, LOW);
      }
      break;
    case 2:
      {
        digitalWrite(S1_LED_RD, LOW);
        digitalWrite(S2_LED_YE, LOW);
        digitalWrite(S3_LED_GR, HIGH);
        digitalWrite(S4_LED_BL, LOW);
      }
      break;
    case 3:
      {
        digitalWrite(S1_LED_RD, LOW);
        digitalWrite(S2_LED_YE, LOW);
        digitalWrite(S3_LED_GR, LOW);
        digitalWrite(S4_LED_BL, HIGH);
      }
      break;
  }
  LedToK();
  //printBTDetails();
}

void setup() {
  Serial.begin(115200);

  BluetoothGetMAC_Name();

  unsigned status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();  
    if (!status) {
        SerialUSB.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        SerialUSB.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        SerialUSB.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        SerialUSB.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        SerialUSB.print("        ID of 0x60 represents a BME 280.\n");
        SerialUSB.print("        ID of 0x61 represents a BME 680.\n");
        while (1);
    }

  count = 0;

  // LEDs set as output
  pinMode(S1_LED_RD, OUTPUT);
  pinMode(S2_LED_YE, OUTPUT);
  pinMode(S3_LED_GR, OUTPUT);
  pinMode(S4_LED_BL, OUTPUT);

  pinMode(K0, OUTPUT);
  pinMode(K1, OUTPUT);
  pinMode(K2, OUTPUT);
  pinMode(K3, OUTPUT);

  pinMode(Button1, INPUT);
  digitalWrite(Button1, HIGH);
  pinMode(Button2, INPUT);
  digitalWrite(Button2, HIGH);
  pinMode(Button3, INPUT);
  digitalWrite(Button3, HIGH);
  pinMode(Button4, INPUT);
  digitalWrite(Button4, HIGH);
  pinMode(Button5, INPUT);
  digitalWrite(Button5, HIGH);
  pinMode(Button6, INPUT);
  digitalWrite(Button6, HIGH);

  pinMode(L_D1, OUTPUT);
  digitalWrite(L_D1, LOW);
  pinMode(L_D2, OUTPUT);
  digitalWrite(L_D2, LOW);
  pinMode(L_D3, OUTPUT);
  digitalWrite(L_D3, LOW);
  pinMode(L_D4, OUTPUT);
  digitalWrite(L_D4, LOW);
  pinMode(L_D5, OUTPUT);
  digitalWrite(L_D5, LOW);
  pinMode(L_D6, OUTPUT);
  digitalWrite(L_D6, LOW);

  pinMode(kB_BL, OUTPUT);
  digitalWrite(kB_BL, LOW);

  // Use this initializer if you're using a 1.8" TFT

  lcdSetup();

  printValues();

  //testdrawtext("BT name:", ST77XX_YELLOW, 5, 45);
  //testdrawtext(HC05NAME, ST77XX_BLUE, 55, 45);

  //testdrawtext("BT Mac:   ", ST77XX_YELLOW, 5, 55);
  //testdrawtext(HC05MAC, ST77XX_BLUE, 50, 55);

  watchdogEnable(5000);

  Timer3.attachInterrupt(BlinkLeds);
  Timer3.start(500000); // Calls every 50ms

  Timer4.attachInterrupt(PrintOnConsole);
  Timer4.start(10000000); // Calls every 50ms

  //#ifdef DEBUG
  Serial.println("Setup->Complete");
  //#endif
}

void loop() {

  watchdogReset();

  if (millis() - lastTimeUpdateMillis > 10000)
  {
    lastTimeUpdateMillis = millis();
    //sendCANMessage();
    //sendNRF24L01Message();
    PrintOnConsole();
  }
  else if (millis() - lastTimeUpdateMillis > 1000)
  {
    lastTimeUpdateMillis = millis();
    //sendCANMessage();
    //sendNRF24L01Message();
    printValues();
  }
}

void LedToK(void)
{
  digitalWrite(K0, digitalRead(S1_LED_RD));
  digitalWrite(K1, digitalRead(S2_LED_YE));
  digitalWrite(K2, digitalRead(S3_LED_GR));
  digitalWrite(K3, digitalRead(S4_LED_BL));
}

void printBTDetails(void)
{
  BLUETOOTH_SERIAL.print("Count = ");
  BLUETOOTH_SERIAL.println(count, DEC);
  BLUETOOTH_SERIAL.print("BT Name:    ");
  BLUETOOTH_SERIAL.println(HC05NAME);
  BLUETOOTH_SERIAL.print("BT Mac:     ");
  BLUETOOTH_SERIAL.println(HC05MAC);
}

void PrintOnConsole(){
    String myStr = "TMP=";     // empty string
    myStr.concat(bme.readTemperature());
    myStr.concat(";HMD=");
    myStr.concat(bme.readHumidity());
    myStr.concat(";BAR=");
    myStr.concat(bme.readPressure());
    myStr.concat("<cr>");
    SerialUSB.println(myStr);
}

void printValues() {
    testdrawtext("Temperature: ", ST77XX_YELLOW, 5, 65);
    String myString = "";     // empty string
    myString.concat(bme.readTemperature());
    int len = myString.length() + 1;
    char chararr[len];
    myString.toCharArray(chararr, len);
    testdrawtext(chararr, ST77XX_BLUE, 79, 65);
    testdrawtext(" *C", ST77XX_BLUE, 110, 65);

    testdrawtext("Pressure: ", ST77XX_YELLOW, 5, 75);
    String myString2 = "";     // empty string
    myString2.concat(bme.readPressure() / 100.0F);
    int len2 = myString2.length() + 1;
    char chararr2[len2];
    myString2.toCharArray(chararr2, len2);
    testdrawtext(chararr2, ST77XX_BLUE, 60, 75);
    testdrawtext(" hPa", ST77XX_BLUE, 100, 75);

    //testdrawtext("Approx. Altitude = ");
    //testdrawtext(bme.readAltitude(SEALEVELPRESSURE_HPA));
    //testdrawtext(" m");


    testdrawtext("Humidity: ", ST77XX_YELLOW, 5, 85);
    String myString3 = "";     // empty string
    myString3.concat(bme.readHumidity());
    int len3 = myString3.length() + 1;
    char chararr3[len3];
    myString3.toCharArray(chararr3, len3);
    testdrawtext(chararr3, ST77XX_BLUE, 65, 85);
    testdrawtext(" %", ST77XX_BLUE, 100, 85);

    //testdrawtext();
}
