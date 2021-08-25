#include <Servo.h>
#include <Keypad.h>

Servo ServoMotor;
#define passArr 7
#define letters 5

String passwords[passArr] = {"24425","13431","68486","41852","99999", "12345","32567"};  // change the password here, just pick any 3 numbers
int position = 0;
const byte ROWS = 4;
const byte COLS = 3;
int servoPos = 0;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int RedpinLock = 12;
int GreenpinUnlock = 2;

void setup(){
  Serial.begin(9600);
  ServoMotor.write(servoPos);
  CorrectPassword(false);
  ServoMotor.attach(11);
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);
}

void loop(){
  int keyPos = 0;
  String userPass = "";
  
  while(keyPos < letters){
    char key = keypad.getKey();
    
    if(key >= '1'){
      userPass += key;
      Serial.println(userPass);
      keyPos++;
    }
    
    if (key == '#'){
      servoPos = 0;
      ServoMotor.write(servoPos);
    }
    if (key == '*'){
      userPass = "";
      keyPos = 0;
    }
    
  }
  
  bool isLettersSame = false;
  
  for(int i = 0; i < passArr; i++){
    for(int k = 0; k < letters; k++){
      if(userPass[k] == passwords[i][k]){
        isLettersSame = true;
        if(k == 4){
          i = passArr;
          break;
        }
      }else{
        isLettersSame = false;
        break;
      }
    }
  }

  if(isLettersSame){
    CorrectPassword(true);
    Serial.println("Correct Password");
    delay(2000);
  }else{
    Serial.println("Password is incorrect");
  }
  CorrectPassword(false);
}
void CorrectPassword(bool isPass){
  if (isPass){
    digitalWrite(RedpinLock, LOW);
    digitalWrite(GreenpinUnlock, HIGH);
    servoPos += 45;
    ServoMotor.write(servoPos);
  }
  else{
    digitalWrite(RedpinLock, HIGH);
    digitalWrite(GreenpinUnlock, LOW);
    
  }
  if(servoPos > 170){
    servoPos = 0;
  }
}
