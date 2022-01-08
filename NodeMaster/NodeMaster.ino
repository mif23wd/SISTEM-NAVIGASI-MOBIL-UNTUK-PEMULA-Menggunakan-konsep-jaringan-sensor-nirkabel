#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(D8, D7); 
DFRobotDFPlayerMini myDFPlayer;
String  value1;
int  value1int;
String  value2;
long  value2int;
String  value3;
int  value3int;
String  value4;
int  value4int;
WiFiServer server(80);

String  httpurl;
String  TheHiddenAnswerOfClient;
HTTPClient http;

String SendWithAnswer(String IPcache, String monmessagecache) {
httpurl = "http://";
httpurl+=IPcache;
httpurl+="/";
httpurl+=monmessagecache;
http.begin(httpurl);
http.GET();
TheHiddenAnswerOfClient = (http.getString());
http.end();
return TheHiddenAnswerOfClient;
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.volume(30);
  myDFPlayer.playMp3Folder(1);
  delay(2000);
  WiFi.disconnect();
  delay(1000);
  WiFi.begin("mif23","qwertyuiop");
  while ((!(WiFi.status() == WL_CONNECTED))){
    Serial.print("..");
    delay(300);
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Connected");
  Serial.println((WiFi.localIP().toString()));
  server.begin();
  myDFPlayer.playMp3Folder(2);
  delay(4500);
  while(SendWithAnswer("192.168.43.111","Yes")==""){
    myDFPlayer.playMp3Folder(3);
    delay(2000);
  }
  myDFPlayer.playMp3Folder(4);
  delay(2500);
  while(SendWithAnswer("192.168.43.112","Yes")==""){
    myDFPlayer.playMp3Folder(5);
    delay(2000);
  }
  myDFPlayer.playMp3Folder(6);
  delay(2500);
  while(SendWithAnswer("192.168.43.113","Yes")==""){
    myDFPlayer.playMp3Folder(7);
    delay(2000);
  }
  myDFPlayer.playMp3Folder(8);
  delay(2500);
  while(SendWithAnswer("192.168.43.114","Yes")==""){
    myDFPlayer.playMp3Folder(9);
    delay(2000);
  }
  myDFPlayer.playMp3Folder(10);
  delay(2500);
  myDFPlayer.playMp3Folder(19);
  delay(3500);
}


void loop()
{
    value1 = (SendWithAnswer("192.168.43.111","Yes"));
    if(value1 == ""){
      Serial.println("");
      Serial.print("Kiri : Terputus");
      myDFPlayer.playMp3Folder(15);
      delay(2500);
    }
    else{
      value1int = value1.toInt();
      if(value1int <= 70){
        myDFPlayer.playMp3Folder(11);
        delay(1500);
        }
      Serial.println("");
      Serial.print("Kiri : ");
      Serial.print(value1int);
    }
    value2 = (SendWithAnswer("192.168.43.112","Yes"));
    if(value2 == ""){
      Serial.println("");
      Serial.print("Kanan : Terputus");
      myDFPlayer.playMp3Folder(16);
      delay(2500);
    }
    else{
      value2int = value2.toInt();
      if(value2int <= 70){
        myDFPlayer.playMp3Folder(12);
        delay(1500);
        }
      Serial.println("");
      Serial.print("Kanan : ");
      Serial.print(value2int);
    }
    value3 = (SendWithAnswer("192.168.43.113","Yes"));
    if(value3 == ""){
      Serial.println("");
      Serial.print("Depan : Terputus");
      myDFPlayer.playMp3Folder(17);
      delay(2500);
    }
    else{
      value3int = value3.toInt();
      if(value3int <= 120){
        myDFPlayer.playMp3Folder(13);
        delay(2500);
        }
      Serial.println("");
      Serial.print("Depan : ");
      Serial.print(value3int);
    }
    value4 = (SendWithAnswer("192.168.43.114","Yes"));
    if(value4 == ""){
      Serial.println("");
      Serial.print("Belakang : Terputus");
      myDFPlayer.playMp3Folder(18);
      delay(2500);
    }
    else{
      value4int = value4.toInt();
      if(value4int <= 120){
        myDFPlayer.playMp3Folder(14);
        delay(3500);
        }
      Serial.println("");
      Serial.print("Belakang : ");
      Serial.print(value4int);
    }

}
