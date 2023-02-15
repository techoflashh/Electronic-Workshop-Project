#include <Servo.h>   //servo library
#include <LiquidCrystal.h>

Servo servo;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int trigPinMain = 10;    
int echoPinMain = 9;   
int servoPin = 8;
int trigPinSec = 12;
int echoPinSec = 11;
int temp;
long duration, dist_to_open, average, dist_to_filled;   
long aver[3];   //array for average



void setup() {       
    Serial.begin(9600);
	lcd.begin(16, 2);
    servo.attach(servoPin);  
    pinMode(trigPinMain, OUTPUT);  
    pinMode(echoPinMain, INPUT);
  pinMode(trigPinSec, OUTPUT);
  pinMode(echoPinSec, INPUT);
    servo.write(0);         //close cap on power on
    delay(100);
    servo.detach(); 
} 

void measure1() {  
 digitalWrite(10,HIGH);
digitalWrite(trigPinMain, LOW);
delayMicroseconds(5);
digitalWrite(trigPinMain, HIGH);
delayMicroseconds(15);
digitalWrite(trigPinMain, LOW);
pinMode(echoPinMain, INPUT);
duration = pulseIn(echoPinMain, HIGH);
dist_to_filled = (duration/2) / 29.1;    //obtain distance
}

void measure2() {  
 digitalWrite(trigPinSec,HIGH);
delayMicroseconds(5);
digitalWrite(trigPinSec, HIGH);
delayMicroseconds(15);
digitalWrite(trigPinSec, LOW);
pinMode(echoPinSec, INPUT);
duration = pulseIn(echoPinSec, HIGH);
dist_to_open = (duration/2) / 29.1;    //obtain distance
}

void loop() { 
  for (int i=0;i<=2;i++) {   //average distance
    measure1();               
   aver[i]=dist_to_filled;            
    delay(10);              //delay between measurements
  }
 dist_to_filled=(aver[0]+aver[1]+aver[2])/3;
  for(int i = 0; i<=2; i++){
    measure2();
    aver[i]=dist_to_open;
    delay(10);
  }
  dist_to_open = (aver[0] +aver[1]+ aver[2])/3;
if ( dist_to_filled<19 ) {
//Change distance as per your need
 lcd.setCursor(0,0);
 lcd.print("  Eco Warriors");
 lcd.setCursor(3,1);
 lcd.print("                ");
 lcd.setCursor(3,1);
 lcd.print((20-dist_to_filled)*5);
 lcd.print("% FILLED");
 Serial.println((20-dist_to_filled)*5);    
}else{
 lcd.setCursor(0,0);
 lcd.print("  Eco Warriors");
  lcd.setCursor(0, 1);
  lcd.print("      Empty     ");
  Serial.println(0);
}

if ( dist_to_open<25 && dist_to_open !=0) {
//Change distance as per your need
 servo.attach(servoPin);
 delay(1);
 servo.write(0);  
 delay(3000);
 servo.write(150);    
 delay(500);
 servo.detach();
}
   else{
     delay(1000);
   }
}