#include <ESP8266WiFi.h>
#include <AfricasTalkingCloud.h>
#include <Arduino.h>
#include "libmath.hpp"

#define WLAN_SSID "AFRONANA"
#define WLAN_PASSWORD "Nanafam4"
#define QOS 2
#define DELAY_INTERVAL 60 

LibMath procData;

WiFiClient esp8266_client;

AfricasTalkingCloudClient client(esp8266_client);

void wifiConnect();
void sendTemperature();
void sendPressure();
void sendHumidity();
double genA;
double cTemp;
double cPress;
double cHum;
char data[50];

void setup() {
  Serial.begin(115200);
  wifiConnect();
}

void loop() {

    while (!client.connected())
    {
      client.connect("ESP8266-Cli", "strathmore", "strathmore");
      client.publish("strathmore/ESP8266-Cli/birth", "ESP8266-Clibirth");
    }

    sendHumidity();
    sendPressure();
    sendTemperature();

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
    client.connect("ESP8266-Cli", "strathmore", "strathmore");
  }

genA = (random(48989, 60562)) / 100000;
cTemp = (random(45232, 64329)) / 100000;
 
double temp = procData.lcdGen_temperature(genA, cTemp);


snprintf(data,20, "%ld", temp);
client.publish("strathmore/ESP8266-Cli/readings/temp", data, QOS);
}

void sendPressure()
{  
   while(!client.connected() && !client.loop()) 
   {
    Serial.println("Connection failed");
    wifiConnect(); 
    client.connect("ESP8266-Cli", "strathmore", "strathmore");
  }
  
genA = (random(46625, 60562)) / 100000; 
cPress = (random(45232, 64329)) / 100000;

double press = procData.lcdGen_pressure(genA, cPress);

 snprintf(data,10, "%ld", press);
 client.publish("strathmore/ESP8266-Cli/readings/pressure", data, QOS);
}

void sendHumidity()
{  
   while(!client.connected() && !client.loop())
  {
    Serial.println("Connection failed");
    wifiConnect(); 
    client.connect("ESP8266-Cli", "strathmore", "strathmore");
  }

  genA = (random(56256, 60562)) / 100000;
  cHum = (random(38987, 45232)) / 100000;

  double hum = procData.lcdGen_humidity(genA, cHum);
 snprintf(data,10, "%ld", hum);
 client.publish("strathmore/ESP8266-Cli/readings/humidity", data, QOS);
}