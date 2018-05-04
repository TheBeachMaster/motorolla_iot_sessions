/*
 Name:		GSM_SUB
 Created:	05/05/2018 00:41:49 AM
 Author:	Kennedy Otieno
 Code: Adapted from the ESP Dallas Temperature sample
*/

#define TINY_GSM_MODEM_SIM800 // Substitute for SIM Module e.g. SIM900 etc
#include <Arduino.h>
#include <TinyGsmClientSIM800.h>
#include <TinyGsmClient.h>
#include <AfricasTalkingCloud.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define QOS2 2
#define QOS1 1
#define DELAY_INTERVAL 60 
#define ONE_WIRE_BUS 2  
#define LEDPIN 13
#define DELAY_INTERVAL 60

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float oldTemp;

const char apn[] = "safaricom";
const char user[] = "saf";
const char pass[] = "data";

const char* commandTopic = "<username>/GSM/commands";
const char* sensorTopic = "<username>/GSM/readings/temp";
const char* birthTopic = "<username>/GSM/birth";
const char* username = "<username>";
const char* password = "<password>";
int ledState = LOW;

#define SerialAT Serial1
#define SerialMon Serial

TinyGsm modem(SerialAT);
TinyGsmClient gsmClient(modem);

void setup(void);
void loop(void);
void getCommands(void);
void sendTemperature(float temp);
void gsmClientConnect(void);

void gsmCallBack(char* topic, byte* payload, unsigned int length);

AfricasTalkingCloudClient client(gsmCallBack, gsmClient); 


void setup()
{
  pinMode(LEDPIN, OUTPUT);
  SerialMon.begin(115200);
  delay(10);

  SerialAT.begin(115200);
  delay(3000);

  SerialMon.println("Initializing Module...");
  modem.init();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);

  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" Error initializing network connectivity");
    while (true);
  }
  SerialMon.println(" OK");

  SerialMon.print("Connecting to ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    SerialMon.println(" Error Connecting to GPRS Network");
    while (true);
  }
  SerialMon.println(" OK");
}

void loop()
{
    float temp;

    while (!client.connected())
    {
        gsmClientConnect();
    }

    do {
      DS18B20.requestTemperatures(); 
      temp = DS18B20.getTempCByIndex(0);
      Serial.print("Temperature: ");
      Serial.println(temp);
    } while (temp == 85.0 || temp == (-127.0));

    if (temp != oldTemp)
    {
      sendTemperature(temp);
      oldTemp = temp;
    }
    int cnt = DELAY_INTERVAL;
    while(cnt--)
      delay(1000);
}

void sendTemperature(float temp)
{  
 while(!client.connected() && !client.loop()) 
 {
    Serial.println("Connection failed");
    gsmClientConnect(); 
  }
 char data[50];
 snprintf(data,10, "%ld", temp);
 client.publish(sensorTopic, data, QOS2);
}

void getCommands(void)
{
while(!client.connected() && !client.loop()) 
 {
    Serial.println("Connection failed");
    gsmClientConnect(); 
    client.connect("GSM", username, password);
  }
}

void gsmCallBack(char* topic, byte* payload, unsigned int length)
{
    String data = (char *)payload;
    if (String(topic) == commandTopic)
    {
        data == "ON" ? digitalWrite(LEDPIN, !ledState) : digitalWrite(LEDPIN, ledState); // Look for a more elegant way of doing this
    }
}

void gsmClientConnect(void) 
{

  if (!client.connect("GSM", username, password))
   {
    SerialMon.print(" Failed to Connect to Broker");
    SerialMon.println(client.state());
    }
  SerialMon.println("Re/Connected");
  client.publish(birthTopic, "GSM-MODULE-birth");
  client.subscribe(commandTopic, QOS1);
}