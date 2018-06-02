#include <TimeLib.h>
#include <TimeAlarms.h>
#include <OneWire.h>

#define M1  2  //Misturador
#define Buz 3  //Buzzer
#define CV1 4  //Valvula de entrada de água do sistema
#define CV2 5  //Valvula de saída TK1
#define CV3 6  //Valvula de entrada TK2
#define CV4 7  //Valvula de saída TK2
#define CV5 8  //Valvula de entrada TK3
#define CV6 9  //Valvula de saída TK3
#define CV7 10 //Valvula de saída do sistema para fermentação
#define CV8 11 //Valvula de resfriamento
#define B1 12  //Bomba
#define Q1 13
#define Q2 14
#define Q3 15
#define FT1 16 //Sensor de vazão de entrada
#define PT1 17 //Sensor capacitivo de fluido na entrada da bomba

OneWire ds(22); // Sensor TEmperatura no Pino 10
AlarmId id;

byte Ts1addr[8]; // Endereço dos thermistores
byte Ts2addr[8];
byte Ts3addr[8];
byte type_s;                // Colocar uma variavel por sensor
float temp[3];              // Temperatura atual
int Tset[3] = {25, 26, 27}; // Temperatura setada
int litragem1 = 1;
int litragem2;
byte Temperatura[5];
//byte curvaaq[5];
byte Tempocoz[5];
byte Tempolup[3];
byte Tempoferv;
byte Temperaturafer;
byte Tempferm;

void setup()
{
  byte z;
  for (z = 2; z < 16; z++)
  { //define as portas como saída e testa
    pinMode(z, OUTPUT);
    digitalWrite(z, HIGH);
    delay(1000);
    digitalWrite(z, LOW);
  }

  Serial.begin(9600);
  while (!Serial);
  registrads();
  printaddr();
  setTime(0, 0, 0, 5, 20, 18);
  Alarm.timerRepeat(10, controlatemp);
  Serial.println();
  Serial.println();
  Serial.println("Inicio");
}

void loop()
{
  float p;
  int val;
  val = (analogRead(2));
  p = (val * 0.0366) + 1;
  Serial.println(val);
  Alarm.delay(1000);

  enchetk1(litragem1);
  aquecetk1(Temperatura[1]);
  transferetk1();
  enchetk1(litragem2);
  aquecetk2();
  transferetk2();
  //aquecer TK1
  transferetk1();
  //agitatk2 quantos minutos?
  transferetk2();
  fervura();
  resfriamento();
  saida();
}
