// ######################################################################################## //
// ######################################### HEADER FILE ################################## //
// ######################################################################################## //

//----------------------------------------- PREPROCESSOR -----------------------------------//
#pragma once
//----------------------------------------- PREPROCESSOR -----------------------------------//


// ----------------------------------------- INCLUDES ------------------------------------- //
// STD headers
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>     

// Project headers
#include "EnviroSimDataParser.h"
#include "SensorMount.h"
#include "SimulationView.h"
#include "SimulationController.h"

//

// ----------------------------------------- INCLUDES ------------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //


// ######################################################################################## //
// ######################################## DECLARATIONS ################################## //
// ######################################################################################## //
class SimulationView;
class SimulationController;
class SensorMount;

class SimulationModel
{

private:
	SimulationView* view;
	SimulationController* controller;
	SensorMount*  m_SensorMount;

public:
	SimulationModel();
	~SimulationModel();

// utility
	void RegisterFile(EnviroSimDataParser * dataReader);
	bool run();

// getters
	SensorMount* getMount();
	void setController(SimulationController *controller);
	void setView(SimulationView *view);

};
