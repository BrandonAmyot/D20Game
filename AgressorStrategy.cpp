//! @file
//! @author Tarik Azzouni - 27013701
//! @brief Implementation file for Agressor Strategy
//!
#pragma once
#include "Strategy.h"
//! The aggressor class strategy pattern
class AgressorStrategy : public Strategy {
public:
	//! executes the monsterMove method
	void execute(Map* map) {
		map->monsterMove();
	}
};