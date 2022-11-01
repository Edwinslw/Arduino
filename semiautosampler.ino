#define EN        8 
//Direction pin
//#define X_DIR     5 rusak
#define Y_DIR     6
#define Z_DIR     7

//Step pin
//#define X_STP     2 rusak
#define Y_STP     3 
#define Z_STP     4 

//DRV8825
int delayTime=70; //Delay between each pause (uS)
int stpsx=1210;// Steps to move
int stpsy=3200;

//Misc.
int waktucelup=500;
int tunda=100;
int pos_awal=0;
int pos_akhir,langkah,state;


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
      //sampling();
      delay(tunda);
}

void motorx(bool dir,int x){
  step(dir, Z_DIR, Z_STP,x*stpsx);
  delay(tunda);
}
void setup(){
  Serial.begin(115200);
  Serial.setTimeout(10);

  //pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);
  
}

void loop(){
  while(!Serial.available());
  int input=Serial.readString().toInt();
  if(input!=30&&input!=40){
    pos_akhir=input;
  }
  langkah=pos_akhir-pos_awal;
  if(langkah==5){
    motorx(false,3);
  }
  else if(langkah==-5){
    motorx(true,3);
  }
  else if(langkah<0){
    motorx(true,abs(langkah));
  }
  else{
    motorx(false,abs(langkah));
  }
  pos_awal=pos_akhir;
  Serial.print(pos_akhir);
  //while(!Serial.available());
  //else{input=Serial.readString().toInt();
  if(input==30||input==40){
    state=input;
  
    if (state==40){
      sampling();
      Serial.print(40);
    }
    else{
      washing();
      Serial.print(30);
  }
}
}
