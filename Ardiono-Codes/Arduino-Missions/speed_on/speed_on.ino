#include <Keyboard.h>
#include "pitches.h"

#define BlueLed 5
#define RedLed 2
#define GreenLed 4 
#define YellowLed 3

#define BlueBtn 9
#define RedBtn 7
#define YellowBtn 6
#define GreenBtn 8
#define buzzer  A3

#define Arr_Num 4
int btns[Arr_Num]= {BlueBtn,RedBtn,YellowBtn,GreenBtn};
int leds[Arr_Num]= {BlueLed,RedLed,YellowLed,GreenLed};
bool isBtnPressed[Arr_Num] = {false, false, false, false};
long ledTime;
int i;
int points = 20;
int ledRnd = 0;
int level = 0;
int delayTime = 700;


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
  if(ledRnd % 10 == 0){
    if(level == 3){
      winGame();
      //if the level is 3 - send 'm' to show finish page
      Keyboard.press('s');
      Keyboard.releaseAll();
      Keyboard.end();
    }else{
      winRound();
      level++;
      //if the level is change send this key to JS to show it on HTML
      Keyboard.press('1');
      Keyboard.releaseAll();
      points += 5;
      delayTime -= 120;
      delay(200);
    }
  }
  /*1t1t1*/
  long pressTime = 10000;
  randomSeed(analogRead(1));
  i = random(0, 4);
  digitalWrite(leds[i], HIGH);
  ledSounds();
  ledTime = millis();
  delay(delayTime);
    
  while(!isBtnPressed[i]){
    if(digitalRead(btns[i]) == LOW){
      ledSounds();
      isBtnPressed[i] = true;
      digitalWrite(leds[i], LOW);
      pressTime = millis() - ledTime;
      ledRnd++;
    }
  }
   
  if(pressTime < (delayTime+500) && isBtnPressed[i]){
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
  isBtnPressed[i] = false;
  delay(delayTime);
  
}

void winRound(){
  int ledIndex = 0;
  int currentLed = 0;
  int toShow[4] = {0,1,2,3};
  for(int i = 0; i < 20; i++){
    currentLed=toShow[ledIndex];
    digitalWrite(leds[currentLed],HIGH);
    delay(150);
    digitalWrite(leds[currentLed],LOW);
    ledIndex = (ledIndex + 1)%4;
  }
  winSound();
}

void winGame(){
  for(int i = 0; i < 100; i++){
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

void winSound(){
  for(int i = 0; i < 1; i++){
    for(uint8_t nLoop = 0;nLoop < 2;nLoop ++){
      tone(buzzer,NOTE_A5);
      delay(50);
      tone(buzzer,NOTE_B5);
      delay(50);
      tone(buzzer,NOTE_C5);
      delay(50);
      tone(buzzer,NOTE_B5);
      delay(50);
      tone(buzzer,NOTE_C5);
      delay(50);
      tone(buzzer,NOTE_D5);
      delay(50);
      tone(buzzer,NOTE_C5);
      delay(50);
      tone(buzzer,NOTE_D5);
      delay(50);
      tone(buzzer,NOTE_E5);
      delay(50);
      tone(buzzer,NOTE_D5);
      delay(50);
      tone(buzzer,NOTE_E5);
      delay(50);
      tone(buzzer,NOTE_E5);
      delay(50);
    }
    noTone(buzzer);
  }
}
