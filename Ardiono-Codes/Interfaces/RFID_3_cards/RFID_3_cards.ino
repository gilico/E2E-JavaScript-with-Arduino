#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <Keyboard.h>
#include <require_cpp11.h>

/*
arduino pro micro:
RFID pin        arduino pro micro pin
RST             pin RST
SDA             pin D-10
MOSI            pin D-16
MISO            pin D-14
SCK             pin D-15

*/
#define RST_PIN 9
#define SS_PIN 10 
#define LED_G 3
#define LED_R 4
#define btn 2

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
#define cardsNum 3
String cardsId[cardsNum] = {"E3 4F D6 3E", "93 4E 1B 3E", "E0 C7 EB 93" };
int posId = 0;
bool isCardTouch = false;
bool isBtnPressed = false;
int x = 0;

void setup() {
  Keyboard.begin();
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  Serial.println("Put your card to the reader");
}
/**/
void loop() {
  if(x == 0){
    Keyboard.press('f');
    x++;
  }/*fn nf fnf nf nf */
  if(digitalRead(btn) == LOW){
    if(!isBtnPressed){
      Keyboard.press('n');
      Keyboard.releaseAll();
      Keyboard.press(32);
      Keyboard.releaseAll();
      delay(100);
      Keyboard.press('f');/**/
      Keyboard.releaseAll();
    }
    isBtnPressed = true;
  }else{
    isBtnPressed = false;
  }
  
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, HIGH);
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
  for (byte i = 0; i < mfrc522.uid.size; i++){
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
    Serial.println();/**/
    Keyboard.press('z');
    Keyboard.releaseAll();
    posId++;/**/
    Serial.println(posId);
    isCardTouch = true;
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, LOW);
    delay(2000);
  }else {
    Serial.println(" Access denied");
    digitalWrite(LED_R, LOW);
    delay(200);
    digitalWrite(LED_R, HIGH);
    delay(200);
    digitalWrite(LED_R, LOW);
    delay(200);
    digitalWrite(LED_R, HIGH);
    isCardTouch = false;
    delay(1000);
  }
  
  
  if(posId == 3){
    posId = 0;
  }
} 
