#include <Keyboard.h>
#include "pitches.h"
#define BlueLedPin 5
#define RedLedPin 2
#define GreenLedPin 4
#define YellowLedPin 3

#define BlueBtnPin 9
#define RedBtnPin 7
#define YellowBtnPin 6
#define GreenBtnPin 8
#define buzzer  A3

#define BTN_NUM 4
int btns[BTN_NUM]= {BlueBtnPin,RedBtnPin,YellowBtnPin,GreenBtnPin};
int leds[BTN_NUM]= {BlueLedPin,RedLedPin,YellowLedPin,GreenLedPin};

const int lastLed = 6;
int ledNumber = 1;
int sequence[lastLed];
int userSequence[lastLed];
int gameStep = 0;
int flag;
boolean gameIsOn = false;
int lightSpeed = 600;
bool isLevelsFinish = false;

void setup() {
  Keyboard.begin();
  Serial.begin(9600);
  for(int k = 0 ; k < BTN_NUM ; k++){ 
    pinMode(btns[k], INPUT_PULLUP);
    pinMode(leds[k], OUTPUT);
    digitalWrite(leds[k], LOW);
  }
}

void loop() {
  if(!isLevelsFinish){
    if(gameIsOn == false && ledNumber == 1){
      generateSequence();
    }
  
    waitToStart();
    delay(1000);
  
    if(gameIsOn == true){ 
      showSequence();
      checkSequence();
    }
    
    
    if(userSequence[lastLed] == sequence[lastLed]){
      delay(300);
      winRound();
      gameStep++;
      sendMissionLevel();
    }
  }
}

void waitToStart(){
  int ledIndex = 0;
  int currentLed = 0;
  int toShow[4] = {0,1,2,3};
  
  for(int i = 0; i < 1000; i++){
    if(gameIsOn == false){
      if(digitalRead(BlueBtnPin) == LOW){
        gameIsOn = true;
      }else{ 
        currentLed = toShow[ledIndex];

        digitalWrite(leds[currentLed],HIGH);
        delay(600);
        digitalWrite(leds[currentLed],LOW);
        
        ledIndex = (ledIndex + 1)%4;
      }
    }
  }
}

void generateSequence(){
  randomSeed(analogRead(1));
  for (int i = 0; i < lastLed; i++) {
    sequence[i] = random(0,4);
  }
}


void showSequence(){
  for(int k = 0; k < BTN_NUM; k++){
    digitalWrite(leds[k], LOW);  
  }
  
  for(int i = 0 ; i < ledNumber ; i++){ 
    //Serial.println(leds[sequence[i]]);
    digitalWrite(leds[sequence[i]], HIGH);
    ledSounds();
    delay(lightSpeed);
    digitalWrite(leds[sequence[i]], LOW);
    ledSounds();
    delay(lightSpeed);
  }
}

void winRound(){
  int ledIndex = 0;
  int currentLed = 0;
  int toShow[4] = {0,1,2,3};
  winSound();
  for(int i = 0; i < 12; i++){
    currentLed=toShow[ledIndex];
    digitalWrite(leds[currentLed],HIGH);
    delay(100);
    digitalWrite(leds[currentLed],LOW);
    ledIndex = (ledIndex + 1)%4;
  }
  
  lightSpeed = lightSpeed - 120;
  ledNumber = 1;
  gameIsOn = false;
}

void wrongAnswer(){
  for(int i = 0; i < 4; i++){
    for(int k = 0; k < BTN_NUM; k++){
      digitalWrite(leds[k],HIGH);
      tone(buzzer, 131);
    }
    delay(300);
    for(int n = 0; n < BTN_NUM; n++){
      digitalWrite(leds[n],LOW);
      noTone(buzzer);
    }
    delay(300);
  }
  // if wrong answer send key to js so strikes counter grow
  Keyboard.press('t'); 
  Keyboard.releaseAll();
  //if user insert wrong btn - show him again the sequance
  showSequence();
  //after the sequance is shown - let him try again;
  checkSequence();
  /*
   * ttt2t2tm
  ledNumber = 1;
  gameIsOn = false;
  lightSpeed = 600; 
  */ 
}

void sendMissionLevel(){
  if(gameStep == 3){
    for(int i = 0; i < BTN_NUM; i++){
      digitalWrite(leds[i], LOW);
    }
    //if the level is 3 - send 'm' to show finish page
    Keyboard.press('m');
    Keyboard.releaseAll();
    Keyboard.end();
    ledNumber = 1;
    isLevelsFinish = true;
    lightSpeed = 600; 
  }else{
    //if the level is change send this key to JS to show it on HTML
    Keyboard.press('2');
    Keyboard.releaseAll();
  }
}



void checkSequence(){
  for(int i = 0; i < ledNumber; i++ ){
    int flag = 0;
    while(flag == 0){
      //Blue light*******
      if (digitalRead(BlueBtnPin) == LOW){
        digitalWrite(BlueLedPin, HIGH);
        ledSounds();
        userSequence[i] = 0;
        flag = 1;
        delay(lightSpeed);
        for(int k = 0; k < BTN_NUM; k++){
          if (userSequence[i] != sequence[i]){
            wrongAnswer();
            return; 
          }
        }
        digitalWrite(BlueLedPin, LOW);
        ledSounds();
      }

      //red light*******
      if (digitalRead(RedBtnPin) == LOW){
        digitalWrite(RedLedPin, HIGH);
        ledSounds();
        userSequence[i] = 1;
        flag = 1;
        delay(lightSpeed);
        for(int k = 0; k < BTN_NUM; k++){
          if (userSequence[i] != sequence[i]){
            wrongAnswer();
            return;  
          }
        }
        digitalWrite(RedLedPin, LOW);
        ledSounds();
      }

      //Yellow light*******
      if (digitalRead(YellowBtnPin) == LOW){
        digitalWrite(YellowLedPin, HIGH);
        ledSounds();
        userSequence[i] = 2;
        flag = 1;
        delay(lightSpeed);
        for(int k = 0; k < BTN_NUM; k++){
          if (userSequence[i] != sequence[i]){
            wrongAnswer();
            return;
          }
        }
        digitalWrite(YellowLedPin, LOW);
        ledSounds();
      }

      //Green light*******
      if (digitalRead(GreenBtnPin) == LOW){
        digitalWrite(GreenLedPin, HIGH);
        ledSounds();
        userSequence[i] = 3;
        flag = 1;
        delay(lightSpeed);
        for(int k = 0; k < BTN_NUM; k++){   
          if (userSequence[i] != sequence[i]){
            wrongAnswer();
            return;
          }
        }
        digitalWrite(GreenLedPin, LOW);
        ledSounds();
      }
    }
  }
  ledNumber++;
}



    /*---------SOUNDS--------------*/

void ledSounds(){
  if(digitalRead(BlueLedPin) == HIGH){
    tone(buzzer, 1047);
  }else if(digitalRead(RedLedPin) == HIGH){
    tone(buzzer, 1319);
  }else if(digitalRead(YellowLedPin) == HIGH){
    tone(buzzer, 262);
  }else if(digitalRead(GreenLedPin) == HIGH){
    tone(buzzer, 523);
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


 
