#define _CRT_SECURE_NO_WARNINGS

// Class header file
#include "SimulationController.h"

// namespace
using namespace std;

SimulationController::SimulationController()
{
}

SimulationController::~SimulationController()
{
}

void SimulationController::setView(SimulationView * view)
{
	this->view = view;

}
void SimulationController::setModel(SimulationModel * model)
{
	this->model = model;
}

bool SimulationController::startSimulation()
{
	std::string input;
	std::cin >> input;
	return (!input.compare("b"));

}
void SimulationController::userSelectSubscriptions()
{
	int deviceNo, sensorNo;
	cin >> deviceNo >> sensorNo;

	if (deviceNo < model->getMount()->getDisplays().size())

	{
		DisplayDevice * display = model->getMount()->getDisplays().at(deviceNo);
		if (sensorNo < display->m_vConnectedSensors.size())
		{
			Sensor * sensor = display->m_vConnectedSensors.at(sensorNo);


			cout << "user selected device " << display->type
				<< " and "
				<< "sensor " <<
				sensor->ID
				<< endl;

			for (auto connection : display->m_vConnectedSensors)
			{
				if (sensor == connection)
				{
					if (sensor->removeObserver(display))
						break;
					else
						sensor->registerObserver(display);
				}
			}

		}
		else
			cout << "invalid sensor #" << endl;
	}
	else
		cout << "invalid display #" << endl;

	//system("pause");
}


string SimulationController::getFileName()
{
	std::string input;
	std::cin >> input;
	return input;
}

