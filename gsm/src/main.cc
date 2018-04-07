#define TINY_GSM_MODEM_SIM800
#include <Arduino.h>
#include <AfricasTalkingCloud.h>
#include <TinyGsmClient.h>
#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 5
#define SerialMon Serial
SoftwareSerial SerialAT(2,3);
DHT dht(DHTPIN, DHTTYPE);

float temperature = dht.readTemperature();
float humidty = dht.readHumidity();
float heatIndex = dht.computeHeatIndex(temperature, humidty, false);
const char apn[]  = "internet";
const char user[] = "";
const char pass[] = "";

const char* birthTopic = "strathmore/gsm/birth";
const char* humidityTopic = "strathmore/gsm/humidity";
const char* temperatureTopic = "strathmore/gsm/temp";
const char* ledStatusTopic = "strathmore/gsm/led";
const char* heatIndexTopic = "strathmore/gsm/heatindex";
char mqttPayloadT[50];
char mqttPayloadH[50];
char mqttPayloadI[50];
int ledState = LOW;
long lastReconnectAttempt = 0;

#define LEDPIN 13
#define DELAY_PERIOD 60
#define SUBSCRIPTION_QOS 1
#define PUBLISH_QOS 1

void setup(void);
void loop(void);
void messageCallback(char* topic, byte* payload, unsigned int length);
void sendPayload(char* packet, const char* topic, int qos);
boolean gsmClientConnect();

TinyGsm modem(SerialAT);
TinyGsmClient gsmClient(modem);
AfricasTalkingCloudClient client(messageCallback, gsmClient);

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
  if (client.connected()) {
    client.loop();
  } else {
    unsigned long t = millis();
    if (t - lastReconnectAttempt > 10000L) {
      lastReconnectAttempt = t;
      if (gsmClientConnect()) {
        lastReconnectAttempt = 0;
      }
    }
  }



// send temp
snprintf(mqttPayloadT,30, "%f", temperature);
sendPayload(mqttPayloadT, temperatureTopic, PUBLISH_QOS);
//send humidity
snprintf(mqttPayloadH, 30, "%f", humidty);
sendPayload(mqttPayloadH, humidityTopic, PUBLISH_QOS);
// send heat index
snprintf(mqttPayloadI, 30, "%f", heatIndex);
sendPayload(mqttPayloadI, heatIndexTopic, PUBLISH_QOS);

int counter = DELAY_PERIOD;
while (counter--)
    delay(1000);
}

void messageCallback(char* topic, byte* payload, unsigned int length)
{
    SerialMon.print("Message received from:");
    SerialMon.println(topic);
    String data = (char *)payload;
    if (String(topic) == ledStatusTopic)
    {
        if (data == "OFF")
        {
            digitalWrite(LEDPIN, ledState);
        }else if (data == "ON")
        {
            ledState = HIGH;
            digitalWrite(LEDPIN, ledState);
        }else
        {
            digitalWrite(LEDPIN, ledState);
        }
    }
}

boolean gsmClientConnect() {

  if (!client.connect("GSM-MODULE-001", "strathmore", "strathmore")) {
    SerialMon.print(" Failed to Connect to Broker");
    SerialMon.println(client.state());
    return false;
  }
  SerialMon.println("Re/Connected");
  client.publish(birthTopic, "GSM-MODULE-001birth");
  client.subscribe(ledStatusTopic, SUBSCRIPTION_QOS);
  return client.connected();
}

void sendPayload(char* packet, const char* topic, int qos)
{
    client.publish(topic, packet, qos);
}