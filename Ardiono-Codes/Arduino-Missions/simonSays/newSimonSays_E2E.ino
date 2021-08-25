#include <Keyboard.h>
#include "pitches.h"
#define BlueLedPin 5
#define RedLedPin 2
#define GreenLedPin 4
#define YellowLedPin 3

#define BlueBtnPin 7
#define RedBtnPin 9
#define YellowBtnPin 6
#define GreenBtnPin 8
#define buzzer  A3

#define BTN_NUM 4
int btns[BTN_NUM]= {BlueBtnPin,RedBtnPin,YellowBtnPin,GreenBtnPin};
int leds[BTN_NUM]= {BlueLedPin,RedLedPin,YellowLedPin,GreenLedPin};

const int lastLed = 6;
int ledNumber = 0;
int sequence[lastLed];
int userSequence[lastLed];
int gameStep = 0;
int flag;
bool gameIsOn = false;
bool isCorrectSequence = false;
int lightSpeed = 480;

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
  while(!gameIsOn){
    gameIsOn = waitToStart();
  }
  
  showSequence();  
  
  if(!checkCurrentSequence()){
    wrongAnswer();
  }

  if(ledNumber == lastLed){    
    if(checkLastLed()){
      delay(300);
      winRound();
      resetGame();
      gameIsOn = false;
    }
  }
}

bool waitToStart(){
  int ledIndex = 0;
  int currentLed = 0;
  int toShow[4] = {0,1,2,3};
  
  for(int i = 0; i < BTN_NUM; i++){
    if(gameIsOn == false){
      if(digitalRead(BlueBtnPin) == LOW){
        generateSequence();
        delay(1000);
        return true;
      }else{ 
        currentLed = toShow[ledIndex];

        digitalWrite(leds[currentLed],HIGH);
        delay(600);
        digitalWrite(leds[currentLed],LOW);
        
        ledIndex = (ledIndex + 1) % 4;
      }
    }
  }
  return false;
}

void generateSequence(){
  randomSeed(analogRead(0));
  for (int i = 0; i < lastLed; i++) {
    sequence[i] = random(0,4);
  }
}


void showSequence(){
  //turn all leds off
  for(int k = 0; k < BTN_NUM; k++){
    digitalWrite(leds[k], LOW);  
  }

  for(int i = 0 ; i <= ledNumber ; i++){ 
    digitalWrite(leds[sequence[i]], HIGH);
    ledSounds();
    delay(lightSpeed);
    digitalWrite(leds[sequence[i]], LOW);
    ledSounds();
    delay(lightSpeed);
  }
}

bool checkCurrentSequence(){
  for(int k = 0; k <= ledNumber; k++){
    bool isCorrectBtn = false;
    while(!isCorrectBtn){
      userSequence[k] = PressBtnNumbers(false);
      delay(lightSpeed);
      
      if(userSequence[k] != sequence[k]){
        return false;        
      }else{
        isCorrectBtn = true;
      }
    }
  }
  ledNumber++;
  //if the for loop is end it's all correct
  return true;
}

int PressBtnNumbers(bool isPress){
  int numbers[BTN_NUM] = {0,1,2,3};
  
  while(!isPress){
    for(int i = 0; i < BTN_NUM; i++){
      if(digitalRead(btns[i]) == LOW){
        digitalWrite(leds[i], HIGH);
        ledSounds();
        delay(lightSpeed);
        digitalWrite(leds[i], LOW);
        ledSounds();
        isPress = true;
        return numbers[i];
      }
    }
  }
}

void wrongAnswer(){
  //turn ON and OFF all the leds for 4 times;
  for(int i = 0; i < BTN_NUM; i++){
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
}

bool checkLastLed(){
  if(userSequence[ledNumber-1] != sequence[lastLed-1]){
    return false;
  }
  return true;
}

void resetGame(){
  Keyboard.press('e'); //press 'e' to js when game is end
  Keyboard.releaseAll();
  delay(210);
  Keyboard.press('f');
  Keyboard.releaseAll();
  ledNumber = 0;
}

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
