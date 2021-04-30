#include <Wire.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <EEPROM.h>


String name1="Rohim";
String name2="Korim";
String name3="Saju";
String name4="JJjk";



#define b1 9
#define b2 10
#define b3 11
#define b4 12
#define buz 13

void dis(String s,String t);

SoftwareSerial mySerial(3, 4);

int a=0,b=0,c=0,d=0,ii=0;
int voted[100]={9};

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int fingerprintID = 0;
String IDname;



void setup() {
  if(EEPROM.read(1)>254)
    EEPROM.write(1,0);

  if(EEPROM.read(2)>254)
    EEPROM.write(2,0);
    
  if(EEPROM.read(3)>254)
    EEPROM.write(3,0);
    
  if(EEPROM.read(4)>254)
    EEPROM.write(4,0);


  pinMode(b1,INPUT_PULLUP);
  pinMode(b2,INPUT_PULLUP);
  pinMode(b3,INPUT_PULLUP);
  pinMode(b4,INPUT_PULLUP);

  
  Serial.begin(9600);
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } 
  else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
  
  Wire.begin();
  lcd.init();
  lcd.backlight();lcd.backlight();
  dis("Place your","finger");
  

}

int w=0,x=0,y=0,z=0;
int ID=0;

void loop() {



  
    int in=getFingerprintIDez();
    for(int i=0;i<ii;i++){
      if(voted[i]==in){
        dis("Error!","Duplicate vote!");
        delay(500);
        return;
        }
      
    }
  
ID=in;
    if(in==1){
       dis("Hi!",name1);
       delay(1000);
       dis("1. W  2. X","3. Y  4. Z");
       for(;!checkBtn();){
       // dis("1. W  2. X","3. Y  4. Z");
       }
       
      
    }else if(in==2){
       dis("Hi!",name2);
       delay(1000);
        dis("1. W  2. X","3. Y  4. Z");

       for(;!checkBtn(););
    }

    else if(in==3){
       dis("Hi!",name3);
       delay(1000);
        dis("1. W  2. X","3. Y  4. Z");

       for(;!checkBtn(););
    }


    else if(in==4){
       dis("Hi!",name4);
       delay(1000);
        dis("1. W  2. X","3. Y  4. Z");

       for(;!checkBtn(););
    }
    
  
    




}













int checkBtn(){

int suc=0;
  
  if(!digitalRead(b1) || !digitalRead(b2) || !digitalRead(b3) ||  !digitalRead(b4))
  {
    w=!digitalRead(b1);
    x=!digitalRead(b2);
    y=!digitalRead(b3);
    z=!digitalRead(b4);
    
    for(;!digitalRead(b1) || !digitalRead(b2) || !digitalRead(b3) || !digitalRead(b4);){
      digitalWrite(buz,1);
    }digitalWrite(buz,0);

    dis("Enter again","");

    for(;digitalRead(b1) && digitalRead(b2) && digitalRead(b3) && digitalRead(b4);){

        if(digitalRead(b1)==0 && w==1){
          digitalWrite(buz,1);
          delay(50);
          digitalWrite(buz,0);
          suc=1;
            Serial.print("W=");
            Serial.println(++a);
             voted[ii++]=ID;
            dis("Congratulations!","Vote saved to W");break;
            
           
        }
        
        else if(digitalRead(b2)==0 && x==1){
          digitalWrite(buz,1);
          delay(50);
          digitalWrite(buz,0);
          suc=1;
            Serial.print("X=");
            Serial.println(++b);
             voted[ii++]=ID;
            dis("Congratulations!","Vote saved to X");break;
        }
          
        else if(digitalRead(b3)==0 && y==1){
          digitalWrite(buz,1);
          delay(50);
          digitalWrite(buz,0);
          suc=1;
            Serial.print("Y=");
            Serial.println(++c);
             voted[ii++]=ID;
            dis("Congratulations!","Vote saved to Y");break;
        }
          
        else if(digitalRead(b4)==0 && z==1){
         digitalWrite(buz,1);
          delay(50);
          digitalWrite(buz,0);
          suc=1;
            Serial.print("Z=");
            Serial.println(++d);
             voted[ii++]=ID;
            dis("Congratulations!","Vote saved to Z");break;
        }
   
      //  else Serial.println("Error!");  
        
        
      
    }
    
    
  }

  
     for(;!digitalRead(b1) || !digitalRead(b2) || !digitalRead(b3) || !digitalRead(b4););

  return suc;
}















int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return 999;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return 999;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return 999;
  
  // found a match!
  //Serial.print("Found ID #"); 
  //Serial.print(finger.fingerID); 
  //Serial.print(" with confidence of "); 
 // Serial.println(finger.confidence);
  return finger.fingerID; 
}



void dis(String s,String t){
  lcd.clear();
  delay(500);
  lcd.setCursor(1,0);// 2nd column,1st row
  lcd.print(s);
  lcd.setCursor(0,1);// 1st column,2nd row
  lcd.print(t);
}
