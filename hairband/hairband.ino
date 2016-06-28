#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define RING_PIN 3
#define CURVE_PIN 6
#define BRIGHT 40

Adafruit_NeoPixel Ring = Adafruit_NeoPixel(24, RING_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Curve = Adafruit_NeoPixel(15, CURVE_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial1.begin(9600);

  while (!(Serial1.available() && Serial1.read() == 'a'));
  
  Ring.begin();
  Ring.setBrightness(BRIGHT);
  Ring.show();
  
  Curve.begin();
  Curve.setBrightness(BRIGHT);
  Curve.show();
}

void loop() {
   Clear();
   for(int y=0;y<2;y++)
   {BothBlue();
    BothOff();
   }
   
  for(int x=0;x<10;x++)
   {CurveBlue();
    RingBlue();
      delay(500);
    CurveOff();
    RingOff();
      delay(500);} 
    
  WhiteAndBlue(50);
}

void RingBlue()
{for(int i=0; i<24;i++){
    Ring.setPixelColor(i,Ring.Color(0,0,70));
    Ring.show();
  }
}
void RingOff()
{for(int i=0; i<24;i++){
    Ring.setPixelColor(i,Ring.Color(0,0,0));
    Ring.show();
  }
}
void CurveBlue()
{ for(int i=0; i<15;i++){
    Curve.setPixelColor(i,Curve.Color(0,0,70));
    Curve.show();
 }
}
void CurveOff()//turn all LED of the Curve Off
{ for(int i=0; i<15;i++){
    Curve.setPixelColor(i,Curve.Color(0,0,0));
    Curve.show();
 }
}
void BothBlue()//Make Both LED blue in order
{ for(int i=0; i<24;i++){
    if(i<15)
    { Ring.setPixelColor(i,Ring.Color(0,0,70));
      Curve.setPixelColor(i,Curve.Color(0,0,70));
      Curve.show();
      Ring.show();
    }
    else
    { Ring.setPixelColor(i,Ring.Color(0,0,70));
      Ring.show();
    }
    delay(250);
  }  
}
void BothOff()//turn off the Both LED in backward order
{ for(int i=23; i>=0;i--){
    if(i>15)
    { Ring.setPixelColor(i,Ring.Color(0,0,0));
      Ring.show();
    }
    else
    { 
      Ring.setPixelColor(i,Ring.Color(0,0,0));
      Curve.setPixelColor(i,Curve.Color(0,0,0));
      Curve.show();
      Ring.show();
    }
    delay(250);
  }  
}
void WhiteAndBlue(int num)//flashes White and Blue
{ for(int x=0; x<=num;x++)
    { if(x%2==0)//if even times
         {for(int r=0; r<24;r++)
          { if(r%2==0)//when it's even
              Ring.setPixelColor(r,Ring.Color(70,70,70));
            else
              Ring.setPixelColor(r,Ring.Color(0,0,70));}
          for(int c=0;c<15;c++)
          {  if(c%2==0)
              Curve.setPixelColor(c,Curve.Color(70,70,70));
             else
              Curve.setPixelColor(c,Curve.Color(0,0,70));}   
         }
      else  
        {for(int r=0; r<24;r++)
          { if(r%2==1)//when it's even
              Ring.setPixelColor(r,Ring.Color(70,70,70));
            else
              Ring.setPixelColor(r,Ring.Color(0,0,70));}
          for(int c=0;c<15;c++)
          {  if(c%2==1)
              Curve.setPixelColor(c,Curve.Color(70,70,70));
             else
              Curve.setPixelColor(c,Curve.Color(0,0,70));}   
         }
        Ring.show();
        Curve.show();
        delay(500);
     }
}
void Clear()
{
  for(int r=0; r<24; r++)
  {Ring.setPixelColor(r,Ring.Color(0,0,0));}
   Ring.show();
 for(int c=0; c<24;c++)
  {Curve.setPixelColor(c,Curve.Color(0,0,0));}
   Curve.show();
}
   

  
        

