//! @file
//! @author Tarik Azzouni - 27013701
//! @brief Implementation file for FriendlyStrategy
//!
#pragma once
#include "Strategy.h"


//! The friendly class strategy pattern
class FriendlyStrategy : public Strategy {
public:
	//! executes the monsterMove method
	void execute(Map* map) {
		map->friendlyMove();
	}
};