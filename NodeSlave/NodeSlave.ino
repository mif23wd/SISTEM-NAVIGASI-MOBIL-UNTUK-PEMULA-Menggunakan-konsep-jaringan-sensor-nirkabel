#include <ESP8266WiFi.h>
#define echoPin D7 // Echo Pin
#define trigPin D6 // Trigger Pin
long duration, distance;
IPAddress staticIP171_129(192,168,43,114); //ganti 3 digit terakhir ip untuk node slave lain
IPAddress gateway171_129(192,168,43,1);
IPAddress subnet171_129(255,255,255,0);

WiFiServer server(80);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  WiFi.disconnect();
  WiFi.config(staticIP171_129, gateway171_129, subnet171_129);
  delay(3000);
   WiFi.begin("mif23","qwertyuiop");
  while ((!(WiFi.status() == WL_CONNECTED))){
    Serial.print("..");
    delay(300);

  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Connected");
  Serial.println((WiFi.localIP().toString()));
  Serial.println((WiFi.gatewayIP().toString().c_str()));
  Serial.println((WiFi.subnetMask().toString().c_str()));
  server.begin();

}


void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration/58.2;
    Serial.println(distance);
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println(distance);
    client.stop();
    delay(1);

}
