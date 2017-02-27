//! @file
//! @brief Implementation file for the Human Strategy 
#pragma once
#include "Strategy.h"

//! The friendly class strategy pattern
class HumanStrategy : public Strategy {
public:
	//! The execute method
	void execute(Map* map) 
	{
		map->move();
	}
};
