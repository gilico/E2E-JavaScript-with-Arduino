#include "pitches.h"
#include <Keyboard.h>
#define start 9
#define wire 8
#define End 7
#define buzzer  A3

#define stateNum 3
int states[stateNum] = {End,wire,start};
bool isWirePress = false;
bool gameIsOn = false;
bool gameIsEnd = false;
int strikes = 0;
int points = 100;
int level = 0;
bool isLevelsFinish = false;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  for(int i = 0; i < stateNum; i++){
    pinMode(states[i],INPUT_PULLUP);
  }
}
/**/
void loop() {
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
          isWirePress = true;
        }else{
          isWirePress = false;
        }
        delay(120);
      }else{
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
      Keyboard.press('3');
      Keyboard.releaseAll();
      if(level == 3){/**/
        //if the level is 3 - send 'm' to show finish page
        Keyboard.press('q');
        Keyboard.releaseAll();
        Keyboard.end();
        isLevelsFinish = true;
      }
    }
  }
  /*
  delay(30000);
  isLevelsFinish = false;
  */
}
