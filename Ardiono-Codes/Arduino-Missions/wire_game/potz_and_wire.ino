#include "pitches.h"
#include <Keyboard.h>

//defenition and variables of wire game
#define start 2
#define wire 3
#define End 4
#define buzzer  A3
#define LED_R 5

#define stateNum 3
int states[stateNum] = {End,wire,start};
bool isWirePress = false;
bool gameIsOn = false;
bool gameIsEnd = false;
int strikes = 0;
int points = 100;
int level = 0;
bool isLevelsFinish = false;
bool isWireGameFinish = false;

//defenition and variables of potentiometer to html
#define potz A2
#define button 16
int prevVal = 0;
bool isBtnPressed = false;
int btnCnt = 0;
long pressTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_R, OUTPUT);
  Keyboard.begin();
  for(int i = 0; i < stateNum; i++){
    pinMode(states[i],INPUT_PULLUP);
  }
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  if(!isWireGameFinish){
    WireGame();
  }else{
    PotzToHtml();
  }
  
  //reset all variebles 
  if(isPressedLong()){
    isWireGameFinish = false;
    isLevelsFinish = false;
    btnCnt = 0;
    strikes = 0;
    points = 0;
  }
}

bool isPressedLong(){
  //if btn is pressed for 3 seconds return true
  long startPress = millis();
  while(digitalRead(button) == LOW){
      pressTime = millis() - startPress;
      delay(200);
      Serial.println(pressTime);
  }

  if(pressTime >= 3000){
    return true;
  }
  return false;
}

void WireGame(){
   //after 3 levels it will turn to true
  if(!isLevelsFinish){
    //if touch the Start area
    if(digitalRead(start) == LOW){
      gameIsOn = true;
      gameIsEnd = false;
      Serial.println("GAME IS ON");
      delay(100);
    }
    
    //if touch the wire
    if(!gameIsEnd && gameIsOn){
      if(digitalRead(wire) == LOW){
        if(!isWirePress){
          tone(buzzer, 131);
          strikes++;
          points--;
          // if wrong answer send key to js so strikes counter grow
          Keyboard.press('t');
          Keyboard.releaseAll();
          // show to current points on port
          Serial.print(points);
          Serial.print(" + ");
          Serial.println(strikes);
          digitalWrite(LED_R, HIGH);
          isWirePress = true;
        }else{
          isWirePress = false;
        }
        delay(120);
      }else{
        digitalWrite(LED_R, LOW);
        noTone(buzzer);
      }
    }
    
    //if touch the End area
    if(digitalRead(End) == LOW && gameIsOn){
      gameIsOn = false;
      gameIsEnd = true;
      Serial.print("You win the game with ");
      Serial.print(points);
      Serial.println(" points");
      delay(100);
      level++;
      //if the level is change send this key to JS to show it on HTML
      //Keyboard.press('r');
      //Keyboard.releaseAll();
      if(level == 1){/**/
        //if the level is 1 - send 'm' to show finish page
        Keyboard.press('e'); //press 'e' to js when game is over
        Keyboard.releaseAll();
        isWireGameFinish = true;
        level = 0;
        isLevelsFinish = true;
        delay(250);
        Keyboard.press('f');
        Keyboard.releaseAll();
        Keyboard.end();
      }
    }
  }
}

void PotzToHtml(){
  int Pval = analogRead(potz);
  int pMap = map(Pval, 0, 1023, 0, 100);

  if(isBtnPressed){
    Keyboard.print(prevVal);
    delay(250);
    isBtnPressed = false;
  }
  Keyboard.end();
  
  if(pMap > prevVal){ 
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.releaseAll();
  }else if(pMap < prevVal){
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.releaseAll();
  }
  delay(10);
  Keyboard.end();

  prevVal = pMap;

  if(digitalRead(button) == LOW){
    isBtnPressed = true;
    btnCnt++;
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();
  }

  if(btnCnt == 5){
    Keyboard.press(32);
    Keyboard.release(32);
    btnCnt = 0;
    delay(6800);
    Keyboard.press('f');
    Keyboard.releaseAll();
  }  
  Serial.println(btnCnt);
}
