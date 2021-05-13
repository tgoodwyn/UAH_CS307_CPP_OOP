#include "DisplayFactory.h"

DisplayFactory* DisplayFactory::instance;

void DisplayFactory::createSystemDisplays(EnviroSimDataParser * dataReader, SensorMount * mount)
{
	DisplayDevice *display = new DisplayDevice();

	while (dataReader->getDisplayData(
		display->type, display->IDs, &display->IDCount))
	{
		mount->m_vSetOfDisplays.push_back(display);
		display = new DisplayDevice();
	}
}

DisplayFactory * DisplayFactory::getInstance()
{
	if (!instance)
		instance = new DisplayFactory;
	return instance;
}

DisplayFactory::DisplayFactory()
{
}

