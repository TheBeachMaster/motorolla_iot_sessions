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