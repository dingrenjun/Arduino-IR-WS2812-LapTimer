#include <MsTimer2.h>
#include <EEPROM.h>
#include <IRremote.h>   //启用红外库
#include <SCoop.h>
#include <Adafruit_NeoPixel.h>
IRsend irsend;         //定义 IRsend 物件来发射信号
int led4=11;
int led5=12;
int buttonPin=16;
int ledState=1,ledState1=1,ledState2=1,ledState3=1;// 记录当前按键的状态
unsigned long int key_cnt;
int bs1,bs2,bs3,mz,val2,a1=1,a2,a3,a4,mz1;
int address = 0;
int address1 = 1;
int address2 = 2;
int address3 = 3;
String indate="";
String val="";
#define PIXEL_COUNT 8  //灯珠的数量
#define PIXEL_PIN   15   //定义 PIN6 接LED
unsigned long int  i;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

defineTaskLoop(TaskTest1)
{ 
 //    Serial.println("0xA10"); 
     irsend.sendSony(mz, 32); // Sony TV power code
         delay(20);
if(digitalRead(buttonPin)==LOW) //盘点是否按下按键
   {      
         delay(10); 
 if(digitalRead(buttonPin)==LOW)
   {    
   while(digitalRead(buttonPin)==LOW)
        {  key_cnt++; }
   while(!digitalRead(buttonPin));    
           bs1=1;a3=1;
    if(key_cnt>200000)
      {   ledState++; 
          key_cnt=0;
     if(ledState==1||ledState==3)
     {
       Serial.println("简单模式-按键控制");
       Serial.println("编号取值(1-9)");
      }
  else if(ledState==2)
      {    Serial.println("竞赛模式-串口控制");
        Serial.println(mz1,HEX);
      Serial.println("编号取值(1-256)");
      Serial.println("LED颜色（Black、Red、Green、Blue、White、Yellow、Purple、DeepPink、DarkPrange）");
      }
       }
  else if(ledState==1)  ledState1++;
       if(ledState==3) ledState=1;
       if(ledState1==10) ledState1=1;
    EEPROM.write(address,ledState);
    EEPROM.write(address1,ledState1);
    if(key_cnt<200000)    key_cnt=0;
  }
}
    delay(5); 
}

void  setup()
{
  Serial.begin(9600);
  pinMode(led4, OUTPUT);//定义红色灯接口为输出接口
  pinMode(led5, OUTPUT);//定义红色灯接口为输出接口 
  pinMode(buttonPin,INPUT_PULLUP); //使用内部上拉
  strip.begin();
  strip.show();   
  mySCoop.start();
}

void sp()
{        
  switch (ledState1) {
            case 1:      mz=0xC11;
            if(bs1==1){  Serial.print("ID:1 ,LED颜色：Black");bs1=0;
                         Serial.print(" ,识别码:");       
                         Serial.println(mz,HEX); 
                      }        
                       colorWipe(strip.Color(0, 0, 0), 50);  // Black/off            
            break;           
            case 2:    mz=0xC12; 
           if(bs1==1){ Serial.print("ID:2 ,LED颜色：Red");bs1=0; 
                       Serial.print(" ,识别码:");       
                       Serial.println(mz,HEX);     
                      }        
                      colorWipe(strip.Color(255, 0, 0), 50);  // Red              
           break;                    
           case 3:     mz=0xC13;
           if(bs1==1){ Serial.print("ID:3 ,LED颜色：Green");bs1=0;
                       Serial.print(" ,识别码:");       
                       Serial.println(mz,HEX);     
                     }   
                      colorWipe(strip.Color(0, 255, 0), 50);  // Green 
            break;          
           case 4:      mz=0xC14;
           if(bs1==1) { Serial.print("ID:4 ,LED颜色：Blue");bs1=0;
                        Serial.print(" ,识别码:");       
                        Serial.println(mz,HEX);     
                       }          
                       colorWipe(strip.Color(0, 0, 255), 50);  // Blue   
            break;           
            case 5:      mz=0xC15;  
           if(bs1==1){   Serial.print("ID:5 ,LED颜色：White");bs1=0;
                         Serial.print(" ,识别码:");       
                         Serial.println(mz,HEX);     
                     }            
                       colorWipe(strip.Color(255,250,250), 50); // White    
           break;                    
           case 6:        mz=0xC16;
            if(bs1==1){   Serial.print("ID:6 ,LED颜色：Yellow");bs1=0;
                          Serial.print(" ,识别码:");       
                          Serial.println(mz,HEX);     
                           }      
                      colorWipe(strip.Color(255,255,0), 50); // Yellow
            break;          
              case 7:     mz=0xC17;
            if(bs1==1) { Serial.print("ID:7 ,LED颜色：Purple");bs1=0;
                         Serial.print(" ,识别码:");       
                         Serial.println(mz,HEX);     
                       }        
                       colorWipe(strip.Color(128,0,128), 50); // Purple
            break;           
            case 8:       mz=0xC18;   
            if(bs1==1){   Serial.print("ID:8,LED颜色：DeepPink");bs1=0;
                          Serial.print(" ,识别码:");       
                          Serial.println(mz,HEX);     
                      }  
                      colorWipe(strip.Color(255,20,147), 50); // DeepPink
           break;                    
           case 9:       mz=0xC19;
             if(bs1==1){ Serial.print("ID:9 ,LED颜色：DarkPrange");bs1=0;
                         Serial.print(" ,识别码:");       
                         Serial.println(mz,HEX);     
                       }         
                   colorWipe(strip.Color(255,140,07), 50); // DarkPrange
           break;  
           default:          
           break;     
  }   

      
}
void racing()
{
    switch (ledState3) {
        case 1:    mz=0xa10;     break;
        case 2:    mz=0xB10;     break;
        case 3:    mz=0xC10;     break;
        case 4:    mz=0xD10;     break;
        case 5:    mz=0xE10;     break;
        case 6:    mz=0x110;     break;
        case 7:    mz=0x210;     break;
        case 8:    mz=0x310;     break;
        case 9:    mz=0x410;     break;
        default:  
        break;
  }    
      if(a4!=ledState3)
     EEPROM.write(address3, ledState3);  
         a4=ledState3;
     switch(ledState2)
          {
        case 1:    colorWipe(strip.Color(0, 0, 0), 50);  //Black                 
        break;
        case 2:   colorWipe(strip.Color(255, 0, 0), 50);  // Red                     
        break;
        case 3:   colorWipe(strip.Color(0, 255, 0), 50);  // Green                     
        break;
        case 4:   colorWipe(strip.Color(0, 0, 255), 50);  // Blue   
        break;       
        case 5:  colorWipe(strip.Color(255,250,250), 50); // White                   
        break;
        case 6:    colorWipe(strip.Color(255,255,0), 50); // Yellow                   
        break;
        case 7:    colorWipe(strip.Color(128,0,128), 50); // Purple                   
        break;
        case 8:     colorWipe(strip.Color(255,20,147), 50); // DeepPink               
        break;      
        case 9:    colorWipe(strip.Color(255,140,07), 50); // DarkPrange                
        break;      
        default:  
        break;
          }  
        if(bs3==1&&val2>0&&val2<=256)
        {
       Serial.print("设置成功，ID:");
       Serial.print(ledState3);  
       Serial.print(" ,识别码:");       
       Serial.println(mz,HEX);     
        bs3=0;
        }   
         if(val=="Black")
       {
      if(bs1==1) { EEPROM.write(address2, 1);   Serial.println("设置成功，LED颜色：Black ");bs1=0;}
        } 
   else  if(val=="R")
       {
         
         if(bs1==1){  EEPROM.write(address2, 2);   Serial.println("设置成功，LED颜色：Red");bs1=0;}
        }
   else if(val=="G")
       {  
         if(bs1==1){  EEPROM.write(address2, 3);  Serial.println("设置成功，LED颜色：Green");bs1=0;}
        } 
  else if(val=="B")
       {
         if(bs1==1){ EEPROM.write(address2, 4);  Serial.println("设置成功，LED颜色:Blue");bs1=0;}
       }   
   else  if(val=="W")
       {
           
         if(bs1==1) { EEPROM.write(address2, 5); Serial.println("设置成功，LED颜色：Black");bs1=0;}
        } 
 else  if(val=="Y")
       { 
         if(bs1==1){  EEPROM.write(address2, 6);  Serial.println("设置成功，LED颜色：Yellow");bs1=0;}
        }
 else if(val=="P")
       { 
           
         if(bs1==1){  EEPROM.write(address2, 7);Serial.println("设置成功，LED颜色：Purple");bs1=0;}
        } 
  else if(val=="D")
       {
         if(bs1==1){EEPROM.write(address2, 8); Serial.println("设置成功，LED颜色:DeepPink");bs1=0;}  
       }   
    else if(val=="Da")
       {
        if(bs1==1){ EEPROM.write(address2, 9);Serial.println("设置成功，LED颜色:DaGrkPrange");bs1=0;}   
       }
}
void loop()
{   
ledState = EEPROM.read(address);
ledState1=EEPROM.read(address1);
ledState2=EEPROM.read(address2);
ledState3=EEPROM.read(address3);
if(a1==1)
{
    a1=0;
  if(ledState==1||ledState==3)
  {     Serial.println("简单模式-按键控制");
       Serial.println("编号取值(1-9)");
   }
  else if(ledState==2)
  {    Serial.println("竞赛模式-串口控制");
      Serial.println("编号取值(1-256)");
      Serial.println("LED颜色（Black、Red、Green、Blue、White、Yellow、Purple、DeepPink、DarkPrange）");
  }
}

while(Serial.available()>0)
{
  indate+=char(Serial.read());
  delay(2);
  if(Serial.available()<=0)
{
  Serial.println(indate);
}
}    //读取电脑传来的数据 
 if(indate.length()>0)
  {
         val=indate;  bs1=1;a2=1;bs3=1;
           if(ledState==2)
      {   val2=val.toInt();     
      if(val2>0&&val2<=256)
         ledState3=val2;
      if(val!="sp"&&val!="racing"&&val!="Black"&&val!="R"&&val!="G"&&val!="B"&&val!="W"&&val!="Y"&&val!="P"&&val!="D"&&val!="Da"&&(val2<1||val2>256))
         Serial.println("输入错误");
      }
      if(ledState==1&&val!="racing"&&val!="sp")
        Serial.println("简单模式请使用按键控制");
     if(val=="sp")        //Simple mode
     { 
       EEPROM.write(address, 1);
      Serial.println("简单模式-按键控制");
      Serial.println("编号取值(1-9)");
     }
     if(val=="racing")       //Racing
     { 
        EEPROM.write(address, 2);
        Serial.println("竞赛模式-串口控制");
        Serial.println("编号取值(1-256)");
        Serial.println("LED颜色（Black、Red、Green、Blue、White、Yellow、Purple、DeepPink、DarkPrange）");
      } 
    
  }
   
switch (ledState) {
    case 1:
    sp();
   digitalWrite(led4, LOW);//点亮灯
   digitalWrite(led5, HIGH);
  
    break;

    case 2:
    racing();
    digitalWrite(led4, HIGH);//点亮灯
    digitalWrite(led5, LOW); //熄灭灯
     break;
     default:          
     break; 
  }  
    indate="";   //清空indate为下一次输入做准备  
   delay(10); 
}
//用一种颜色填充点
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
   // delay(1000);
}
}
