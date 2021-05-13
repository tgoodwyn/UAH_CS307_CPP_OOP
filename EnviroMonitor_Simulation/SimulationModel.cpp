// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS FILE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //


//----------------------------------------- PREPROCESSOR -----------------------------------//
#define _CRT_SECURE_NO_WARNINGS
#define C_INTERVAL 6.0
//----------------------------------------- PREPROCESSOR -----------------------------------//



// ---------------------------------------- INCLUDE AREA ---------------------------------- //
// Class header file
#include "SimulationModel.h"
// ---------------------------------------- INCLUDE AREA ---------------------------------- //

// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //

SimulationModel::SimulationModel()
{
}

SimulationModel::~SimulationModel()
{
}

void SimulationModel::RegisterFile(EnviroSimDataParser * dataReader)
{
	this->m_SensorMount = new SensorMount(dataReader);
	this->m_SensorMount->assignIndividualSensors();
	for (auto i : m_SensorMount->getDisplays())
	{
		i->registerObserver(this->view);
	}
}

SensorMount * SimulationModel::getMount()
{
	return m_SensorMount;
}

void SimulationModel::setController(SimulationController * controller)
{
	this->controller = controller;
}

void SimulationModel::setView(SimulationView * view)
{
	this->view = view;

}


bool SimulationModel::run()
{
	// local, time related variables
	struct _timeb   tStruct;
	double          thisTime;
	double          outputTime;
	double          interval = C_INTERVAL;
	bool            done = false;
	// time initialization
	_ftime(&tStruct);
	thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);
	outputTime = thisTime + interval;

	//int c = 0;
	this->m_SensorMount->collectData();

	while (!done) 
	{
		#pragma region hit check
		int hit;
		char ch;
		hit = _kbhit();
		if (hit)
		{
			ch = _getch();
			if (ch == 's')
			{
				this->view->displaySubscriptions(this->m_SensorMount);
				this->controller->userSelectSubscriptions();
			}
			
		}
		#pragma endregion


		// get time
		_ftime(&tStruct);  
		thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); 		
		// main loop
		if (thisTime >= outputTime)
		{
			cout << "\n\n======================================================================" << endl;
			this->m_SensorMount->collectData();
			this->view->displayMissingSensors();
			outputTime += interval; 
			return true;
		}

	}
	return false;
}



