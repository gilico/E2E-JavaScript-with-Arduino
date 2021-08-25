#include <Keyboard.h>
#include "pitches.h"

#define BlueLed 5
#define RedLed 2
#define GreenLed 4 
#define YellowLed 3
#define WhiteLed 14

#define BlueBtn 7
#define RedBtn 9
#define YellowBtn 6
#define GreenBtn 8
#define WhiteBtn 16

#define buzzer  A3

#define Arr_Num 5
int btns[Arr_Num]= {BlueBtn, YellowBtn, GreenBtn, RedBtn, WhiteBtn};
int leds[Arr_Num]= {BlueLed, YellowLed, GreenLed, RedLed, WhiteLed};
bool isBtnPressed[Arr_Num] = {false, false, false, false};

long ledTime;
int currLed;
int points = 25;
int ledRnd = 0;
int delayTime = 250;
bool gameIsOn = false;

void setup() {
  Keyboard.begin();
  Serial.begin(9600);
  for(int k = 0 ; k < Arr_Num ; k++){ 
    pinMode(btns[k], INPUT_PULLUP);
    pinMode(leds[k], OUTPUT);
    digitalWrite(leds[k], LOW);
  }
}

void loop() {
  if(!gameIsOn){
    gameIsOn = waitToStart();
    delay(1000);
  }

  if(gameIsOn){
    CheckLedAndBtn();
  }

  if(ledRnd % 15 == 0){
    IfGameIsEnd();
  }
}

bool waitToStart(){
  int ledIndex = 0;
  int ledPos = 0;
  int toShow[Arr_Num] = {0,1,2,3,4};
  
  for(int i = 0; i < 1000; i++){
    if(gameIsOn == false){
      if(digitalRead(GreenBtn) == LOW){
        return true;
      }else{ 
        ledPos = toShow[ledIndex];

        digitalWrite(leds[ledPos],HIGH);
        delay(600);
        digitalWrite(leds[ledPos],LOW);
        
        ledIndex = (ledIndex + 1) % Arr_Num;
      }
    }
  }
  return false;
}

void checkPressTime(int pressTime){
  if(pressTime < (delayTime+400) && isBtnPressed[currLed]){
    Serial.print(points);
    Serial.println(" GOOD");
  }else{
    points--;
    // if wrong answer send key to js so strikes counter grow
    Keyboard.press('t'); 
    Keyboard.releaseAll();
    Serial.print(points);
    Serial.println(" BAD");
  }
}

void ledSounds(){
  if(digitalRead(BlueLed) == HIGH || digitalRead(BlueBtn) == LOW){
    tone(buzzer, 1047);
    delay(200);
    noTone(buzzer);
  }else if(digitalRead(RedLed) == HIGH || digitalRead(RedBtn) == LOW){
    tone(buzzer, 1319);
    delay(200);
    noTone(buzzer);
  }else if(digitalRead(YellowLed) == HIGH || digitalRead(YellowBtn) == LOW){
    tone(buzzer, 262);
    delay(200);
    noTone(buzzer);
  }else if(digitalRead(GreenLed) == HIGH || digitalRead(GreenBtn) == LOW){
    tone(buzzer, 523);
    delay(200);
    noTone(buzzer);
  }else{
    noTone(buzzer);
  }
}

//ttef
int prevLed = -1;
long pressTime;
void CheckLedAndBtn(){
  randomSeed(analogRead(1));
  //use this loop so it's will not be the same led index
  while(prevLed == currLed){
    currLed = random(0, Arr_Num);
  }
  digitalWrite(leds[currLed], HIGH);
  ledSounds();
  ledTime = millis();
  delay(delayTime);
      //
  while(!isBtnPressed[currLed]){
    if(digitalRead(btns[currLed]) == LOW){
      ledSounds();
      isBtnPressed[currLed] = true;
      digitalWrite(leds[currLed], LOW);
      pressTime = millis() - ledTime;
      ledRnd++;
    }
  } 
  prevLed = currLed;
  checkPressTime(pressTime);  
  isBtnPressed[currLed] = false;
  delay(delayTime);
}

void IfGameIsEnd(){
  Keyboard.press('e');
  Keyboard.releaseAll();
  ledRnd = 0;
  delay(220);
  Keyboard.press('f'); //js keydown full screen
  Keyboard.releaseAll();
  winGame();
  gameIsOn = false;
}

void winGame(){
  for(int i = 0; i < 10; i++){
    for(int k = 0; k < Arr_Num; k++){
      digitalWrite(leds[k],HIGH);
    }
    delay(300);
    for(int n = 0; n < Arr_Num; n++){
      digitalWrite(leds[n],LOW);
    }
    delay(300);
  }
}
