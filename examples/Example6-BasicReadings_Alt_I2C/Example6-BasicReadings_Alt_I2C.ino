/*
  Using the MLX90632 FIR Sensor
  By: Nathan Seidle
  SparkFun Electronics
  Date: December 21st, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14569

  This example shows how to remotely read the surface temperature of whatever the sensor is pointed at. 
  
  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the sensor onto the shield
  Serial.print it out at 9600 baud to serial monitor.

  Available functions:
  .getObjectTemp()
  .getObjectTempF()
  .getSensorTemp()
  .setMode() - MODE_SLEEP, MODE_STEP, MODE_CONTINUOUS
  .getMode()
  .enableDebugging()
  .disableDebugging()
  .deviceBusy()
  .dataAvailable()
*/

#include <Wire.h>
#include "wiring_private.h"

#include "SparkFun_MLX90632_Arduino_Library.h"
MLX90632 myTempSensor;

TwoWire myWire(&sercom1, 11, 13);

void setup()
{
  Serial.begin(9600);
  Serial.println("MLX90632 Read Example");

  myWire.begin();
  pinPeripheral(11, PIO_SERCOM);
  pinPeripheral(13, PIO_SERCOM);
  myWire.setClock(100000);

  MLX90632::status tempStatus;
  myTempSensor.begin(0x3A, myWire, tempStatus);
}

void loop()
{
  float objectTemp;

  //For the world
  objectTemp = myTempSensor.getObjectTemp(); //Get the temperature of the object we're looking at in C
  Serial.print("Object temperature: ");
  Serial.print(objectTemp, 2);
  Serial.print(" C");

  //For us silly people that use Fahrenheit
  /*objectTemp = myTempSensor.getObjectTempF(); //Get the temperature of the object we're looking at in F
  Serial.print("Object temperature: ");
  Serial.print(objectTemp, 2);
  Serial.print(" F");*/
  
  Serial.println();
}
