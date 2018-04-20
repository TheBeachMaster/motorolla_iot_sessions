from random import randint
import paho.mqtt.client as mqtt
from linear_math import Linear
import time as timer
from decimal import Decimal

QOS = 2

datagen = Linear()

broker = "sungura1-angani-ke-host.africastalking.com"
brokerPort = 10883 
client = mqtt.Client("paho_mqtt_client")
username = "paho"
pahopassword = "pahopassword"

def on_pub(client, userdata, mid):
    print("published:"+str(mid))

# fired when client succesfully subscribes to a topic
def on_sub(client, obj, mid, granted_qos):
    print("Subscribed:" + str(mid) + " " + str(granted_qos))

# fired when a client successfully connects to the server    
def on_con(client, userdata, flags, rc):
    print("Connected with code: " + str(rc))

# fired when a client disconnects from the server
def on_discon(client, userdata, rc):
    print("Successfully disconected from the broker")

# fired when a client receives a message from the subscribed topic
def on_msg(client, userdata, message):
    timer.sleep(1)
    print("Received a message from the broker: ", str(message.payload.decode("utf-8")))

# supply authentication details to a connnecting client
client.username_pw_set(username, password=pahopassword)

# callbacks to be triggered when stuff happens : Event loops
client.on_message = on_msg
client.on_subscribe = on_sub
client.on_publish = on_pub
client.on_connect = on_con
client.on_disconnect = on_discon

# connection details (broker url , broker port, keepalive<=60 seconds)
client.connect(broker, brokerPort, 60)

# strange behavior where the publsihing occurs before the on_connect event is fired first
timer.sleep(5)

def sendTemperature():  
    genA = randint(13985, 27845) / 1000
    cTemp = randint(130188, 259949) / 100000
    genA = Decimal(genA)
    cTemp = Decimal(cTemp)
    temp = datagen.lcdGen_tempreture(genA, cTemp)
    data = str(temp)
    client.publish("paho/linear/readings/temp", data, QOS)


def sendPressure():
    genA = randint(46625, 60562) / 100000 
    cPress = randint(45232, 64329) / 100000
    genA = Decimal(genA)
    cPress = Decimal(cPress)
    press = datagen.lcdGen_pressure(genA, cPress)
    data = str(press)
    client.publish("paho/linear/readings/pressure", data, QOS)


def sendHumidity():
    genA = randint(13985, 27845) / 10000
    cHum = randint(38987, 45232) / 10000
    genA = Decimal(genA)
    cHum = Decimal(cHum)
    hum = datagen.lcdGen_humidity(genA, cHum)
    data = str(hum)
    client.publish("paho/linear/readings/humidity", data, QOS)

counter = 0
while (counter < 30):
    client.loop_start()
    sendTemperature()
    sendPressure()
    sendHumidity()
    counter = counter + 1
    print(counter)
    timer.sleep(2)

print("Good Bye!")
client.loop_stop()
client.disconnect()