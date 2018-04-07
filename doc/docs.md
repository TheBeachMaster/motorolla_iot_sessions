# Get Up and Running 

On a fresh box go ahead and install **PlatformIO** 

> PlatformIO is a unified development environment with debugging , unit testing and FOTA capabilities.

## Installing PlatformIO Core 

> Ensure you have `Python 2.7` 
>
> Also ensure you have a working setup of the Arduino IDE with ESP Tools installed. Follow these instructions → [https://goo.gl/ennK3k](http://esp8266.github.io/Arduino/versions/2.0.0/doc/installing.html) 
>
> Most of the code and compilation will be done from a text editor -  [Visual Studio Code](aka.ms/vscode) is recommended - and the command line interface - bash , cmd.exe or PowerShell.

1. From and administrative command line run the following:

   ```bash
   # use sudo if need be
   $ pip install -U platformio 
    
   # For Windows 
   > pip install -U platformio
   ```

   > Other installation options can be found here → [https://goo.gl/7Ubxdc](http://docs.platformio.org/en/latest/installation.html#id5)

2. Change to a fresh directory and run the following command to initialize a new project for Arduino UNO board


   ```bash
   $ platformio init --board uno
   ```

   This will generate (if successful) 

   ​	

   ```bash
   ...lib ## Keep your custom libraries here
   .../lib/readme.txt
   ...src ## All application source files live here
   ....travis.yml ## use this for CI/CD configrations
   ...gitignore ## what not to push to Version Control (git)
   ```

   3. Add your application's source files and run the following commands after connecting your board to the PC

      ```bash
      $ pio run --target upload
      ```



## Getting up and running with MQTT 

## An Overview of MQTT

[MQTT](http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html) is a Client Server publish/subscribe messaging transport protocol. It is light weight, open, simple, and designed so as to be easy to implement. These characteristics make it ideal for use in many situations, including constrained environments such as for communication in Machine to Machine (M2M) and Internet of Things (IoT) contexts where a small code footprint is required and/or network bandwidth is at a premium.

The protocol runs over TCP/IP, or over other network protocols that provide ordered, lossless, bi-directional connections. Its features include:

- Use of the publish/subscribe message pattern which provides one-to-many message distribution and decoupling of applications.
- A messaging transport that is agnostic to the content of the payload.
- Three qualities of service for message delivery:
  - "At most once", where messages are delivered according to the best efforts of the operating environment. Message loss can occur. This level could be used, for example, with ambient sensor data where it does not matter if an individual reading is lost as the next one will be published soon after.
  - "At least once", where messages are assured to arrive but duplicates can occur.
  - "Exactly once", where message are assured to arrive exactly once. This level could be used, for example, with billing systems where duplicate or lost messages could lead to incorrect charges being applied.
- A small transport overhead and protocol exchanges minimized to reduce network traffic.
- A mechanism to notify interested parties when an abnormal disconnection occurs.

## [MQTT Architecture](https://www.eclipse.org/community/eclipse_newsletter/2014/february/article2.php)

MQTT has a client/server model, where every sensor is a client and connects to a server, known as a broker, over TCP.

MQTT is message oriented. Every message is a discrete chunk of data, opaque to the broker.

Every message is published to an address, known as a topic. Clients may subscribe to multiple topics. Every client subscribed to a topic receives every message published to the topic.

For example, imagine a simple network with three clients and a central broker.

All three clients open TCP connections with the broker. Clients B and C subscribe to the `topic temperature` .

 ![febarticle2.1](febarticle2.1.png)

At a later time, Client A publishes a value of `22.5` for topic `temperature` . The broker forwards the message to all subscribed clients.

 ![febarticle2.2](febarticle2.2.png)



The publisher subscriber model allows MQTT clients to communicate one-to-one, one-to-many and many-to-one.

## MQTT Configuration

|              |                                        |
| ------------ | -------------------------------------- |
| **Username** | Default account username  `strathmore` |
| **Password** | Default account  passkey  `strathmore` |

> Note that your topics should start with `strathmore/` followed by a unique namespace  such as `strathmore/studentid-01/gsm/farm/track2` to avoid namespace collision on the public broker.
>
> Do not pass any special characters(such as emojis 😂) as they will be rejected by the broker

# Managing your own mini-IoT instance

## Requirements and steps

1. Install Node.JS as described here → [https://goo.gl/eP6r5J](https://nodejs.org/en/download/package-manager/)

2. Install Node-Red via `npm` as described here → [https://goo.gl/5Q3v4P](https://nodered.org/docs/getting-started/installation)

3. Optionally setup a free MongoDB Atlas Cluster and add a Stitch Backend application to store your data. Check these out  → [https://goo.gl/Tz1VXe](https://www.mongodb.com/cloud/atlas) . Select the **Free Sandbox** option. This will be you mini-data sink.

4. If you have setup an application on the Atlas Cluster successfully, you can install the mongo-db plugin for node-red as described here → [https://goo.gl/VSU3HV](https://www.npmjs.com/package/node-red-node-mongodb) . You can also setup  a MySQL instance ,Cassandra and PostGres instances by searching for their respective node-red plugins. There's a nice tutorial on MongoDB here → [https://goo.gl/8GatHn](https://www.compose.com/articles/power-prototyping-with-mongodb-and-node-red-2/) 

5. To launch a node-red instance run the following command from an  admin console window

    

   ```bash
   # unix-like environment
   $ node-red 

   # DOS-like environment
   > node-red
   ```

6. Follow this guide to help you configure your data sources and sinks. Link here → [https://goo.gl/UU7eQA](https://cookbook.nodered.org/)

7. When your are ready configure your **Mqtt Node** to point to `sungura1-angani-ke-host.africastalking.com:18083` . Note that `sungura1-angani-ke-host.africastalking.com` is the hostname and `10883` is the port. This configuration should not be used on production environments,it's for demos only. For prod deployments contact us at `info@africastlaking.com` .

## Managing your IoT Device farm

### ESP 8266 Procedural Data generator

Steps:

1. Create a new ESP8266 project

   ```bash
   pio init --board=esp01
   ```

2. In the `lib` folder of the created project  add the following 2 files 

   ```bash
   ../lib
   ../lib/libmath.hpp
   ../lib/libmath.cc
   ```

3. In `libmath.hpp` add the following declarations  

   ```c++
   #ifndef LIBMATH_H
   #define LIBMATH_H

   class LibMath
   {
   public:
       LibMath(){}

       /** \brief Linear Congruential temprature data generator
        * 
        * x = (a * x + c) mod m
        * Temperature range is set between 10°C and 42°C
        * Outside these ranges the genrated values will be reset
        * 
        * @param a The multiplier parameter (a) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0.
        *          Ideally between 0.4898978 and 0.5001568
        * @param c The increment parameter (c) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0
        *          Ideally between 0.889798  and 0.999958
        * @return  The generated temprature
        */
       double lcdGen_temperature(double a, double c);

       /** \brief Linear Congruential pressure data generator
        * 
        * x = (a * x + c) mod m
        * Pressure range is set between 0.7bars and 1.2bars
        * 
        * @param a The multiplier parameter (a) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0.
        *          Ideally between 0.46625 and 0.60562
        * @param c The increment parameter (c) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0
        *          Ideally between 0.45232 and 0.64329
        * @return  The generated pressure data
        */ 
       double lcdGen_pressure(double a, double c);

       /** \brief Linear Congruential humidity data generator
        * 
        * x = (a * x + c) mod m
        * Humidity  is set between 5% and 87%
        * 
        * @param a The multiplier parameter (a) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0.
        *          Ideally between 0.562562 and 0.60562
        * @param c The increment parameter (c) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0
        *          Ideally between 0.38986798 and 0.45232
        * @return  The generated humidty data
        */
       double lcdGen_humidity(double a, double c);

   private:

       // TODO Declare initializers
       const int tempMax = 42;
       const int tempMIn = 10;
       const int humMax = 87;
       const int humMin = 5;
       const double maxPress = 1.2;
       const double minPress = 0.7;
   };
   #endif // !LIBMATH_H


   ```

4. In the `libmath.cc` file add the following

   ```c++
   #include "libmath.hpp"


       /** \brief Linear Congruential temprature data generator
        * 
        * x = (a * x + c) mod m
        * Temperature range is set between 10°C and 42°C
        * Outside these ranges the genrated values will be reset
        * 
        * @param a The multiplier parameter (a) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0.
        *          Ideally between 0.4898978 and 0.5001568
        * @param c The increment parameter (c) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0
        *          Ideally between 0.889798  and 0.999958
        * @return  The generated temprature
        */
   double LibMath::lcdGen_temperature(double a, double c)
   {
      double temperatureModulus;
      temperatureModulus = tempMax % tempMIn;
      double tempVal = 0.99926546;
      tempVal = ( a * tempVal + c ) * temperatureModulus;
      return tempVal;
   }

       /** \brief Linear Congruential humidity data generator
        * 
        * x = (a * x + c) mod m
        * Humidity  is set between 5% and 87%
        * 
        * @param a The multiplier parameter (a) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0.
        *          Ideally between 0.562562 and 0.60562
        * @param c The increment parameter (c) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0
        *          Ideally between 0.38986798 and 0.45232
        * @return  The generated humidty data
        */
   double LibMath::lcdGen_humidity(double a, double c)
   {
      double humidtyModuls;
      humidtyModuls = humMax % humMin;
      double humidityVal = 0.99946;
      humidityVal = ( a * humidityVal + c ) * humidtyModuls;
      return humidityVal;
   }

       /** \brief Linear Congruential pressure data generator
        * 
        * x = (a * x + c) mod m
        * Pressure range is set between 0.7bars and 1.2bars
        * 
        * @param a The multiplier parameter (a) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0.
        *          Ideally between 0.46625 and 0.60562
        * @param c The increment parameter (c) used in the transition algorithm.
        *          Lower than (m) if (m) is not equal to 0
        *          Ideally between 0.45232 and 0.64329
        * @return  The generated pressure data
        */ 
   double LibMath::lcdGen_pressure(double a, double c)
   {
      double pressureModulus;
      pressureModulus = 3 % 2;
      double pressureVal = 0.55624;
      pressureVal = ( a * pressureVal + c ) * pressureModulus;
      return pressureVal;
   }
   ```

5. Now in the `src`  directory add a `main.cc` file so that the tree now looks like this

   ```bash
   ../lib
   ../lib/libmath.hpp
   ../lib/libmath.cc
   ../src/
   ../src/main.cc
   ..*.ini
   ..*.yml
   ...# etc
   ```

6. Add the following to `main.cc` file. Modify the values for your topic and Wi-Fi Network

   ```c++
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
   ```

7. Next install the external dependencies required the project , `AfricasTalkingCloud` library.

   > In the above project root directory run the following command

   ```bash
   > pio lib install "AfricasTalkingCloud" # for Windows
   $ pio lib install "AfricasTalkingCloud" # for Unix-like (sudo might be required)
   ```

8. Now check if the project run fine by running the following command from the terminal

   ```bash
   > pio run # WinDOS
   $ pio run #Unix-like might need Admin previledges
   ```

9. If the above step throws no errors, connect your ESP board to your dev box and run the following commands

   ```bash
   > pio run --target upload # WinDOS
   $ pio run --target upload # Unix-like (might need admin previledges)
   ```

   > Assumptions : 
   >
   > Getting started with ESP 8266 → [https://goo.gl/MfzLGy](https://www.geekstips.com/esp8266-arduino-tutorial-iot-code-example/) 
   >
   > ​