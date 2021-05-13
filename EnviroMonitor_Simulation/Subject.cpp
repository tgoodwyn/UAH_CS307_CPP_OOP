#include "Subject.h"
// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //
Subject::Subject()
{
}

Subject::~Subject()
{
}

void Subject::registerObserver(Observer * obs)
{
}

bool Subject::removeObserver(Observer * obs)
{
	return false;
}

void Subject::notifyObservers()
{
}

int Subject::getBroadcasterID()
{
	return 0;
}



double Subject::getCurrentReading()
{
	return 0.0;
}
