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
    const double tempMax = 42;
    const double tempMIn = 10;
    const double pressMax = 2;
    const double humMax = 87;
    const double humMin = 5;
    const double maxPress = 1.2;
    const double minPress = 0.7;
};
#endif // !LIBMATH_H
