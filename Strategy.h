//! @file
//! @author Tarik Azzouni - 27013701
//! @brief Implementation file for the Strategy class which other classes inherit from
//!
#pragma once
#include "Map.h"
//! The startegy class in which FriendlyStrategy, AgressorStrategy, and MovementStrategy inherit from.
class Strategy {
public:
	//! the abstract execute method
	virtual void execute(Map* map) = 0;
};