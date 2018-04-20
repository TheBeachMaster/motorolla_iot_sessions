import math
from decimal import Decimal
class Linear:
    '''brief Linear Congruential temprature data generator
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
    '''

    def lcdGen_tempreture(self, a, c):
        a = Decimal(a)
        c = Decimal(c)
        # decimal.Decimal
        # a.self = a
        # c.self = c
        tempMax = 42
        tempMin = 10
        temperatureModulus = Decimal(tempMax % tempMin)
        tempVal = Decimal(0.59926546)
        tempVal = (a * tempVal + c) * temperatureModulus
        return tempVal

    '''brief Linear Congruential humidity data generator
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
    '''

    def lcdGen_humidity(self, a, c):
        a = Decimal(a)
        c = Decimal(c)
        #a.self = a
        #c.self = c
        humMax = 87
        humMin = 10
        humidtyMudulus = Decimal(humMax % humMin)
        humidityVal = Decimal(0.995)
        humidityVal = (a * humidityVal + c)* humidtyMudulus
        return humidityVal

    '''brief Linear Congruential pressure data generator
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
    '''

    def lcdGen_pressure(self, a, c):
        a = Decimal(a)
        c = Decimal(c)
        #a.self = a
        #c.self = c
        pressureModulus = Decimal(3 % 2)
        pressureVal = Decimal(0.55624)
        pressureVal = (a * pressureVal + c) * pressureModulus
        return pressureVal

