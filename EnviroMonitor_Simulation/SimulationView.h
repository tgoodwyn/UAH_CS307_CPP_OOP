// ######################################################################################## //
// ######################################### HEADER FILE ################################## //
// ######################################################################################## //


//----------------------------------------- PREPROCESSOR -----------------------------------//
#pragma once
//----------------------------------------- PREPROCESSOR -----------------------------------//


// ----------------------------------------- INCLUDES ------------------------------------- //
// STD headers
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
// Project headers
#include "SensorMount.h"
#include "SimulationModel.h"
#include "SimulationController.h"
#include "Observer.h"

// ----------------------------------------- INCLUDES ------------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //


// ######################################################################################## //
// ######################################## DECLARATIONS ################################## //
// ######################################################################################## //


class SimulationController;
class SimulationModel;
class SensorMount;

class SimulationView : Observer
{
public:
	//vector<DisplayDevice *>m_setOfDisplays; 
	SimulationModel *model;
	SimulationController *controller;

public:
	SimulationView();
	~SimulationView();

// utility
	void displayWelcome();
	void displaySystemInfo(SensorMount* mount);
	void initializeObserverSystem(SensorMount* mount);
	void displaySubscriptions(SensorMount* mount);
	void displaySensorReading(DisplayDevice* display, Sensor* sensor);
	void askToBegin();

// Required overrides 
	void handleNotification(DisplayDevice *display);

// Getters and setters 
	void setController(SimulationController *controller);
	void setModel(SimulationModel * model);

	void displayMissingSensors();
};

