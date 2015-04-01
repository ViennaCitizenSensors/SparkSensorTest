// This #include statement was automatically added by the Spark IDE.
#include "Barometer_BMP085.h"

#define AIRQUALITY A0

float temperature=0, pressure=0, atm=0, altitude=0;
unsigned int airquality=0;
Barometer myBarometer;

void setup(){
  Serial.begin(9600);

  #ifdef BAROMETER_BMP085
  myBarometer.init();
  Spark.variable("temp", &temperature, DOUBLE);
  Spark.variable("pressure", &pressure, INT);
  #endif

  Spark.variable("airquality", &airquality, INT);

  pinMode(AIRQUALITY, INPUT);
}

void loop()
{
#ifdef BAROMETER_BMP085
   temperature = myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT()); //Get the temperature, bmp085ReadUT MUST be called first
   pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());//Get the temperature
   altitude = myBarometer.calcAltitude(pressure); //Uncompensated caculation - in Meters
   atm = pressure / 101325;
#else
  temperature = 0;
  pressure = 0;
#endif

  Serial.print("Temperature: ");
  Serial.print(temperature, 2); //display 2 decimal places
  Serial.println("deg C");

  Serial.print("Pressure: ");
  Serial.print(pressure, 0); //whole number only.
  Serial.println(" Pa");

  Serial.print("Ralated Atmosphere: ");
  Serial.println(atm, 4); //display 4 decimal places

  Serial.print("Altitude: ");
  Serial.print(altitude, 2); //display 2 decimal places
  Serial.println(" m");


airquality = analogRead(AIRQUALITY);

  Serial.print("Air Quality: ");
  Serial.print(airquality, 2); //display 2 decimal places
  Serial.print(" (");
  Serial.print(airquality / 4096 * 100, 2); //display 2 decimal places
  Serial.println("%)");

  Serial.println();

  delay(1000); //wait a second and get values again.
}
