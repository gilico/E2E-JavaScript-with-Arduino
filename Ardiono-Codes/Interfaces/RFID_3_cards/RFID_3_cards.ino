#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#define RST_PIN 9
#define SS_PIN 10 
#define LED_G 4

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
#define cardsNum 3
String cardsId[cardsNum] = {"E3 4F D6 3E", "93 4E 1B 3E", "E0 C7 EB 93" };
int posId = 0;
bool isCardTouch = false;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_G, OUTPUT);
  Serial.println("Put your card to the reader");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content.substring(1) == cardsId[posId] && !isCardTouch) {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    posId++;
    Serial.println(posId);
    isCardTouch = true;
  }else {
    Serial.println(" Access denied");
    isCardTouch = false;
    delay(500);
  }
} 
