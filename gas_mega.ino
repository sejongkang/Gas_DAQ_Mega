#include <glcd.h>
#include <glcd_Buildinfo.h>
#include <glcd_Config.h>
#include <fonts/allFonts.h>
#include <string.h>

const int senPin1 = 97;
const int senPin2 = 96;
const int senPin3 = 95;
const int senPin4 = 94;
const int senPin5 = 93;
const int senPin6 = 92;
const int pumpPin = 2;
const int dhtPin = 3;

char * serial = "202001";

int values[6];
int i = 0;
int j = 0;
char buf[128], result[64];
char LCDbuf[128];
char sensors[7][9] = {"","TGS-2600\0", "TGS-2602\0", "TGS-2603\0", "TGS-2610\0", "TGS-2620\0", "TGS-0826\0"};
int RUN=1;
void setup() {
  delay(5000);
  GLCD.Init();  
  GLCD.SelectFont(System5x7);
  GLCD.CursorTo(1,3);
  GLCD.print("Device Init Start..");
  
  // put your setup code here, to run once:
  Serial1.begin(9600);
  pinMode(senPin1, OUTPUT);
  pinMode(senPin2, OUTPUT);
  pinMode(senPin3, OUTPUT);
  pinMode(senPin4, OUTPUT);
  pinMode(senPin5, OUTPUT);
  pinMode(senPin6, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(senPin1, HIGH);
  digitalWrite(senPin2, HIGH);
  digitalWrite(senPin3, HIGH);
  digitalWrite(senPin4, HIGH);
  digitalWrite(senPin5, HIGH);
  digitalWrite(senPin6, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pumpPin, HIGH);
  delay(3000);
  digitalWrite(pumpPin, LOW);
  GLCD.ClearScreen();
  GLCD.CursorTo(0,0);
  sprintf(LCDbuf,"Serial Num : %s", serial);
  GLCD.print(LCDbuf);
  memset(result, '\0', sizeof(result));
  strcat(result, serial);
  strcat(result, " ");
  for(i=0; i<6; i++){        //result로 합치기
    sprintf(buf,"%d ",analogRead(i));
    sprintf(LCDbuf," %s : %04d ", sensors[i+1], analogRead(i));
    GLCD.CursorTo(1,i+2);
    GLCD.print(LCDbuf);
    strcat(result, buf);
  }

  Serial1.println(result);
  delay(1000);
}

void setLCD(int x, int y, String txt){
  GLCD.SelectFont(System5x7);
  GLCD.CursorTo(0,1);
  GLCD.print(serial);
  GLCD.CursorTo(x,y);
  GLCD.print(txt);
}
