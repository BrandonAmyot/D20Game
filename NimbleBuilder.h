//! @file 
//! @author Vance De Waele - 25149436
//! Implementation of the Builder Pattern. This is the implementation of a 
//! concrete builder.
#pragma once
#include "CharacterBuilder.h"

class NimbleBuilder : public CharacterBuilder {
	
	virtual void buildName(string given) {
		m_character->setName(given);
	}
	virtual void buildLevel(int lvl) {
		m_character->setLevel(lvl);
	}
	virtual void buildDiceRolls(int* rolls) {
		m_character->setDiceRolls(rolls);
	}
	virtual void buildStatsFromDiceRolls() {
		m_character->setStrength(m_character->getDiceRolls(2));
		m_character->setDexterity(m_character->getDiceRolls(0));
		m_character->setConstitution(m_character->getDiceRolls(1));
		m_character->setIntelligence(m_character->getDiceRolls(3));
		m_character->setWisdom(m_character->getDiceRolls(5));
		m_character->setCharisma(m_character->getDiceRolls(4));
	}
	virtual void buildHitPoints() {
		m_character->setHitPoints(10);
	}
	virtual void buildArmorClass() {
		m_character->setArmorClass();
	}
	virtual void buildAttackBonus() {
		m_character->setAttackBonus();
	}
	virtual void buildDamageBonus() {
		m_character->setDamageBonus();
	}
	virtual void buildNumAttacks() {
		m_character->setNumAttacks();
	}
	virtual void buildLevelDependencies() {
		m_character->setLevelDependencies(m_character->getLevel());
	}
	virtual void buildItems() {
		m_character->setItems();
	}
	virtual void buildProfBonus(){
		m_character->setProfBonus();
	}
};