// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS FILE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //


//----------------------------------------- PREPROCESSOR -----------------------------------//
#define _CRT_SECURE_NO_WARNINGS
//------------------------------------------------------------------------------------------//


// ---------------------------------------- INCLUDE AREA ---------------------------------- //
// Class header file
#include "Sensor.h"
// -------------------------------------- END INCLUDE AREA -------------------------------- //


// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //

Sensor::Sensor()
{
}

Sensor::~Sensor()
{
}


#pragma region Utility 


void Sensor::registerObserver(DisplayDevice *obs)
{
	m_vObservers.push_back(obs);
	obs->subscriptionCount++;

}



bool Sensor::removeObserver(DisplayDevice *obs)
{
	for (vector<DisplayDevice *>::iterator it = m_vObservers.begin(); it != m_vObservers.end(); it++)
	{
		if (obs == *it)
		{
			m_vObservers.erase(it);
			obs->subscriptionCount--;
			return true;
		}
	}
	return false; 
}


void Sensor::notifyObservers()
{
	for (auto it : m_vObservers)
	{
		it->handleNotification(this);
	}
}

int Sensor::getBroadcasterID()
{
	return ID;
}

double Sensor::getCurrentReading()
{
	return curVal;
}



void Sensor::generateData(void)
{

	this->curVal = this->minVal + (rand() % (int)(this->maxVal - this->minVal));

}
#pragma endregion


#pragma region getters
double Sensor::getDataReading()
{
	return curVal;
}

char * Sensor::getType()
{
	return type;
}

char * Sensor::getMaterial()
{
	return material;
}

char * Sensor::getUnits()
{
	return units;
}
int& Sensor::getID()
{
	return ID;
}
double & Sensor::getMin()
{
	return minVal;
}
double & Sensor::getMax()
{
	return maxVal;
}
#pragma endregion

