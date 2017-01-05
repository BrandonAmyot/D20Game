//! @file 
//! @author Vance De Waele - 25149436
//! Implementation of the Builder Pattern. This is an abstract class that provides
//! the structure for the various builders implemented.
#pragma once
#include "Character.h"
#include <string>

class CharacterBuilder {

public:
	Character* getCharacter() { return m_character; }
	void createNewCharacter() { m_character = new Character; }
	
	virtual void buildName(string) = 0;
	virtual void buildLevel(int) = 0;
	virtual void buildDiceRolls(int*) = 0;
	virtual void buildStatsFromDiceRolls() = 0;
	virtual void buildHitPoints() = 0;
	virtual void buildArmorClass() = 0;
	virtual void buildAttackBonus() = 0;
	virtual void buildDamageBonus() = 0;
	virtual void buildNumAttacks() = 0;
	virtual void buildLevelDependencies() = 0;
	virtual void buildItems() = 0;
	virtual void buildProfBonus() = 0;
	

protected:
	Character* m_character;
};