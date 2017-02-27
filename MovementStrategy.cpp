//! @file
//! @brief Implementation file for Movement Strategy
//!
#pragma once
#include "Strategy.h"
//! The Movement class strategy pattern 
class MovementStrategy {
private:
	//! A strategy pointer instance vairbale
	Strategy *strategy;
public:
	//! Default constructor
	MovementStrategy() {};
	//! Non-Default constructor
	MovementStrategy(Strategy *initStrategy) {
		this->strategy = initStrategy;
	}
	//! Sets the strategy varbale
	void setStrategy(Strategy *newStrategy) {
		this->strategy = newStrategy;
	}
	//! runs the execute method
	void executeStrategy(Map* map) {
		return this->strategy->execute(map);
	}
};
