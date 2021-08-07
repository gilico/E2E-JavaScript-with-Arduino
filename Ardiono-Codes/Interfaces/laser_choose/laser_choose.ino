#include <Keyboard.h>
#define sensorA 2
#define sensorB 3
#define sensorC 4
#define sensorD 5

int answerA = 0;
int answerB = 0;
int answerC = 0;
int answerD = 0;


#define arrSize 4
int answers[arrSize] = {answerA,answerB,answerC,answerD};
int sensors[arrSize] = {sensorA,sensorB,sensorC,sensorD};
char letters[arrSize] = {'a' , 'b' , 'c' , 'd'};
bool isBtnPressed = false;
void setup() {
  
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  for(int i = 0; i < arrSize; i++){
    if(digitalRead(sensors[i]) == 0){
      if(!isBtnPressed){
        Keyboard.press(letters[i]);
        Keyboard.releaseAll();
      }
      isBtnPressed = true;
    }else{
      Keyboard.releaseAll();
      isBtnPressed = false;
    }
    delay(500);
  }
}
