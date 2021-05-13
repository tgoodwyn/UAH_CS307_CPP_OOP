// ######################################################################################## //
// ######################################### HEADER FILE ################################## //
// ######################################################################################## //

//----------------------------------------- PREPROCESSOR -----------------------------------//
#pragma once
//----------------------------------------- PREPROCESSOR -----------------------------------//


// ----------------------------------------- INCLUDES ------------------------------------- //
// STD headers
#include <vector>

// Project headers
#include "EnviroSimDataParser.h"
#include "DisplayDevice.h"
#include "Sensor.h"
#include "DisplayFactory.h"

// ----------------------------------------- INCLUDES ------------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //


// ######################################################################################## //
// ######################################## DECLARATIONS ################################## //
// ######################################################################################## //

class DisplayDevice;
class Sensor;

class SensorMount
{


public:
	vector<DisplayDevice *>m_vSetOfDisplays;
	vector<Sensor*>m_vSetOfSensors;


public:

	// special class methods
	SensorMount(EnviroSimDataParser* dataReader );
	~SensorMount();

	// utility functions
	void assignIndividualSensors();
	void collectData();
	void resetSystemObservers();
	//void reportUnmonitoredSensors();

	// getters
	vector<DisplayDevice *> getDisplays();
	vector<Sensor*> getSensors();

};

