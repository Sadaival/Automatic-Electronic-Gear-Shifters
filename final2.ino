#include <Servo.h>
#include <Adafruit_TFTLCD.h> 
#include <Adafruit_GFX.h> 


#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4 

#define TS_MINX 163
#define TS_MINY 140
#define TS_MAXX 948
#define TS_MAXY 854

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int posl12 =130;
int posl23 =105;
int posl34 =94;
int posl45 =85;
int posl56 =75;
int posl67 =55;
int posl76 =92;
int posl65 =104;
int posl54 =115;
int posl43 =129;
int posl32 =140;
int posl21 =150;



int posr12 =118;
int posr23 =105;
int posr34 =93;
int posr45 =87;
int posr56 =79;
int posr67 =64;
int posr76 =88;
int posr65 =96;
int posr54 =105;
int posr43 =115;
int posr32 =124;
int posr21 =137;


int ManSpeedMax=20;
int MotorSpeedMax =35;
float l7=10;
float l6=.875*l7;//8.75
float l5=0.7778*l7;
float l4=.7*l7;


float sp1=4;
float sp2=7;
float sp3=9;
float sp4=12;
float sp5=15;
float sp6=18;
float sp7=20;

float sp8=8;
float sp9=11;
float sp10=14;
float sp11=18;
float sp12=21;
float sp13=25;
float sp14=28;



int interruptPin =21;
int sensorValue=0;
volatile byte counter;
volatile byte counter2;
int mode=1;
//float counter;
float rpm;
unsigned int passedtime;
int sp;
unsigned int currentmilli;
float a[8];
int temp=0;

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


boolean buttonEnabled = true;

Servo leftservo; 
Servo rightservo;

int m=1;
int y=0;
int x=0;
int l=45;
int r=46;
int z=1;
int k=1;

int pos = 170; // variable to store the servo position

void setup() {
  leftservo.attach(46);  // attaches the servo on pin 9 to the servo object
  rightservo.attach(45);
  //pinMode( 45, INPUT);
  //pinMode(46,INPUT);
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(2);  
  tft.fillScreen(WHITE);

//a[5]=50;
//a[6]=50;
//a[7]=50;


  attachInterrupt(digitalPinToInterrupt(interruptPin),isr,RISING);
 // attachInterrupt(digitalPinToInterrupt(20),sw,FALLING);
   // attachInterrupt(digitalPinToInterrupt(20),vor,RISING);
   //  attachInterrupt(digitalPinToInterrupt(20),bor,FALLING);
  counter=0;
  rpm=0;
  passedtime=0;
  sp=0;
  currentmilli=0;

  tft.drawRect(0,0,250,320,BLACK);
  
  tft.setCursor(15,100);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print("EVOLUTION");
  
 
  tft.setCursor(80,200);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("IITG");
  delay(2000);
  tft.fillScreen(BLACK);

  tft.setCursor(10,30);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Left Gear");

   tft.setCursor(10,105);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Right Gear");

  tft.fillCircle(215,40, 20, BLUE);
  tft.drawCircle(215,40,20,WHITE);
  tft.setCursor(210,35);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print(z);

  tft.fillCircle(215,115, 20, BLUE);
  tft.drawCircle(215,115,20,WHITE);
  tft.setCursor(210,110);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print(m);

  tft.setCursor(10,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Speed (km/hr)");

  tft.fillRect(75,220, 100, 55, RED);
  tft.drawRect(75,220,100,55,WHITE);
  tft.setCursor(105,237);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print(sp);  





  tft.fillRect(20,280, 200, 35, GREEN);
  tft.setCursor(70,285);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("Manual");

}
 




void loop() {
 //  Serial.print("\n\n");
   //         Serial.print(x);
     //       Serial.print("\n\n");
counter2=digitalRead(20);
   Serial.print("counter is ");
   Serial.println(counter2);
   
   if(counter2==0 && temp==0){

    temp=temp+1;
    invert();
    
    }
    if(counter2==1){

      temp=0;
      
      }


if(mode==0){
  
  tft.fillRect(20,280, 200, 35, GREEN);
  tft.setCursor(70,285);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("Manual");
  Serial.print("Manual");
  
  }

if(mode==1){

  
  tft.fillRect(20,280, 200, 35, GREEN);
  tft.setCursor(50,285);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("Automatic");
  Serial.print("Automatic");
  
  }


      
//delay(3000);

  //if(counter==1){passedtime=millis();}  
  if(counter==0){
    currentmilli=millis();
    if((currentmilli-passedtime)>=3000){
      rpm=0;
      Serial.println(currentmilli-passedtime);
/*
 // if(rpm<50){    
 // a[0]=a[1];
//  a[1]=a[2];
//  a[2]=a[3];
 // a[3]=a[4];
  //a[4]=rpm;
  
//  rpm=(a[0]+a[1]+a[2]+a[3]+a[4])/5.00;
//  }
  
 // if(rpm>=50){
  a[0]=a[1];
  a[1]=a[2];
  a[2]=a[3];
  a[3]=a[4];
  a[4]=a[5];
  a[5]=a[6];
  a[6]=a[7];
  a[7]=rpm;
  
  rpm=(a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7])/8.00;  
    
    }
  Serial.println(counter);
  //Serial.println(counter);
  counter=0;
  */
      delay(500);

  //Serial.print("RPM=");
  //Serial.println(rpm);
  sp=(3.14*0.71*rpm)*1000/(60*60);
  Serial.println(rpm);
  Serial.print("speed=");
  Serial.println(sp);
  Serial.print("\n\n");
  tft.fillRect(75,220, 100, 55, RED);
  tft.drawRect(75,220,100,55,WHITE);
  tft.setCursor(105,237);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print(sp);
      }
  }
  if(counter>=1){
  currentmilli=millis();
  Serial.println(currentmilli);
  Serial.println(passedtime);
  rpm=(12*counter)/((currentmilli-passedtime)/1000.00);
  Serial.println(currentmilli-passedtime);
  passedtime=millis();
   Serial.print("RPM=");
  Serial.println(rpm);
 /*if(rpm<50){    
  a[0]=a[1];
  a[1]=a[2];
  a[2]=a[3];
  a[3]=a[4];
  a[4]=rpm;
  
  rpm=(a[0]+a[1]+a[2]+a[3]+a[4])/5.00;
  }
  
  if(rpm>=50){*/
  a[0]=a[1];
  a[1]=a[2];
  a[2]=a[3];
  a[3]=a[4];
  a[4]=a[5];
  a[5]=a[6];
  a[6]=a[7];
  a[7]=rpm;
  
  rpm=(a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7])/8.00;  
 // }
  Serial.println(counter);
  //Serial.println(counter);
  counter=0;
 // Serial.print("RPM=");
  //Serial.println(rpm);
  //sp=(3.14*0.71*rpm)*(3600/1000);
  sp=(3.14*0.71*rpm*0.06);
  Serial.println(rpm);
  Serial.print("speed=");
  Serial.println(sp);
  Serial.print("\n\n");
  tft.fillRect(75,220, 100, 55, RED);
  tft.drawRect(75,220,100,55,WHITE);
  tft.setCursor(105,237);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print(sp);
  
  }
sensorValue = analogRead(interruptPin);
//Serial.println(sensorValue);
  //}




if(mode==0){


  y = analogRead(15);
  x = analogRead(14);

  
 
if (x>=0 && x<100)
      {
        if (z==1)
          {
          do{z=2;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
    
            pos=posl12;
    
            leftservo.write(pos);
           
            Serial.print(z);
            Serial.print("\n\n");
            Serial.print(x);
            Serial.print("\n\n");
    
           // shiftl12();
            x = analogRead(14);
    
          } while(x<300);
    
    
    }
    
    else if (z==2)
    {
    
      do{z=3;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
    
        pos=posl23;
        
        leftservo.write(pos);
    //                pos=posbl23;
    //        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n"); 
    
        //shiftl23();
        x = analogRead(14);
        } while(x<300);
    
    }
    
    
    else if (z==3)
    
    {
    
      do{z=4;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
      
      pos=posl34;
      
      leftservo.write(pos);
   //               pos=posbl34;
   //         leftservo.write(pos);
      Serial.print(z);
      Serial.print("\n\n");
      Serial.print(x);
      Serial.print("\n\n");
      
     // shiftl34();
      x = analogRead(14); 
      } while(x<300);
    
    }
    
    else if (z==4)
    
    {
    
        do{z=5;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl45;
        leftservo.write(pos); 
   //                 pos=posbl45;
 //           leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");
       // shiftl45();
        x = analogRead(14);
        } while(x<300);
    
    }
    
    else if (z==5)
    
    {
    
        do{z=6;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl56;
        
        leftservo.write(pos);
    //                pos=posbl56;
  //          leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");
        
       // shiftl56();
        x = analogRead(14);
        } 
        while(x<300);
    
    }
    
    else if (z==6)
    
    {
        do{z=7;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl67;
        
        leftservo.write(pos);
        //            pos=posbl67;
  //          leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");
        
     //   shiftl67();
        x = analogRead(14);
        }
        while(x<300);
    
    }
    
 }

if (x>650 && x<1050)

    {
    if (z==7)
    
    {
    
        do{z=6;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl76;
        
        leftservo.write(pos); 
    //                pos=posbl76;
   //         leftservo.write(pos);       
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");
        
      //  shiftl76();
        x = analogRead(14);
        } while(x>700);
    
    }
    
    else  if (z==6)
    
    {
    
        do{z=5;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl65;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");
        
      //  shiftl65();
        x = analogRead(14);
        } while(x>700);
    
    }
    
    else if (z==5)
    {
    
        do{z=4;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl54;
        
        leftservo.write(pos);
       //             pos=posbl54;
    //        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");

        
       // shiftl54();
        x = analogRead(14);
        } while(x>700);
        
    
    }
    
    
    else if (z==4)
    {
    
        do{z=3;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl43;
        
        leftservo.write(pos);
    //                pos=posbl43;
    //        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");
        
       // shiftl43();
        x = analogRead(14);
        } while(x>700);
        
    }
    
    else if (z==3)
    
    {
    
        do{
        z=2;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl32;
        
        leftservo.write(pos);
      //              pos=posbl32;
   //         leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");
      //  shiftl32();
        x = analogRead(14);
        } while(x>700);
    
    }
    
    else if (z==2)
    
    {
    
        do{z=1;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl21;
        
        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");

        
     //   shiftl21();
        x = analogRead(14);
        }while(x>700);
    }
 }














 

  
 
if (y>=0 && y<100)
      {
        if (m==1)
          {
          do{m=2;
    tft.fillCircle(215,115, 20, BLUE);
            tft.drawCircle(215,115,20,WHITE);
            tft.setCursor(210,110);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(m);

    
            pos=posr12;
    
            rightservo.write(pos);
            Serial.print(m);
            Serial.print("\n\n");
            Serial.print(y);
            Serial.print("\n\n");
          //  shiftr12();
            y = analogRead(15);
    
          } while(y<300);
    
    
    }
    
    else if (m==2)
    {
    
      do{m=3;
              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);

    
        pos=posr23;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n"); 
    
     //   shiftr23();
        y = analogRead(15);
        } while(y<300);
    
    }
    
    
    else if (m==3)
    
    {
    
      do{
      m=4;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
      
      pos=posr34;
      
      rightservo.write(pos);
      Serial.print(z);
      Serial.print("\n\n");
      Serial.print(y);
      Serial.print("\n\n");
     // shiftr34();
      y = analogRead(15); 
      } while(y<300);
    
    }
    
    else if (m==4)
    
    {
    
        do{
        m=5;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr45;
        rightservo.write(pos); 
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");
       // shiftr45();
        y = analogRead(15);
        } while(y<300);
    
    }
    
    else if (m==5)
    
    {
    
        do{m=6;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr56;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");
        
      //  shiftr56();
        y = analogRead(15);
        } 
        while(y<300);
    
    }
    
    else if (m==6)
    
    {
        do{m=7;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr67;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");

        
     //   shiftr67();
        y = analogRead(15);
        }
        while(y<300);
    
    }
    
 }

if (y>650 && y<1050)

    {
    if (m==7)
    
    {
    
        do{
        m=6;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr76;
        
        rightservo.write(pos);        
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");
      //  shiftr76();
        y = analogRead(15);
        } while(y>600);
    
    }
    
    else  if (m==6)
    
    {
    
        do{ m=5;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
              
        pos=posr65;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");
        
      //  shiftr65();
        y = analogRead(15);
        } while(y>700);
    
    }
    
    else if (m==5)
    {
    
        do{m=4;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr54;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");
       
      //  shiftr54();
        y = analogRead(15);
        } while(y>700);
        
    
    }
    
    
    else if (m==4)
    {
    
        do{ m=3;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr43;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");
        
       // shiftr43();
        y = analogRead(15);
        } while(y>700);
        
    }
    
    else if (m==3)
    
    {
    
        do{ m=2;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr32;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");
        
      //  shiftr32();
        y = analogRead(15);
        } while(y>700);
    
    }
    
    else if (m==2)
    
    {
    
        do{ m=1;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr21;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");

        
       // shiftr21();
        y = analogRead(15);
        }while(y>7000);
    }
 }
}






else if(mode==1){
  
 if(sp<sp1){
  z=1;
  tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl21;
        
        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");

  } 
  else if(sp>=sp1 && sp<sp2){
  
  if(z<2){tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl12;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
  if(z>2){ tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl32;
        
        leftservo.write(pos);
      //              pos=posbl32;
   //         leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
        z=2;
  } 
 else if(sp>=sp2 && sp<sp3){
  
  if(z<3){tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl23;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
  if(z>3){tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl43;
        
        leftservo.write(pos);
    //                pos=posbl43;
    //        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");
        }
        z=3;
  } 
  else if(sp>=sp3 && sp<sp4){
  
  if(z<4){tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl34;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
  if(z>4){tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl54;
        
        leftservo.write(pos);
       //             pos=posbl54;
    //        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
        z=4;
  } 
 else  if(sp>=sp4 && sp<sp5){
  
  if(z<5){tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl45;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
  if(z>5){tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl65;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
        z=5;
  } 
 else if(sp>=sp5 && sp<sp6){
  
  if(z<6){tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl56;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
  if(z>6){tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl76;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
        z=6;
  } 
  else if(sp>=sp6 && sp<sp7){
  z=7;
  tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl67;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");
  } 
  






  





 if(sp<sp8){
  m=1;
   tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr21;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");

  } 
  else if(sp>=sp8 && sp<sp9){
  
  if(m<2){tft.fillCircle(215,115, 20, BLUE);
            tft.drawCircle(215,115,20,WHITE);
            tft.setCursor(210,110);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(m);

    
            pos=posr12;
    
            rightservo.write(pos);
            Serial.print(m);
            Serial.print("\n\n");
            Serial.print(y);
            Serial.print("\n\n");}
  if(m>2){tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr32;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
        m=2;
        }
   
 else if(sp>=sp9 && sp<sp10){
  
  if(m<3){tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);

    
        pos=posr23;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n"); }
  if(m>3){tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr43;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
        m=3;
  } 
  else if(sp>=sp10 && sp<sp11){
  
  if(m<4){tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
      
      pos=posr34;
      
      rightservo.write(pos);
      Serial.print(z);
      Serial.print("\n\n");
      Serial.print(y);
      Serial.print("\n\n");}
  if(m>4){tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr54;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
        m=4;
  } 
 else  if(sp>=sp11 && sp<sp12){
  
  if(m<5){tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr45;
        rightservo.write(pos); 
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
  if(m>5){tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
              
        pos=posr65;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
        m=5;
  } 
 else if(sp>=sp12 && sp<sp13){
  
  if(m<6){tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr56;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
  if(m>6){ tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr76;
        
        rightservo.write(pos);        
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
        m=6;
  } 
  else if(sp>=sp13 && sp<sp14){
  m=7;
  tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr67;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");
  }  
  
  
  
  
  //code for automatic
  












  
  }
//delay(200);

}














void isr(){
  counter++;
  Serial.println(counter);
  }



void invert(){
  if(mode==0){
    mode=1;
   // Serial.print("Automatic");
    }
  else if(mode==1){

    mode=0;
  //  Serial.print("Manual");
    
    }
  
  }




/*
  void shiftr12(){m=2;
            tft.fillCircle(215,115, 20, BLUE);
            tft.drawCircle(215,115,20,WHITE);
            tft.setCursor(210,110);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(m);

    
            pos=posr12;
    
            rightservo.write(pos);
            Serial.print(m);
            Serial.print("\n\n");
            Serial.print(y);
            Serial.print("\n\n");}
void shiftr23(){m=3;
              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);

    
        pos=posr23;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n"); }
void shiftr34(){m=4;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
      
      pos=posr34;
      
      rightservo.write(pos);
      Serial.print(z);
      Serial.print("\n\n");
      Serial.print(y);
      Serial.print("\n\n");}
void shiftr45(){m=5;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr45;
        rightservo.write(pos); 
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
void shiftr56(){m=6;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr56;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
void shiftr67(){m=7;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr67;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}


void shiftr76(){m=6;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr76;
        
        rightservo.write(pos);        
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
void shiftr65(){m=5;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
              
        pos=posr65;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
void shiftr54(){m=4;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr54;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
void shiftr43(){ m=3;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr43;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}
void shiftr32(){ m=2;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr32;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}

        
void shiftr21(){ m=1;

              tft.fillCircle(215,115, 20, BLUE);
              tft.drawCircle(215,115,20,WHITE);
              tft.setCursor(210,110);
              tft.setTextColor(WHITE);
              tft.setTextSize(2);
              tft.print(m);
        
        pos=posr21;
        
        rightservo.write(pos);
        Serial.print(m);
        Serial.print("\n\n");
        Serial.print(y);
        Serial.print("\n\n");}







void shiftl12{z=2;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
    
            pos=posl12;
    
            leftservo.write(pos);
           
            Serial.print(z);
            Serial.print("\n\n");
            Serial.print(x);
            Serial.print("\n\n");}
void shiftl23{z=3;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
    
        pos=posl23;
        
        leftservo.write(pos);
    //                pos=posbl23;
    //        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n"); }
void shiftl34{z=4;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
      
      pos=posl34;
      
      leftservo.write(pos);
   //               pos=posbl34;
   //         leftservo.write(pos);
      Serial.print(z);
      Serial.print("\n\n");
      Serial.print(x);
      Serial.print("\n\n");}
void shiftl45{z=5;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl45;
        leftservo.write(pos); 
   //                 pos=posbl45;
 //           leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
void shiftl56{z=6;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl56;
        
        leftservo.write(pos);
    //                pos=posbl56;
  //          leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
void shiftl67{z=7;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl67;
        
        leftservo.write(pos);
        //            pos=posbl67;
  //          leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}


void shiftl76{z=6;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl76;
        
        leftservo.write(pos); 
    //                pos=posbl76;
   //         leftservo.write(pos);       
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
void shiftl65{z=5;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl65;
        leftservo.write(pos);
      //              pos=posbl65;
     //       leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
void shiftl54{z=4;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl54;
        
        leftservo.write(pos);
       //             pos=posbl54;
    //        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
void shiftl43{z=3;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl43;
        
        leftservo.write(pos);
    //                pos=posbl43;
    //        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
void shiftl32{z=2;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl32;
        
        leftservo.write(pos);
      //              pos=posbl32;
   //         leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}
void shiftl21{z=1;
            tft.fillCircle(215,40, 20, BLUE);
            tft.drawCircle(215,40,20,WHITE);
            tft.setCursor(210,35);
            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.print(z);
        
        pos=posl21;
        
        leftservo.write(pos);
        Serial.print(z);
        Serial.print("\n\n");
        Serial.print(x);
        Serial.print("\n\n");}


*/
