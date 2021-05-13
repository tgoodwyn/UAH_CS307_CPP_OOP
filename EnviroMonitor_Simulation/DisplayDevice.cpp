// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS FILE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //


//----------------------------------------- PREPROCESSOR -----------------------------------//
#define _CRT_SECURE_NO_WARNINGS
//----------------------------------------- PREPROCESSOR -----------------------------------//



// ----------------------------------------- INCLUDES ------------------------------------- //
// Class header file
#include "DisplayDevice.h"
// ----------------------------------------- INCLUDES ------------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //

DisplayDevice::DisplayDevice()
{
	
}

DisplayDevice::~DisplayDevice()
{
}

void DisplayDevice::handleNotification(Sensor * s)
{
	this->currentReading = s->getCurrentReading();
	this->broadcasterID = s->getBroadcasterID();
	notifyObservers();
}

int DisplayDevice::getUnsubscribedNumber()
{
	return IDCount - subscriptionCount;
}

void DisplayDevice::registerObserver(SimulationView * obs)
{
	m_vObservers.push_back(obs);
}

bool DisplayDevice::removeObserver(SimulationView * obs)
{
	return false;
}

void DisplayDevice::notifyObservers()
{		
		m_vObservers.at(0)->handleNotification(this);
}


int DisplayDevice::getBroadcasterID()
{
	return this->broadcasterID;
}

double DisplayDevice::getCurrentReading()
{
	return this->currentReading;
}
