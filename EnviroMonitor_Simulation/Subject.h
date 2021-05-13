#pragma once
#include "Observer.h"
// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //
class Observer;
class Subject
{
public:
	vector<Observer *> m_vObservers;
	int broadcasterID;
	double currentReading;
public:
	Subject();									
	~Subject();									
	virtual void registerObserver(Observer *obs);
	virtual bool removeObserver(Observer *obs);		
	virtual void notifyObservers();			
	virtual int getBroadcasterID();
	virtual double getCurrentReading();

};

