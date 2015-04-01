SparkSensorTest
===============

We're trying to build up a sensor-network over the city of vienna. By using Spark Core we found a nice platform for quick and almost Arduino-compatible microconttrollers.
The sourcecode in "src" can be directly opened using Spark Dev.

Installation
------------

- Make sure you claimed your Spark Core, or Photon, Electron first.
- Do a git clone of the repository and open the file "sensors.ino" with Spark Dev.
- Hit "Flash via the Cloud" (Crtl+U).

Your Core should start flashing pink, after a minute it should be back online with the "breathing cyan". You can now access the sensor data over the cloud, eg via Spark CLI or Spark Dev (Spark => Show cloud variables)

Licence
-------
See licence information in the source-files.
