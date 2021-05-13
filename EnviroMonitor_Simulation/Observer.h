#pragma once

// STD headers
#include <vector>

#include "Subject.h"
// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //
class Subject;
class Observer
{
public:
	vector<Subject *> m_vSubscriptions;
public:
	Observer();							
	~Observer();						
	virtual void handleNotification(Subject *s);	
};

