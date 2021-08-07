#include <Keyboard.h>
#define potz A3
#define button 4
int prevVal = 0;
bool isBtnPressed = false;
int btnCnt = 0;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  int Pval = analogRead(potz);
  int pMap = map(Pval, 0, 1023, 0, 100);

  if(isBtnPressed){
    //pMap = prevVal;
    Keyboard.print(prevVal);
    delay(250);
    isBtnPressed = false;
  }
  Keyboard.end();
  
  if(pMap > prevVal){
    Keyboard.press(KEY_UP_ARROW);
    //delay(10);
    Keyboard.release(KEY_UP_ARROW);
  }else if(pMap < prevVal){
    Keyboard.press(KEY_DOWN_ARROW);
    //delay(10);
    Keyboard.release(KEY_DOWN_ARROW);
  }
  delay(10);
  Keyboard.releaseAll();

  prevVal = pMap;

  if(digitalRead(button) == LOW){
    isBtnPressed = true;
    btnCnt++;
    Keyboard.press(KEY_TAB);
    delay(100);
    Keyboard.release(KEY_TAB);
  }

  if(btnCnt == 5){
    Keyboard.press(32);
    Keyboard.release(32);
    btnCnt = 0;
  }


  
  Serial.println(btnCnt);
}
