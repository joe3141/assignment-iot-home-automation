#include <Wire.h>

#define SSID "AndroidAP"
#define PASS "vcrz5833"

String message = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

   pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);

  while(Serial.available()>0)
   delay(1000);

   Serial.println("AT");
   if(Serial.find("OK"))
     {
       Serial.println("Module is ready");
     }
     else
     {
       Serial.println("Module have no response.");
     }

     Serial.println("AT+CWMODE=3");
     delay(200);

      if(Serial.find("OK"))
     {
       Serial.println("Mode set");
     }
     else
     {
       Serial.println("Module have no response.");
     }

     
     while(Serial.find("OK") == false)
     {
     String wifi="AT+CWJAP=\"";
     wifi+=SSID;
     wifi+="\",\"";
     wifi+=PASS;
     wifi+="\"";
     Serial.println(wifi);
     //Serial2.println(wifi);
     //delay(15000);
     }
     Serial.println("Connected");

     Serial.println("AT+CIPMUX=1");
     delay(200);
     if(Serial.find("OK"))
     {
       Serial.println("Mode set");
     }
     else
     {
       Serial.println("Module have no response.");
     }

     Serial.println("AT+CIPSERVER=1,80");
     if(Serial.find("OK"))
     {
       Serial.println("Mode set");
     }
     else
     {
       Serial.println("Module have no response.");
     }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) // check if the esp is sending a message 
  {
 
    
    if(Serial.find("+IPD,"))
    {
     delay(1000); // wait for the serial buffer to fill up (read all the serial data)
     // get the connection id so that we can then disconnect
     int connectionId = Serial.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
          
     Serial.find("pin="); // advance cursor to "pin="
     
     int pinNumber = (Serial.read()-48)*10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
     pinNumber += (Serial.read()-48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
     
     digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin 
       
     if(Serial.find("msg=")){
     message = Serial.readStringUntil('\0');
     char buffer1[32];
     message.toCharArray(buffer1, 32);
     Wire.beginTransmission(8);
     Wire.write(buffer1);
     Wire.endTransmission();
     }
     
     // make close command
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
//     closeCommand+="\r\n";
     
//     sendData(closeCommand,1000,DEBUG); // close connection
    Serial.println(closeCommand);
    }
  }
  delay(500);
}


