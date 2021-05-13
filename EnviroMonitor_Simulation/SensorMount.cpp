// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS FILE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //


//----------------------------------------- PREPROCESSOR -----------------------------------//
#define _CRT_SECURE_NO_WARNINGS
//----------------------------------------- PREPROCESSOR -----------------------------------//


// ----------------------------------------- INCLUDES ------------------------------------- //
// Class header file
#include "SensorMount.h"
// ----------------------------------------- INCLUDES ------------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //

SensorMount::SensorMount(EnviroSimDataParser * dataReader)
{
	Sensor *sens = new Sensor();

	while (dataReader->getSensorData(
		sens->getType(), sens->getMaterial(), &sens->getID(),
		sens->getUnits(), &sens->getMin(), &sens->getMax()))
	{
		m_vSetOfSensors.push_back(sens);
		sens = new Sensor();
	}

	DisplayFactory* dfac = DisplayFactory::getInstance();
	dfac->createSystemDisplays(dataReader, this);
}

SensorMount::~SensorMount()
{
}

void SensorMount::assignIndividualSensors()
{
	for (auto display : m_vSetOfDisplays)
	{
		for (auto sens : m_vSetOfSensors)
		{
			for (int i = 0; i < display->IDCount; i++)
			{
				if (display->IDs[i] == sens->getID())
					display->m_vConnectedSensors.push_back(sens);
			}
		}

	}
}

void SensorMount::collectData()
{
	for (auto i : m_vSetOfSensors)
	{
		i->generateData();
		i->notifyObservers();
	}
}

void SensorMount::resetSystemObservers()
{
	for (auto display : m_vSetOfDisplays)
	{
		for (auto sensor : display->m_vConnectedSensors)
		{
			sensor->registerObserver(display);
		}
	}
}




vector<DisplayDevice*> SensorMount::getDisplays()
{
	return m_vSetOfDisplays;
}

vector<Sensor*> SensorMount::getSensors()
{
	return m_vSetOfSensors;
}
