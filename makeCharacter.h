//! @file 
//! @author Vance De Waele - 25149436
//! Implementation of the Builder Pattern. This is the implementation of a 
//! director for the builder pattern.
#pragma once
#include "CharacterBuilder.h"

class MakeCharacter
{
public:
	void setCharacterBuilder(CharacterBuilder* mc) {                                    
		m_characterBuilder = mc;              
	}
	Character* getCharacter() {
		return m_characterBuilder->getCharacter();
	}
	void constructCharacter(string name, int level, int* rolls) {                                    
		m_characterBuilder->buildName(name);
		m_characterBuilder->buildLevel(level);
		m_characterBuilder->buildDiceRolls(rolls);
		m_characterBuilder->buildStatsFromDiceRolls();
		m_characterBuilder->buildHitPoints();
		m_characterBuilder->buildArmorClass();
		m_characterBuilder->buildAttackBonus();
		m_characterBuilder->buildDamageBonus();
		m_characterBuilder->buildNumAttacks();
		m_characterBuilder->buildLevelDependencies();
		m_characterBuilder->buildItems();
		m_characterBuilder->buildProfBonus();
	}
private:
	CharacterBuilder* m_characterBuilder;
};