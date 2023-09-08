#include <Arduino.h>

// put function declarations here:
#define DEBUG 0

#define STRIP_DELAY 5000   // HOW MUCH TIME LED STRIP SHOULD LIGHT UP
#define PIXEL_NO 50        // NUMBER OF PIXELS

#define LED_PIN_1 2        // INTER CHANGE IF NECESSARY
#define LED_PIN_2 3

#define SS_PIN1 6          // INTER CHANGE IF NECESSARY 
#define SS_PIN2 7          // INTER CHANGE IF NECESSARY 

#define RST_PIN 8          // DON'T CHANGE

#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>

byte readCard[4];

String Box1 = "A39F1B16";  // MADINA
String Box2 = "5C1DDC38";  // NOBU
String Box3 = "CCFFD337";  // THE POINT
String Box4 = "20C3935E";  // MADINA
String Box5 = "20C3935E";  // NOBU
String Box6 = "CC241B49";  // THE POINT

String tagID1 = "";
String tagID2 = "";

// Create instances
MFRC522 reader_1(SS_PIN1, RST_PIN);
MFRC522 reader_2(SS_PIN2, RST_PIN);

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(PIXEL_NO, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(PIXEL_NO, LED_PIN_2, NEO_GRB + NEO_KHZ800);


// NEOPIXEL

void brighten_1() {
  uint16_t i, j;

  for (j = 0; j < 255; j++) {
    for (i = 0; i < strip1.numPixels(); i++) {
      strip1.setPixelColor(i, j, j, j);
    }
    strip1.show();
    delay(1);
  }
}

void darken_1() {
  uint16_t i, j;

  for (j = 255; j > 0; j--) {
    for (i = 0; i < strip1.numPixels(); i++) {
      strip1.setPixelColor(i, j, j, j);
    }
    strip1.show();
    delay(1);

  }

}

void brighten_2() {
  uint16_t i, j;

  for (j = 0; j < 255; j++) {
    for (i = 0; i < strip2.numPixels(); i++) {
      strip2.setPixelColor(i, j, j, j);
    }
    strip2.show();
    delay(1);
  }
}

void darken_2() {
  uint16_t i, j;

  for (j = 255; j > 0; j--) {
    for (i = 0; i < strip2.numPixels(); i++) {
      strip2.setPixelColor(i, j, j, j);
    }
    strip2.show();
    delay(1);

  }

}

void show1(){
  brighten_1();
  delay(STRIP_DELAY);
  darken_1();
  }
void show2(){
  brighten_2();
  delay(STRIP_DELAY);
  darken_2();
  }

  
// RFID READ
//Read new tag if available
boolean getID_1()
{
  // Getting ready for Reading PICCs
  if ( ! reader_1.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return false;
  }
  if ( ! reader_1.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return false;
  }
  tagID1 = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
    //readCard[i] = reader_1.uid.uidByte[i];
    tagID1.concat(String(reader_1.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID1.toUpperCase();
  reader_1.PICC_HaltA(); // Stop reading
  return true;
}

boolean getID_2()
{
  // Getting ready for Reading PICCs
  if ( ! reader_2.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return false;
  }
  if ( ! reader_2.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return false;
  }
  tagID2 = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
    //readCard[i] = reader_1.uid.uidByte[i];
    tagID2.concat(String(reader_2.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID2.toUpperCase();
  reader_2.PICC_HaltA(); // Stop reading
  return true;
}


void setup()
{
  Serial.begin(9600);
  // Initiating
  SPI.begin(); // SPI bus
  reader_1.PCD_Init(); // MFRC522
  reader_2.PCD_Init(); // MFRC522

  strip1.begin();
  strip2.begin();
  strip1.show(); // initialize all pixels to "off"
  strip2.show();
}

void loop()
{

  //Wait until new tag is available
  while (getID_1())
  {
    if (tagID1 == Box1)
    {
      Serial.println("A");
      show1();
    }
    else if (tagID1 == Box2)
    {
      Serial.println("B");
      show1();
    }
    else if (tagID1 == Box3)
    {
      Serial.println("C");
      show1();
    }
    if (tagID1 == Box4)
    {
      Serial.println("A");
      show1();
    }
    else if (tagID1 == Box5)
    {
      Serial.println("B");
      show1();
    }
    else if (tagID1 == Box6)
    {
      Serial.println("C");
      show1();
    }
    if (DEBUG) {
      Serial.println(" ID : " + String(tagID1));
    }
    yield();
  }

  while (getID_2())
  {
    if (tagID2 == Box1)
    {
      Serial.println("D");
      show2();
    }
    else if (tagID2 == Box2)
    {
      Serial.println("E");
      show2();
    }
    else if (tagID2 == Box3)
    {
      Serial.println("F");
      show2();
    }
    if (tagID2 == Box4)
    {
      Serial.println("D");
      show2();
    }
    else if (tagID2 == Box5)
    {
      Serial.println("E");
      show2();
    }
    else if (tagID2 == Box6)
    {
      Serial.println("F");
      show2();
    }
    if (DEBUG) {
      Serial.println(" ID : " + String(tagID2));
    }
    yield();
  }
  
}
