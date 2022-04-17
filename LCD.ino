// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     47
#define TFT_RST    48  // you can also connect this to the Arduino reset
// in which case, set this #define pin to -1!
#define TFT_DC     50

// For 1.44" and 1.8" TFT with ST7735 use
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void lcdSetup(void) {
  tft.initR(INITR_GREENTAB);   // initialize a ST7735S chip, black tab
  //tft.setRotation(2);
//  tft.fillScreen(ST77XX_BLACK);

  //delay(5);
//  tft.setRotation(1);
//  tft.fillScreen(ST77XX_BLACK);

//  delay(5);
//  tft.setRotation(3);
//  tft.fillScreen(ST77XX_BLACK);

//  delay(5);

  // large block of text
//  tft.fillScreen(ST77XX_BLACK);

  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);

  

  testdrawtext("Humidity and Temperature:", ST77XX_GREEN, 5, 5);
  testdrawtext("Results:", ST77XX_WHITE, 5, 30);
  //testdrawtext("NRF24L01 MESSAGE", ST77XX_YELLOW, 5, 55);
#ifdef DEBUG
  SerialUSB.println("LCD->Initialized");
#endif
}

void testdrawtext(char *text, uint16_t color, uint8_t x, uint8_t y) {
  tft.setCursor(x, y);
  tft.setTextColor(color, ST77XX_BLACK);
  tft.setTextWrap(true);
  tft.print(text);
}
