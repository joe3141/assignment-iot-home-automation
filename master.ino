//#include <PS2Keyboard.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Servo.h>

#define DOORINPUT 12
#define DOOROUTPUT 10
//#define DataPin 2
//#define IRQpin 3


int keybIndex = 0, doorPos = 0;
String keybMessage = "", onlineMessage = "";
//PS2Keyboard keyboard;
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
Servo door;

void setup() {
  
  digitalWrite(DOORINPUT, LOW);
    

  door.attach(DOOROUTPUT);
  
  // LCD init
  lcd.begin(16, 2); //16 columns and 2 rows
  lcd.print("hello, world!");
  delay(1000);

  // Keyboard init
//  keyboard.begin(DataPin, IRQpin);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  
  if(digitalRead(DOORINPUT)){
    lcd.setCursor(0, 0);
    lcd.print("Please wait...");
    doorEvent();
    lcd.setCursor(0, 0);
    lcd.print("Ready!"); 
  }
  
  lcd.setCursor(0, 0);
  lcd.print(onlineMessage);

//  if(keyboard.available())
//    keybEvent();

  delay(100);
}

void doorEvent(){
  
   // OPEN DOOR
   for (doorPos = 0; doorPos <= 180; doorPos += 1) {
    // in steps of 1 degree
    door.write(doorPos);
    delay(15);  
  }
  
  delay(5000);

  // CLOSE DOOR
  for (doorPos = 180; doorPos >= 0; doorPos -= 1) {
    door.write(doorPos);
    delay(15);
  }
  doorPos = 0;
}

//void keybEvent(){
//
//  char c = keyboard.read();
//  keybMessage += c;
//  lcd.setCursor(i, 1);
//  lcd.print(c);
//  i = (i + 1) % 15;
//
//  if (c == PS2_ENTER) {
//    lcd.setCursor(0, 1);
//    lcd.print("                ");
//    sendMessage();
//    keybMessage="";
//    i = 0;
//    // handle sending to internet
//  }
//}

void sendMessage(){

}

void receiveEvent(int howMany){
  onlineMessage = "";
   while(1 < Wire.available()){
   char c = Wire.read();
    onlineMessage += c;
  }
  Wire.read();
  delay(1000);
}
