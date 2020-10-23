#include<Servo.h>
Servo one;
Servo two;

#define TL A2
#define TR A0
#define BR A1
#define BL A3
//bottom left is taken as avg 
#define TR_ERROR 0
#define TL_ERROR 0
#define BR_ERROR 0

int pos1=90,pos2=90;
int threshold = 30;
int tr,tl,br,bl,dx,dy;

void setup() 
{
    Serial.begin(9600);
    one.attach(10);
    two.attach(9);
    pinMode(TR,INPUT);
    pinMode(BR,INPUT);
    pinMode(TL,INPUT);
    pinMode(BL,INPUT);
    two.write(pos1);
    one.write(pos2);
}

void loop() 
{
    refresh();
    while(abs(dx) > threshold)
    {
      disp();
      if(pos1<10||pos1>180)
      {
          pos1 = pos1 <10?10:180;
          break;
      }
        if(dx < 0)
          one.write(--pos1);
        else
          one.write(++pos1);
        delay(20);
        refresh();
    }
    while(abs(dy) > threshold)
    {
      disp();
      if(pos2<10||pos2>180)
      {
          pos2 = pos2<10?10:180;
          two.write(pos2);
          break;
      }
      if(dy < 0)
         two.write(++pos2);
      else
         two.write(--pos2);
       delay(20);
       refresh();
    }
    disp();    
}
void disp()
{
    // printing sensor data
    Serial.print("0 1024 ");
    Serial.print(tr);
    Serial.print(" ");
    Serial.print(tl);
    Serial.print(" ");
    Serial.print(br);
    Serial.print(" ");
    Serial.println(bl);
}
void refresh()
{
     
    tr = analogRead(TR)+TR_ERROR;
    tl = analogRead(TL)+TL_ERROR;
    br = analogRead(BR)+BR_ERROR;
    bl = analogRead(BL);
    dx = (tr-tl + br-bl)/2;// avg of sensors in x axis
    dy = (tl-bl + tr-br)/2;// avg of sensors in y axis
}
