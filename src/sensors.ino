// This #include statement was automatically added by the Spark IDE.
#include "../includes/Barometer.h"

#define AIRQUALITY A0

float temperature, pressure, atm, altitude, airquality;
Barometer myBarometer;

void setup(){
  Serial.begin(9600);
  myBarometer.init();
  Spark.variable("temperature", &temperature, DOUBLE);
  Spark.variable("pressure", &pressure, INT);
  Spark.variable("airquality", &airquality, DOUBLE);
  pinMode(AIRQUALITY, INPUT);
}

void loop()
{
   temperature = myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT()); //Get the temperature, bmp085ReadUT MUST be called first
   pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());//Get the temperature
   altitude = myBarometer.calcAltitude(pressure); //Uncompensated caculation - in Meters
   atm = pressure / 101325;

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
