/*
  Using the MLX90632 FIR Sensor

  This example shows how to remotely read the surface temperature of whatever the sensor is pointed at. 

*/

#include <Wire.h>
#include <wiring_private.h>
#include "SparkFun_MLX90632_Arduino_Library.h"
#define MOSFET 6

TwoWire myWire(&sercom1, 11, 13);
MLX90632 myTempSensor;

void setup()
{
	uint8_t address = 0x3A;
	Serial.begin(9600);
	pinMode(MOSFET, OUTPUT);
	digitalWrite(MOSFET, LOW);
	Serial.println("Enter any character to begin the Example");
	while (!Serial.available());
	Serial.println("MLX90632 Read Example");

	myWire.begin();
	pinPeripheral(11, PIO_SERCOM);
	pinPeripheral(13, PIO_SERCOM);
	myWire.setClock(1000000);

	//  myTempSensor.enableDebugging(Serial);
	MLX90632::status myStatus;
	myTempSensor.begin(address, myWire, myStatus);
	//myTempSensor.enableDebugging();
	if (myStatus != MLX90632::status::SENSOR_SUCCESS)
	{
		Serial.println("MLX90632 communication failed");
		while (true);
	}

	uint16_t valueInMemory; //Create a container
	myTempSensor.readRegister16(EE_MEAS1, valueInMemory);
	Serial.print("Value stored in EE_MEAS1: 0x");
	Serial.println(valueInMemory, HEX);

	myTempSensor.readRegister16(EE_MEAS2, valueInMemory);
	Serial.print("Value stored in EE_MEAS2: 0x");
	Serial.println(valueInMemory, HEX);

	// setup digital outputs to visualize loop timing
	//pinMode(14, OUTPUT);
	//digitalWrite(14, LOW);
	//pinMode(16, OUTPUT);
	//digitalWrite(16, LOW);
	//pinMode(10, OUTPUT);
	//digitalWrite(10, LOW);
}

void loop()
{
	float objectTemp;
	float AMB;
	float Sto;
	MLX90632::status myStatus;
	objectTemp = myTempSensor.startRawSensorValues(myStatus); //start measurement conversion
	myStatus = MLX90632::status::SENSOR_NO_NEW_DATA;
	
	while (myStatus != MLX90632::status::SENSOR_SUCCESS)
	{
		myTempSensor.getRawSensorValues(myStatus, AMB, Sto); //Get the temperature of the object we're looking at in C
		objectTemp = myTempSensor.getObjectTemp(AMB, Sto);
	}
	Serial.print("AMB:");
	Serial.println(AMB);
	Serial.print("Sto:");
	Serial.println(Sto);
	Serial.print("Object temperature: ");
	Serial.print(objectTemp, 2);
	Serial.println(" C");

}
