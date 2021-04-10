// Position Control using TB6560 and stepper Motor
// Global Variables
int val=0;
int val1=0;
int val2=0;
int fcount=0;
int Gs=0;
//Kalmas Filter for better noise cancellation
#include <SimpleKalmanFilter.h>
SimpleKalmanFilter simpleKalmanFilter(2, 4, 0.001);
void setup()
{
Serial.begin(9600);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(13, OUTPUT);
digitalWrite(8, LOW); //Dir+
digitalWrite(9, LOW);  //CLK+
digitalWrite(13, LOW);  //Sts
}

int stepRotation(int s)
{
  if((s-fcount) >0)
  {
  int c=s-fcount;
  for (int i = 0; i < c; i++)
  {
  digitalWrite(9, HIGH);
  delayMicroseconds(500);
  digitalWrite(9, LOW);
  delayMicroseconds(500);
  digitalWrite(8, LOW);
  digitalWrite(13, HIGH);  //Sts
 }
  fcount=fcount+1;
  Gs=s;
 }
 
  if((s-fcount) < 0)
  {
  int c=fcount-s;
  for (int i = 0; i < c; i++)
  {
  digitalWrite(9, HIGH);
  delayMicroseconds(500);
  digitalWrite(9, LOW);
  delayMicroseconds(500);
  digitalWrite(8, HIGH);
  digitalWrite(13, LOW);  //Sts
   }
  fcount=fcount-1;
  Gs=s;
   }
 
 if((s-fcount) == 0)
  {
  int cp=s;
  digitalWrite(9, LOW);
  delayMicroseconds(500);
  digitalWrite(9, LOW);
  fcount=fcount;
  s=s;
  Gs=s;
  digitalWrite(13, LOW);  //Sts
 }
 }

void loop()
{  
   int c=analogRead(A0);  //Potentio Meter
   float ev = simpleKalmanFilter.updateEstimate(c);
   val1= map(ev, 0, 1023, -200, 200);
   stepRotation(val1);
   Serial.print(val1);
   Serial.print("\t");
   Serial.print(Gs);
   Serial.print("\t");
   Serial.println(fcount);
 
}
