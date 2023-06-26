#include <Keypad.h>
int passout=11;

int Pass_Length= 6;
char data[6];
char MasterArm[6]= "1741A";
char MasterDisArm[6]="1741B";
char testkey[2] ="D";
const byte ROWS = 4; 
const byte COLS = 4; 
byte data_count=0;
byte mastercount=0;
char kagelo = '#';

int chechReady=2;
int Siren =12;
int test  =13;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {6, 5, 4, 3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  pinMode(passout,OUTPUT);
  pinMode(chechReady,INPUT);
  pinMode(Siren,OUTPUT);
  Serial.begin(9600);
  pinMode(test,OUTPUT);
}
  
void loop(){
  char customKey = customKeypad.getKey();

   if (customKey){
      Serial.print('\n');
      Serial.print(customKey);
    
     data[data_count] = customKey;  
       if(customKey==kagelo){
       clearData();
       Serial.print("\ncode clear try again");
       data_count--;
       }
     data_count++; 
    }

  if(data_count == Pass_Length-1){
       if(!strcmp(data, MasterArm)){
           if(digitalRead(chechReady)==1){ 
              Serial.print("\nCorrect The System Armed]\n");
              digitalWrite(passout,HIGH);
             }
            else{
              tone(Siren,1000);
              delay(10);
              noTone(Siren);
              Serial.print("\nZones Open,Please close Zones and try again\n");
              }
       }
    else if(!strcmp(data, MasterDisArm)){
       Serial.print("\nCorrect The System DisArmed\n");
       digitalWrite(passout, LOW);
       }
      else{Serial.print("\nincorect");
       }
    
      clearData();
                                    
     }
  
     if(!strcmp(data,testkey))
      {
       healthCheck();
      }

  

  }
//--------------------------------------------
void clearData(){
  while(data_count !=0){
    data[data_count--]=0;
  }
}


void healthCheck(){
  {
     analogWrite(13, 600);
     delay(1900);
     analogWrite(13,680); 
  }
}

  

