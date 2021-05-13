#pragma once
#include "SensorMount.h"
#include "DisplayDevice.h"
#include "EnviroSimDataParser.h"

class SensorMount;
class DisplayFactory;
class DisplayFactory
{
public:
	static DisplayFactory *instance;
	void createSystemDisplays(EnviroSimDataParser * dataReader, SensorMount * mount);
	static DisplayFactory *getInstance();

	
private:
	DisplayFactory();

};

