#include <TimeLib.h>
#include <TimeAlarms.h>
#include <OneWire.h>

#define M1  39  //Misturador
#define Buz 3  //Buzzer
#define CV1 40  //Valvula de entrada de água do sistema
#define CV2 28  //Valvula de saída TK1
#define CV2d 26
#define CV3 24  //Valvula de entrada TK2
#define CV3d 22
#define CV4 23  //Valvula de saída TK2
#define CV4d 25
#define CV5 27  //Valvula de entrada TK3
#define CV5d 29
#define CV6 31  //Valvula de saída TK3
#define CV6d 33
#define CV7 35 //Valvula de saída do sistema para fermentação
#define CV7d 37
#define CV8 38 //Valvula de resfriamento
#define B1 36  //Bomba
#define Q1 30
#define Q2 32
#define Q3 34
#define FT1 16 //Sensor de vazão de entrada
#define PT1 17 //Sensor capacitivo de fluido na entrada da bomba

OneWire ds(10); // Sensor TEmperatura no Pino 10
AlarmId id;

byte Ts1addr[8]; // Endereço dos thermistores
byte Ts2addr[8];
byte Ts3addr[8];
byte type_s;                // Colocar uma variavel por sensor
float temp[3];              // Temperatura atual
int Tset[3] = {25, 26, 27}; // Temperatura setada
bool term = 0;
bool term2 = 0;
// variaveis recebiveis

int litra[2] = {18,20};
//int litra1;
//int litrag2;
int Temperatura[5] = {65, 68, 70, 73, 78};
//byte curvaaq[5];
int Tempocoz[5] = {20, 25, 10, 10, 5};
int Tempolup[3] = {45, 55, 0}; 
int Tempoferv = 60;
int Temperaturafer = 100;
int Tempferm = 25;

void setup()
{
  byte z;
 /* for (z = 2; z < 16; z++)
  { //define as portas como saída e testa
    pinMode(z, OUTPUT);
    digitalWrite(z, HIGH);
    delay(1000);
    digitalWrite(z, LOW);
  }*/

  Serial.begin(9600);
delay(1000); 
 // while (!Serial);
  registrads();
  printaddr();
  setTime(0, 0, 0, 5, 20, 18);
  Alarm.timerRepeat(10, controlatemp);
  Serial.println();
  Serial.println();
  Serial.println("Inicio Duds");
}

void loop()
{
  recebedados();
  float p;
  int val;
  val = (analogRead(2));
  p = (val * 0.0366) + 1;
  Serial.println(val);
  Alarm.delay(1000);

  enchetk1(litra[1]);
  aquecetk1(Temperatura[1]+5);  //5 a mais que primeira Temperatura
  transferetk1();
  enchetk1(litra[2]);
  aquecetk2();
  transferetk2();
  transferetk1();
  //agitatk2 quantos minutos?
  transferetk2();
  fervura();
  resfriamento();
  saida();
}
