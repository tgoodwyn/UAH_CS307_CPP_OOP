#pragma once

// STD headers
#include <string>
// Project headers
#include "SimulationView.h"
#include "SimulationModel.h"
class SimulationView;
class SimulationModel;

class SimulationController
{
public:
	SimulationView* view;
	SimulationModel* model;

public:
	SimulationController();	
	~SimulationController();

// utility
	string getFileName(void);
	void userSelectSubscriptions();
	bool startSimulation();
// Getters and setters 
	void setView(SimulationView *view);
	void setModel(SimulationModel * model);


};

