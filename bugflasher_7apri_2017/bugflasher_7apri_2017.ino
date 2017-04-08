#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <SimpleDHT.h>
#include <Wire.h>

const int RedLED=7 ;
const int YellowLED=8;
const int GreenLED=9;
WiFiClient client;

 const char* host = "indahomeiot.appspot.com";
  const int httpPort = 80;
  
void setup() {
  Serial.begin(115200);
  delay(10);
   Serial.println("setup started");

   pinMode(RedLED,OUTPUT) ;
   pinMode(YellowLED,OUTPUT) ;
   pinMode(GreenLED,OUTPUT) ;

   
   
   WiFiManager wifiManager;

 // wifiManager.startConfigPortal("FanRelayAP");
   wifiManager.autoConnect("SensorAP");
  Serial.println("It is working");

}

void loop() {
 // delay(5000);

sendLED("1");
 
   
  delay(30000);


}


void sendLED(String deviceId)
{
 
   String url="/device/LED/getdata/"+deviceId;
   Serial.println("url for sendtemperature = "+url); 

    if (client.connect(host, httpPort)) {
    Serial.println("connection happened");
     Serial.print("Requesting URL for sending temp: ");
     Serial.println(url);

      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");
               
     unsigned long timeout = millis();
     while (client.available() == 0) {
    if (millis() - timeout > 10000) {
      Serial.println(">>> Client Timeout !");
    }
  }


      String line ;
      while(client.available()){
       line = client.readStringUntil('\r');
      Serial.print(line);

      }

      if (line.indexOf("red") >=0)
{
 Serial.println("red"); 
 LightLed("red");
}

if (line.indexOf("yellow") >=0)
{
  LightLed("yellow");
  Serial.println("yellow"); 
}



if (line.indexOf("green") >=0)
{
  LightLed("green");
  Serial.println("green"); 
}


    }
  else
  {
    Serial.println("connection failed");
  }
  Serial.println("stopping client");
  client.stop();



}

void LightLed(String color)
{
  if(color.equals("red"))
  {
     digitalWrite(RedLED,HIGH) ;
     digitalWrite(YellowLED,LOW) ;
     digitalWrite(GreenLED,LOW) ;
  }

  if(color.equals("yellow"))
  {
     digitalWrite(RedLED,LOW) ;
     digitalWrite(YellowLED,HIGH) ;
     digitalWrite(GreenLED,LOW) ;
  }

  if(color.equals("green"))
  {
     digitalWrite(RedLED,LOW) ;
     digitalWrite(YellowLED,LOW) ;
     digitalWrite(GreenLED,HIGH) ;
  }
    
}









