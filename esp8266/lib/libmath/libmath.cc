#include "libmath.hpp"

double LibMath::lcdGen_temperature(double a, double c)
{
   temperatureModulus = 42 % 10;
   double tempVal = 0.99926546;
   tempVal = ( a * tempVal + c ) * temperatureModulus;
   return tempVal;
}

double LibMath::lcdGen_humidity(double a, double c)
{
   humidtyModuls = 87 % 5;
   double humidityVal = 0.99946;
   humidityVal = ( a * humidityVal + c ) * humidtyModuls;
   return humidityVal;
}
double LibMath::lcdGen_pressure(double a, double c)
{
   pressureModulus = 3 % 2;
   double pressureVal = 0.55624;
   pressureVal = ( a * pressureVal + c ) * pressureModulus;
   return pressureVal;
}