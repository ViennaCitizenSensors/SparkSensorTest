/*
 * sensors.ino
 * A library for barometer
 *
 * Copyright (c) 2015 School of data
 * Website    : https://schoolofdata.wordpress.com/
 * Author     : Erwin Preuner
 * Change Log :
 *
 * loovee 9-24-2014
 * Change all int to short, all unsigned int to unsigned short to fit some 32bit system
 *
 * The MIT License (MIT)
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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
