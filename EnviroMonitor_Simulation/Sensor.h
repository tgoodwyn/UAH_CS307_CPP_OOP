// ######################################################################################## //
// ######################################### HEADER FILE ################################## //
// ######################################################################################## //


//----------------------------------------- PREPROCESSOR -----------------------------------//
#pragma once
//----------------------------------------- PREPROCESSOR -----------------------------------//


// ----------------------------------------- INCLUDES ------------------------------------- //
// STD headers
#include <vector>
#include <iostream>

// Project headers
#include "DisplayDevice.h"
#include "Subject.h"

// ----------------------------------------- INCLUDES ------------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //


// ######################################################################################## //
// ######################################## DECLARATIONS ################################## //
// ######################################################################################## //
class DisplayDevice;
class Sensor : public Subject
{

public:
	char type[30], material[30], units[30];
	int ID;
	double minVal, maxVal, curVal;
	vector<DisplayDevice *> m_vObservers; 
	int broadcasterID;
	double currentReading;

public:

	// special class methods
	Sensor();			
	~Sensor();

	// utility functions
	void generateData(); 
	void registerObserver(DisplayDevice *obs);
	bool removeObserver(DisplayDevice *obs);
	void notifyObservers();
	int getBroadcasterID();
	double getCurrentReading();

	// getters
	char* getType();
	char* getMaterial();
	char* getUnits();
	int& getID();
	double& getMin();
	double& getMax();
	double getDataReading();


};

