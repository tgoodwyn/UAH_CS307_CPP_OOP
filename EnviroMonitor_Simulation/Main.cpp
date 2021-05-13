// ======================================================================================== //
// ============================================ MAIN ====================================== //
// ======================================================================================== //
// A program for EnviroSensors, INC.
// Author: Tyler Goodwyn
// ======================================================================================== //

//------------------------------------------ PREPROCESSOR -----------------------------------//
#define _CRT_SECURE_NO_WARNINGS
//------------------------------------------ PREPROCESSOR -----------------------------------//


// ----------------------------------------- INCLUDES ------------------------------------- //
// STD headers
#include <iostream>

// Project headers
#include "SimulationView.h"
#include "EnviroSimDataParser.h"
#include "SimulationModel.h"
#include "SimulationController.h"

// ----------------------------------------- INCLUDES ------------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //

// ======================================================================================== //
// ============================================ MAIN ====================================== //
// ======================================================================================== //


void createSimulation(SimulationView * view, SimulationModel * model, SimulationController * controller);

int main(void)
{

	SimulationView * view = new SimulationView();
	SimulationModel * model = new SimulationModel();
	SimulationController * controller = new SimulationController();

	createSimulation(view, model, controller);
	view->displayWelcome();

	// SensorData2.xml
	string str_name = controller->getFileName();
	const char *c = str_name.c_str();
	EnviroSimDataParser *dataReader = new EnviroSimDataParser(c);

	model->RegisterFile(dataReader);
	view->displaySystemInfo(model->getMount());

	view->initializeObserverSystem(model->getMount());
	view->askToBegin();
	if (!controller->startSimulation())
		return 0;
	while (model->run());
}

void createSimulation(SimulationView * view, SimulationModel * model, SimulationController * controller)
{
	view->setModel(model);
	view->setController(controller);
	model->setView(view);
	model->setController(controller);
	controller->setModel(model);
	controller->setView(view);
}

