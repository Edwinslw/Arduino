#include<LiquidCrystal.h>
#define EN        8 
//Direction pin
#define X_DIR     12 
#define Y_DIR     6
#define Z_DIR     7

//Step pin
#define X_STP     13
#define Y_STP     3 
#define Z_STP     4 
//DRV8825
int delayTime=70; //Delay between each pause (uS)
int stpsx=1210;// Steps to move
int stpsy=3200;
int waktucelup=500;
int tunda=100;
int sampel=8;
int balik=sampel-1;
int langkah=1;


void step(boolean dir, byte dirPin, byte stepperPin, int steps)

{

  digitalWrite(dirPin, dir);

  delay(100);

  for (int i = 0; i < steps; i++) {

    digitalWrite(stepperPin, HIGH);

    delayMicroseconds(delayTime); 

    digitalWrite(stepperPin, LOW);

    delayMicroseconds(delayTime); 

  }

}
void sampling(){
    step(true, Y_DIR, Y_STP, stpsy);
    delay(waktucelup);
    step(false, Y_DIR, Y_STP, stpsy);
    delay(tunda);
}

void washing(){
    for(int j=0; j<2;j++){
      step(true, Y_DIR, Y_STP, stpsy);
      delay(100);
      step(false, Y_DIR, Y_STP, stpsy);
      delay(100);
      }
  delay(tunda);
}

void motorx(bool dir,int x){
  step(dir, Z_DIR, Z_STP,x*stpsx);
  delay(tunda);
}
void setup(){
  Serial.begin(9600);

  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);
  
}

void loop(){
  int i=0;
  while (i<sampel){
    if(i%2==1||i==0){
      sampling();
    }
    else if(i%2==0&&i!=0){
      washing();
    }
    i++;
    if(i==sampel){
      int k=0;
      while(k<balik){
        motorx(true,langkah);
        i--;
        if(sampel%2==0){
          if(k%2==1){
            sampling();
          }
          else if(k%2==0){
            washing();
          }
        }
        else{
          if(k%2==0){
            sampling();
          }
          else if(k%2==1&&k!=balik){
            washing();
          }
        }
    k++;    
    }
  i=0;  
  }
  else{
    motorx(false,langkah);
  }
}
}
