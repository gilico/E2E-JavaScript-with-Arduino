#include <Keyboard.h>
#define sensorA A0
#define sensorB A1
#define sensorC A2
#define sensorD A3
/*c
int answerA = 0;
int answerB = 0;
int answerC = 0;
int answerD = 0;
sf
*/
#define arrSize 4
/*int answers[arrSize] = {answerA,answerB,answerC,answerD};cbb*/
int sensors[arrSize] = {sensorA,sensorB,sensorC,sensorD};
char letters[arrSize] = {'a' , 'b' , 'c' , 'd'};
bool isBtnPressed = false;

void setup() {
  Keyboard.begin();
}
/*cb*/
void loop() {
  
  for(int i = 0; i < arrSize; i++){
    int sensVal = analogRead(sensors[i]);
    if(sensVal < 800){
      if(!isBtnPressed){
        Keyboard.press(letters[i]);
        Keyboard.releaseAll();
        delay(2000);
      }
      isBtnPressed = true;
    }else{
      Keyboard.releaseAll();
      isBtnPressed = false;
    }
    delay(100);
  }  
}/*ddbaaccddd*/
