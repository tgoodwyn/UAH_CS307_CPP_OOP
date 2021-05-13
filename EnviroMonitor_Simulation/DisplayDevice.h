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
#include "Sensor.h"
#include "SimulationView.h"

// ----------------------------------------- INCLUDES ------------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //


// ######################################################################################## //
// ######################################## DECLARATIONS ################################## //
// ######################################################################################## //
class Sensor;
class SimulationView;

class DisplayDevice : public Observer, public Subject
{
public:
	char type[30];
	int IDs[10];
	int IDCount;
	int subscriptionCount;
	vector<Sensor*> m_vConnectedSensors; 
	vector<Sensor*> m_vSubscriptions;
	vector<SimulationView*> m_vObservers;

public:
	DisplayDevice();
	~DisplayDevice();


// Required overrides 
	void registerObserver(SimulationView *obs);
	bool removeObserver(SimulationView *obs);
	void notifyObservers();
	int getBroadcasterID();
	double getCurrentReading();
// Utility
	void handleNotification(Sensor *s);


// getters
	int getUnsubscribedNumber();
};

