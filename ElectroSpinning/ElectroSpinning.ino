#include<Nextion.h>

//Pin input dan output
#define EN 8
//Motor poros x
#define DIR1 6
#define STP1 3

//Motor poros z
//#define DIR2 6
//#define STP2 3

/*byte kanan = 26;
byte kiri = 30;
int nganan;
int ngiri;*/

int kecepatan_manual=0;
int kecepatan_auto=0;
int delayTime=30;
bool statusotomatis;
bool kekanan;
bool kekiri;
//Nextion
//Definisi komponen tombol
//halaman 1
NexButton otomatis=NexButton(1,1,"otomatis");
NexButton manual=NexButton(1,2,"manual");
NexDSButton saklar=NexDSButton(1,3,"saklar");

//halaman 2
NexButton kembali_manual=NexButton(2,1,"kembali_manual");
NexButton kiri=NexButton(2,2,"kiri");
NexButton tambah_manual=NexButton(2,3,"tambah_manual");
NexButton kurang_manual=NexButton(2,4,"kurang_manual");
NexButton kanan=NexButton(2,5,"kanan");

//halaman 3
NexButton kembali_auto=NexButton(3,9,"kembali_auto");
NexButton jalankan=NexButton(3,5,"jalankan");
NexButton tambah_auto=NexButton(3,1,"tambah_auto");
NexButton kurang_auto=NexButton(3,2,"kurang_auto");

//halaman 4
NexDSButton homescreen=NexDSButton(4,3,"homescreen");

//Daftar objek dengan event touch
NexTouch *nex_listen_list[]={
  &saklar, &otomatis,&manual,&kembali_manual,&kiri,
  &tambah_manual,&kurang_manual,&kanan,&kembali_auto,
  &jalankan,&tambah_auto,&kurang_auto,&homescreen,NULL
};

//Touch event
//halaman 1

//saklar
//saat ditekan
void saklarPushCallback(void *ptr){
  
}
//saat dilepas
void saklarPopCallback(void *ptr){
  
}

//otomatis
//saat ditekan
void otomatisPushCallback(void *ptr){
  
}
//saat dilepas
void otomatisPopCallback(void *ptr){
  
}

//manual
//saat ditekan
void manualPushCallback(void *ptr){
  
}
//saat dilepas
void manualPopCallback(void *ptr){
  
}

//halaman 2 manual

//kembali
//saat ditekan
void kembali_manualPushCallback(void *ptr){
  
}
//saat dilepas
void kembali_manualPopCallback(void *ptr){
  
}

//tambah
//saat ditekan
void tambah_manualPushCallback(void *ptr){
  kecepatan_manual++;
}
//saat dilepas
void tambah_manualPopCallback(void *ptr){
  
}

//kurang
//saat ditekan
void kurang_manualPushCallback(void *ptr){
  if(kecepatan_manual>0){
    kecepatan_manual--;
  }
}
//saat dilepas
void kurang_manualPopCallback(void *ptr){
  
}

//kanan
//saat ditekan
void kananPushCallback(void *ptr){
  kekanan=true;
}
//saat dilepas
void kananPopCallback(void *ptr){
  kekanan=false;
}

//kiri
//saat ditekan
void kiriPushCallback(void *ptr){
  kekiri=true;
}
//saat dilepas
void kiriPopCallback(void *ptr){
  kekiri=false;
}

//halaman 3 otomatis

//kembali
//saat ditekan
void kembali_autoPushCallback(void *ptr){
  
}
//saat dilepas
void kembali_autoPopCallback(void *ptr){

}

//tambah
//saat ditekan
void tambah_autoPushCallback(void *ptr){
  kecepatan_auto++;
}
//saat dilepas
void tambah_autoPopCallback(void *ptr){
  
}

//kurang
//saat ditekan
void kurang_autoPushCallback(void *ptr){
  if(kecepatan_auto>0){
    kecepatan_auto--;
  }
}
//saat dilepas
void kurang_autoPopCallback(void *ptr){
  
}

//jalankan
//saat ditekan
void jalankanPushCallback(void *ptr){
  
}
//saat dilepas
void jalankanPopCallback(void *ptr){
  statusotomatis=true;
}

//halaman 4
//kembali
//saat ditekan
void homescreenPushCallback(void *ptr){
  statusotomatis=false;
}
//saat dilepas
void homescreenPopCallback(void *ptr){
  
}

//fungsi penggerak motor
void step(boolean dir, int dirPin, int stepperPin, int langkah)
{
  digitalWrite(dirPin, dir);
  for (int i = 0; i < langkah; i++)
    {
     digitalWrite(stepperPin, HIGH);
     delayMicroseconds(delayTime);
     digitalWrite(stepperPin, LOW);
     delayMicroseconds(delayTime);
     }
  }
  
void setup() {
  Serial.begin(9600);
  delay(500);
  pinMode(DIR1,OUTPUT);
  pinMode(STP1,OUTPUT);
  pinMode(EN,OUTPUT);
  digitalWrite(EN, LOW);
  //pinMode(DIR2,OUTPUT);
  //pinMode(STP2,OUTPUT);

  //pendaftaran touch event
  saklar.attachPush(saklarPushCallback);
  saklar.attachPop(saklarPopCallback);
  otomatis.attachPush(otomatisPushCallback);
  otomatis.attachPop(otomatisPopCallback);
  manual.attachPush(manualPushCallback);
  manual.attachPop(manualPopCallback);
  kembali_manual.attachPush(kembali_manualPushCallback);
  kembali_manual.attachPop(kembali_manualPopCallback);
  kiri.attachPush(kiriPushCallback);
  kiri.attachPop(kiriPopCallback);
  kanan.attachPush(kananPushCallback);
  kanan.attachPop(kananPopCallback);
  tambah_manual.attachPush(tambah_manualPushCallback);
  tambah_manual.attachPop(tambah_manualPopCallback);
  kurang_manual.attachPush(kurang_manualPushCallback);
  kurang_manual.attachPop(kurang_manualPopCallback);
  kembali_auto.attachPush(kembali_autoPushCallback);
  kembali_auto.attachPop(kembali_autoPopCallback);
  tambah_auto.attachPush(tambah_autoPushCallback);
  tambah_auto.attachPop(tambah_autoPopCallback);
  kurang_auto.attachPush(kurang_autoPushCallback);
  kurang_auto.attachPop(kurang_autoPopCallback);
  jalankan.attachPush(jalankanPushCallback);
  jalankan.attachPop(jalankanPopCallback);
  homescreen.attachPush(homescreenPushCallback);
  homescreen.attachPop(homescreenPopCallback);
}

void loop() {
  // put your main code here, to run repeatedly:
  nexLoop(nex_listen_list);
  if(statusotomatis==true){
    step(true,DIR1,STP1,kecepatan_auto);
    delayMicroseconds(1600);
  }
  if(kekanan==true){
    step(true,DIR1,STP1,kecepatan_manual);
    delayMicroseconds(500);
  }
  if(kekiri==true){
    step(false,DIR1,STP1,kecepatan_manual);
    delayMicroseconds(500);
  }
}
