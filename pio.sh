#!/bin/bash

if ! hash python; then
    echo "Python is required to run some of these tests"
    exit 1
fi

py=$(python -V 2>&1 | sed 's/.* \([0-9]\).\([0-9]\).*/\1\2/')
if [[ "$py" -lt "27" ||  "$py" -gt "30" ]]
then
    echo "This script requires Python 2.7.X installed"
    exit 1
fi


# Install WiFi 101  , TinyGSM , Dallas Temp and OneWire 
platformio lib -g install 299 1287 54 2604

# WIFI101 
platformio ci ./wifi --board=megaatmega2560 --lib="."
platformio ci ./wifi_sub --board=megaatmega2560 --lib="."

# GSM
platformio ci ./gsm --board=megaatmega2560 --lib="." 
platformio ci ./gsm_sub --board=megaatmega2560 --lib="." 

# ESP8266
platformio ci  ./esp8266 --board=esp01 --lib="." --lib="esp8266/lib/libmath"

exit 0