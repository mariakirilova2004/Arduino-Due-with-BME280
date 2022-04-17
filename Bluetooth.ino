

int HC_05_PROG = 40;    // HC-05 Programming pin
int HC_05_POWER = 38;   // HC-05 Power

char btTemp[64];

char HC05MAC[64];
unsigned char avb = 0;

char HC05NAME[64];
unsigned char iHC05NameSize = 0;
unsigned char iTMP = 0;

#define BLUETOOTH_SERIAL Serial1

void BluetoothGetMAC_Name(void) {

  pinMode(HC_05_POWER, OUTPUT);
  pinMode(HC_05_PROG, OUTPUT);

  // set the pins to LOW
  digitalWrite(HC_05_PROG, HIGH);
  digitalWrite(HC_05_POWER, HIGH);

  // now power on the BT
  digitalWrite(HC_05_POWER, LOW);

  // initiate the BT serial at 38400 which is the default
  // speed at which the BT AT mode operates at
  BLUETOOTH_SERIAL.begin(38400);

  delay(1000);

  BLUETOOTH_SERIAL.println("AT+ADDR?");
  delay(500);
  memset(btTemp, 0x00, 64);
  avb = BLUETOOTH_SERIAL.available();

  if (avb != 0) {
    BLUETOOTH_SERIAL.readBytes(btTemp, avb);
  }
  delay(50);

  iTMP = find_textEX("ADDR:", btTemp);
  avb = avb - iTMP - 5 - 6;
  memcpy(HC05MAC, btTemp + iTMP + 5, avb);


  BLUETOOTH_SERIAL.println("AT+NAME?");
  delay(500);
  memset(btTemp, 0x00, 64);
  iHC05NameSize = BLUETOOTH_SERIAL.available();

  if (iHC05NameSize != 0) {
    BLUETOOTH_SERIAL.readBytes(btTemp, iHC05NameSize);
  }

  iTMP = find_textEX("NAME:", btTemp);
  iHC05NameSize = iHC05NameSize - iTMP - 5 - 6;
  memcpy(HC05NAME, btTemp + iTMP + 5, iHC05NameSize);


//  BLUETOOTH_SERIAL.println("AT+UART=9600,0,0\r\n");
//  delay(500);


  // set the key pin to High
  digitalWrite(HC_05_POWER, HIGH);
  // set the key pin to INPUT
  pinMode(HC_05_PROG, INPUT);


  // small delay
  delay(500);

  // now power on the BT
  digitalWrite(HC_05_POWER, LOW);

  delay(1000);

  BLUETOOTH_SERIAL.begin(9600);           // start serial for output
}

int find_textEX(String needle, String haystack) {
  int foundpos = -1;
  for (int i = 0; (i < haystack.length() - needle.length()); i++) {
    if (haystack.substring(i, needle.length() + i) == needle) {
      foundpos = i;
    }
  }
  return foundpos;
}
