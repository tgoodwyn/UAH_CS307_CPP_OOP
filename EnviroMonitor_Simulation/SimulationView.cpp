// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS FILE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //


//------------------------------------------ PREPROCESSOR -----------------------------------//
#define _CRT_SECURE_NO_WARNINGS
//------------------------------------------ PREPROCESSOR -----------------------------------//


// ----------------------------------------- INCLUDES ------------------------------------- //
// Class header file
#include "SimulationView.h"
// ----------------------------------------- INCLUDES ------------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //

SimulationView::SimulationView()
{
}

SimulationView::~SimulationView()
{
}

void SimulationView::displayWelcome()
{
	cout << "======================================================================" << endl; 
	cout << "|                                                                    |" << endl;
	cout << "|                   Programming Assignment 1                         |" << endl;
	cout << "|                  Prepared by Tyler Goodwyn                         |" << endl;
	cout << "|                           CS 307                                   |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "======================================================================" << endl;
	cout << endl << endl; 
	cout << "This is a a simulation of EnviroSensors Inc equipment " << endl;
	cout << "Please enter the name of a file that contains equipment information " << endl;
	cout << "Include the dot .XML extension in the name " << endl;

}

void SimulationView::displaySystemInfo(SensorMount* mount)
{
	cout << "\n\n======================================================================" << endl;
	cout << "======================================================================" << endl;
	cout << "The following information provided for checking purposes:" << endl;
	for (auto display : mount->getDisplays())
	{


		cout << "\n\nDisplay type: " << display->type << " has the following sensors:" << endl;


		for (int i = 0; i < display->IDCount; i++)
		{
			cout << "\nSensor " << i + 1 << endl;
			cout << std::left <<
				std::setw(15) << "  Sensor type: " <<
				std::setw(18) << display->m_vConnectedSensors.at(i)->type <<
				std::setw(15) << " |     minVal: " <<
				std::setw(20) << display->m_vConnectedSensors.at(i)->minVal << "\n" <<
				std::setw(15) << "  Units: " <<
				std::setw(18) << display->m_vConnectedSensors.at(i)->units <<
				std::setw(15) << " |     ID: " <<
				std::setw(20) << display->m_vConnectedSensors.at(i)->ID << "\n" <<		
				std::setw(15) << "  Material: " <<
				std::setw(18) << display->m_vConnectedSensors.at(i)->material << 
				std::setw(15) << " |     maxVal: "  <<
				std::setw(20) << display->m_vConnectedSensors.at(i)->maxVal << endl << endl;

		}
	}

}

void SimulationView::initializeObserverSystem(SensorMount * mount)
{
	mount->resetSystemObservers();
	for (auto display : mount->getDisplays())
	{
		display->registerObserver(this);
	}
}

void SimulationView::displaySubscriptions(SensorMount* mount)
{
	int i = 0;
	for (auto display : mount->getDisplays())
	{
		cout << "\n\n" << i << ". Device " << display->type << ":" << endl ;

		for (int i = 0; i < display->IDCount; i++)
		{
			bool monitored = false;
			Sensor * sensor = display->m_vConnectedSensors.at(i);
			for (auto d : sensor->m_vObservers)
			{
				if (d == display)
				{
					monitored = true;
					break;
				}
			}

			cout 
				<< "\t" << i << ". Sensor " 
				<< sensor->ID
				<< " - "
				<< ((monitored) ? "is being monitored" : "is not being monitored")
				<< endl;
		}
		i++;
	}


}

void SimulationView::displaySensorReading(DisplayDevice* display, Sensor* sensor)
{
	cout << "\n"                << display->type << ":" << endl;
	cout << std::left 
		 << std::setw(15)
		 << string("\tSensor ID:  ")    
		 << std::setw(8)
		 << to_string(sensor->ID)
		 << std::setw(25)
		 << "\t| Current value: "   << sensor->curVal
		 << " "                   << sensor->units << endl;
	cout << std::setw(15)
		<< string("\tSensor type:  ") 
		<< std::setw(8) 
		<<sensor->type
		<< std::setw(25)
		<< "\t| Sensor material: " << sensor->material
		<< endl;
	return;
}

void SimulationView::askToBegin()
{
	cout << "\n\n======================================================================" << endl;
	cout << "======================================================================" << endl;
	cout << "\nEnter b to begin simulation. Press any other key to exit\n Once the simulation has begun, press s to configure subscriptions" << endl;

}

void SimulationView::handleNotification(DisplayDevice * display)
{
	for (auto s : model->getMount()->getSensors())
	{
		if (display->getBroadcasterID() == s->getID())
		{
			displaySensorReading(display, s);
			break;
		}
	}
}

void SimulationView::setController(SimulationController * controller)
{
	this->controller = controller;
}

void SimulationView::setModel(SimulationModel * model)
{
	this->model = model;

}

void SimulationView::displayMissingSensors()
{
	for (auto d : model->getMount()->getDisplays())
	{
		if (d->getUnsubscribedNumber() > 0)
		{
			cout << "\n" << d->type << " has " << d->getUnsubscribedNumber()
				<< " unreported sensors " << endl;
		}
	}

}

