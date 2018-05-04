/*
 Name:		WIFI101_SUB
 Created:	05/05/2018 01:11:49 AM
 Author:	Kennedy Otieno
 Code: Adapted from the ESP Dallas Temperature sample
*/

#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>
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

char ssid[] = "AFRONANA";     //  your network SSID (name)
char pass[] = "Nanafam4";  // your network password 
int status = WL_IDLE_STATUS;     // the Wifi radio's status

const char* commandTopic = "<username>/WIFI101/commands";
const char* sensorTopic = "<username>/WIFI101/readings/temp";
const char* birthTopic = "<username>/WIFI101/birth";
const char* username = "<username>";
const char* password = "<password>";
int ledState = LOW;

WiFiClient wifisub101Cli;

void setup(void);
void loop(void);
void getCommands(void);
void sendTemperature(float temp);
void connectToWPA(void);
void reconnectDevice(void);
void printWifiData(void);
void printCurrentNet(void);


void wifiCallBack(char* topic, byte* payload, unsigned int length);

AfricasTalkingCloudClient client(wifiCallBack, wifisub101Cli); 


void setup()
{
  pinMode(LEDPIN, OUTPUT);
    WiFi.setPins(10, 3, 4);
    Serial.begin(9600);
    while (!Serial) {
        ;
    }
    connectToWPA();
  Serial.println(" OK");
}

void loop()
{
    float temp;

    while (!client.connected())
    {
        reconnectDevice();
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
    reconnectDevice(); 
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
    reconnectDevice(); 
    client.connect("WIFI101", username, password);
  }
}

void wifiCallBack(char* topic, byte* payload, unsigned int length)
{
    String data = (char *)payload;
    if (String(topic) == commandTopic)
    {
        data == "ON" ? digitalWrite(LEDPIN, !ledState) : digitalWrite(LEDPIN, ledState); // Look for a more elegant way of doing this
    }
}

void connectToWPA()
{
    Serial.println(F("Setting up connection...."));
    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true);
    }
    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }
    // you're connected now, so print out the data:
    Serial.print("You're connected to the network");
    printCurrentNet();
    printWifiData();
}


void printWifiData() {
    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    Serial.println(ip);

    // print your MAC address:
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.print("MAC address: ");
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.println(mac[0], HEX);

}

void printCurrentNet() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print the MAC address of the router you're attached to:
    byte bssid[6];
    WiFi.BSSID(bssid);
    Serial.print("BSSID: ");
    Serial.print(bssid[5], HEX);
    Serial.print(":");
    Serial.print(bssid[4], HEX);
    Serial.print(":");
    Serial.print(bssid[3], HEX);
    Serial.print(":");
    Serial.print(bssid[2], HEX);
    Serial.print(":");
    Serial.print(bssid[1], HEX);
    Serial.print(":");
    Serial.println(bssid[0], HEX);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.println(rssi);

    // print the encryption type:
    byte encryption = WiFi.encryptionType();
    Serial.print("Encryption Type:");
    Serial.println(encryption, HEX);
    Serial.println();
}

void reconnectDevice(void) 
{

    while (!client.connected()) 
    {
        // Connect to WPA...
        connectToWPA();
        Serial.print(F("Contacting Server: "));
        Serial.println();
    if (!client.connect("WIFI101", username, password))
    {
        Serial.print(" Failed to Connect to Broker");
        Serial.println(client.state());
        }
    Serial.println("Re/Connected");
    client.publish(birthTopic, "WIFI101-MODULE-birth");
    client.subscribe(commandTopic, QOS1);
    }
}