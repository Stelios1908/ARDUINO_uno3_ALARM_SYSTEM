// C++ code
//
#include <string.h>
int ZONE1=7;
int ZONE2=6;
int ZONE3=5;
int ZONE4=4;
int ZONE5=3;
int ZONE6=2;
int Armed=8;
int Siren=9;
int Password=13;
int Ready=11;
int Alarm=12;

int sensor1=A0;
int sensor2=A1;
int sensor3=A2;
int sensor4=A3;
int sensor5=A4;
int sensor6=A5;
  
int ledstate=LOW;
unsigned long pm=0;
const long interval=80;

int cnt=0;



void setup()
{
  pinMode(ZONE1, OUTPUT);
  pinMode(ZONE2, OUTPUT);
  pinMode(ZONE3, OUTPUT);
  pinMode(ZONE4, OUTPUT);
  pinMode(ZONE5, OUTPUT);
  pinMode(ZONE6, OUTPUT);
  pinMode(Siren, OUTPUT);
  pinMode(Ready, OUTPUT);
  pinMode(Alarm, OUTPUT);
  pinMode(Armed, OUTPUT);
    
  pinMode(Password,INPUT);

 
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
  pinMode(sensor3,INPUT);
  pinMode(sensor4,INPUT);
  pinMode(sensor5,INPUT);
  pinMode(sensor6,INPUT);
  
  Serial.begin(9600);
}

void loop()
{

  if(digitalRead(Ready)==1 && digitalRead(Password) == 1){
   digitalWrite(Armed , HIGH);
  }else{
    digitalWrite(Armed , LOW);
  }
  
  if(digitalRead(Armed)==1){
   int i=0;
    
   while(digitalRead(Armed)==1){
      if(analogRead(i)< 650 || analogRead(i)> 700 ){
         tone(Siren,1000);
         delay(100);
         tone(Siren,2000);
         delay(100);
         digitalWrite(Alarm,HIGH);
         digitalWrite(7-i,HIGH);
        }
      
      if(digitalRead(Password)==0 ){
          noTone(Siren);
          digitalWrite(Alarm,LOW);
          digitalWrite(Armed,LOW);
          break;
      }
        i++;
        if(i==6){i=0;}
    }
     
  }
  else{ //here inside  when the system ia disArmed and check Zones
          Serial.print(analogRead(A1));
          Serial.print('\n');
         cnt=0;
         for(int j=0;j<6;j++){
         //call this function for any sensor and check if Zone is Open or Close
         checkStateSensor(j); 
         }
    
         if(cnt ==6){digitalWrite(Ready,HIGH);}
         else{ digitalWrite(Ready,LOW);}
      }  

} 
// --------------------functions-------------------------
void checkStateSensor(int sensorNo){
    if(!(analogRead(sensorNo) < 700 && analogRead(sensorNo)> 650))
    {
      unsigned long cm = millis();
      if(cm - pm >= interval){
        pm=cm;
        if(ledstate==LOW){ledstate=HIGH;}
        else{ledstate=LOW;}
      }
      digitalWrite(7-sensorNo,ledstate);
    }
     else{digitalWrite(7-sensorNo, LOW);
          cnt++;} 
    }
  


  
  
  
  