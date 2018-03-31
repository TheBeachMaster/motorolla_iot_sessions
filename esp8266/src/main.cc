#include <ESP8266WiFi.h>
#include <AfricasTalkingCloud.h>
#include <Arduino.h>
#include "libmath.hpp"

#define WLAN_SSID "SSID"
#define WLAN_PASSWORD "PASSWORD"
#define QOS 2
#define DELAY_INTERVAL 60 

LibMath procData;

WiFiClient esp8266_client;

AfricasTalkingCloudClient client(esp8266_client);

void wifiConnect();
void sendTemperature();
void sendPressure();
void sendHumidity();


void setup() {
  Serial.begin(115200);
  wifiConnect();
}

double genA
double cTemp;
double cPress;
double cHum;

void loop() {

    while (!client.connected())
    {
      client.connect("ESP8266-0112", "<username>", "<password>");
      client.publish("<username>/ESP8266-0112/birth", "ESP8266-0112birth");
    }


    int cnt = DELAY_INTERVAL;
    while(cnt--)
      delay(1000);
}

void wifiConnect()
{
    Serial.print("Connecting to Network");
    WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
}

void sendTemperature()
{  
   while(!client.connected() && !client.loop()) 
   {
    Serial.println("Connection failed");
    wifiConnect(); 
    client.connect("ESP8266-0112", "<username>", "<password>");
  }

genA = (random(48989, 60562)) / 100000;
cTemp = (random(45232, 64329)) / 100000;
 
double temp = procData.lcdGen_temperature(genA, cTemp);

char data[50];
snprintf(data,20, "%ld", temp);
client.publish("<username>/ESP8266-0112/readings/temp", data, QOS);
}

void sendPressure()
{  
   while(!client.connected() && !client.loop()) 
   {
    Serial.println("Connection failed");
    wifiConnect(); 
    client.connect("ESP8266-0112", "<username>", "<password>");
  }
  
genA = (random(46625, 60562)) / 100000; 
cPress = (random(45232, 64329)) / 100000;

double press = procData.lcdGen_pressure(genA, cPress);

 char data[50];
 snprintf(data,10, "%ld", press);
 client.publish("<username>/ESP8266-0112/readings/pressure", data, QOS);
}

void sendHumidity()
{  
   while(!client.connected() && !client.loop())
  {
    Serial.println("Connection failed");
    wifiConnect(); 
    client.connect("ESP8266-0112", "<username>", "<password>");
  }

  genA = (random(56256, 60562)) / 100000;
  cHum = (random(38987, 45232)) / 100000;

  double hum = procData.lcdGen_humidity(genA, cHum)
 char data[50];
 snprintf(data,10, "%ld", hum);
 client.publish("<username>/ESP8266-023545/readings/humidity", data, QOS);
}