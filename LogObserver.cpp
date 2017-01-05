#include "LogObserver.h"

LogObserver::LogObserver() {};

LogObserver::LogObserver(Map* m, Character* c, Dice* d)
{
	sMap = m;
	sMap->Attach(this);
	sCharacter = c;
	sCharacter->Attach(this);
	sDice = d;
	sDice->Attach(this);
};
LogObserver::~LogObserver()
{
	sMap->Detach(this);
	sCharacter->Detach(this);
	sDice->Detach(this);
};
void LogObserver::Update()
{
	display();
}

void LogObserver::display()
{

}