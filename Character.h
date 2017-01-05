//! @file 
//! @author Vance De Waele - 25149436
//! Character class header file. The file has had a few methods added in to deal with the
//! needs of the Builder Pattern as well as the level-dependent requirements of this assignment.

#pragma once
#include "Subject.h"
#include <string>
#include "dice.h"
#include "stdfxs.h"
#include <fstream>
#include <afx.h>
using namespace std;

class Character : public Subject, public CObject {
public:

	//! *************************************************************************************************************************
	//! CONSTRUCTORS AND DESTRUCTORS
	//! *************************************************************************************************************************

	//! Default for serialization.
	Character();
	
	//! A constructor.
	//!	Randomly generates the Ability Scores while still taking in a level
	//! \param integer lvl to determine the level
	Character(int lvl);	

	//! A destructor.
	~Character();
	
	//! A constructor.
	//!	Takes in a string, 7 integers - level and 6 dice scores.
	//! \param string name to set the character's name
	//! \param int lvl to determine the level
	//! \param int s to determine strength
	//! \param int d to determine dexterity
	//! \param int c to determine constitution
	//! \param int i to determine intelligence
	//! \param int w to determine wisdom
	//! \param int h to determine charisma
	Character(string name, int lvl, int s, int d, int c, int i, int w, int h);
	
	//! *************************************************************************************************************************
	//! MUTATORS
	//! *************************************************************************************************************************

	//! Setter to specify a Character's name.
	void setName(string givenName) { name = givenName; }
	//! Method that sets level of the character.
	void setLevel(int lvl) { level = lvl; }
	//! Method that sets hit points
	void setHitPoints(int health) { hitPoints = health; }
	//! Sets a specific number for expPoints
	void setSpecificExp(int exp) { expPoints = exp; }
	//! Setter to set strength and its modifier
	//! \param int to determine strength
	void setStrength(int s);	
	//! Setter to set dexterity and its modifier
	//! \param int to determine dexterity
	void setDexterity(int d);	
	//! Setter to set constituion and its modifier
	//! \param int to determine constitution
	void setConstitution(int c);	
	//! Setter to set intelligence and its modifier
	//! \param int to determine intelligence
	void setIntelligence(int i);	
	//! Setter to set wisdom and its modifier
	//! \param int to determine wisdom
	void setWisdom(int w);	
	//! Setter to set charisma and its modifier
	//! \param int to determine charisma
	void setCharisma(int h);	
	//! Setter to set experience points
	//! \param int which represents the level of the character
	void setLevelDependencies(int);
	//! Method to set armor class.
	void setArmorClass() { armorClass = 10 + heroModifiers[1]; }
	//! Method to allow a specific armor class value to be passed in.
	void setArmorClass(int arm) { armorClass = arm; }	
	//! Method to set attack bonus.
	void setAttackBonus() { attackBonus = heroModifiers[0]; }	
	//! Method to set damage bonus.
	void setDamageBonus() { damageBonus = heroModifiers[0]; }		
	//! Method to set the number of attacks a Character has.
	void setNumAttacks();
	//! Method that sets the proficiency bonus
	void setProfBonus();
	//! Method to conserve the initial roll values in creating a Character.
	void setDiceRolls(int*);
	//! Method for setting stats from loading a character
	void setStatsFromLoad();

	//! *************************************************************************************************************************
	//! ACCESSORS
	//! *************************************************************************************************************************

	//! Method to return the name of the Character created.
	//! \return name attribute
	string getName() { return name; }
	//! Method to return the level of a character.
	//! \return level attribute
	int getLevel() { return level; }
	//! Method to return the hit points of a character.
	//! \return hitPoints attribute
	int getHitPoints() { return hitPoints; }
	//! Method to return the experience points of a character.
	//! \return expPoints attribute
	int getExpPoints() { return expPoints; }
	//! Method to return the strength attribute of the character
	//! \return strength
	int getStrength() { return heroAbility[0]; }
	//! Method to return the dexterity attribute of the character
	//! \return dexterity
	int getDexterity() { return heroAbility[1]; }	
	//! Method to return the constitution attribute of the character
	//! \return constitution
	int getConstitution() { return heroAbility[2]; }
	//! Method to return the intelligence attribute of the character
	//! \return intelligence
	int getIntelligence() { return heroAbility[3]; }	
	//! Method to return the wisdom attribute of the character
	//! \return wisdom
	int getWisdom() { return heroAbility[4]; }
	//! Method to return the charisma attribute of the character
	//! \return charisma
	int getCharisma() { return heroAbility[5]; }
	//! Method to return the armor class of the character
	int getArmorClass() { return armorClass; }
	//! Method to return the attack bonus of the character
	int getAttackBonus() { return attackBonus; }
	//! Method to return the damage bonus of the character
	int getDamageBonus() { return damageBonus; }
	//! Method to return the number of attacks of the character
	int getNumAttacks() { return numAttacks; }
	//! Method that return the proficiency bonus of the character
	int getProfBonus(){ return profBonus; }
	//! Method to display the various attributes of the character
	//! \return Displays attributes
	void getScores();
	//! Method used to obtain a specific roll of dice.
	int getDiceRolls(int x) { return diceRolls[x]; }	
	//! Method to return a given modifier of the character
	//! \return modifier requested
	int getModifier(int x) { return heroModifiers[x]; }	
	
	
	
	
	//! *************************************************************************************************************************
	//! OTHER METHODS
	//! *************************************************************************************************************************

	//! Method to level up a character based on experience acquired.
	void levelUp();
	//! Method to determine the validity of a character.
	//! \return boolean that states validity of a character.
	bool isValidCharacter();	
	//! Method to modify the hit points of a character post-attack.
	//! Please note that this method was renamed from 'getHit' to avoid confusion.
	//! \param int representing the damage taken by a character.
	void receiveAttack(int);
	//! Necessary for Serialization of the class.
	void Serialize(CArchive& archive);
	//! Method to set the Items carried by a hero to default values
	void setItems();
	//! Adds an item to the inventory
	void addToInventory(Item& item);
	//!Displays the inventory of the character
	void displayInventory();
	//! Equips an item from the inventory
	void equipInventory();
	//! Equips a given item
	void equipItem(Item& item);
	//! Removes an item
	void removeItem();
	//! Displays Items worn by a hero.
	void displayWornItems();
	//! Method that updates the modifiers of a hero
	void updateMods(int x);
	//! Method to update modifiers on removal of item from a hero
	void negativeMods(int x);
	//! Method to see if character is alive
	boolean isAlive();
	//! Method to give hero experience points
	int giveHeroExp() { return expPoints; };

	//! Method to output to a TextFile
	void outputToFile(string output);

	//! *************************************************************************************************************************
	//! OPERATOR OVERLOADS
	//! *************************************************************************************************************************

	friend ostream& operator<<(ostream&, const Character&);
		
	//! *************************************************************************************************************************
	//! ATTRIBUTES
	//! *************************************************************************************************************************
	
private:
	string name;//! String to represent the name of a character.
	int level;//! Represents the level of a character
	int hitPoints;//! Represents the hit points of a character
	int expPoints;//! Represents the experience points of a character
	int armorClass;//! Representes the armor class of a character
	int attackBonus;//! Represents the attack bonus of a character
	int damageBonus;//! Represents the damage bonus of a character
	int heroAbility[6];//! 0:Strength; 1:Dexterity; 2:Constitution; 3:Intelligence; 4:Wisdom; 5:Charisma
	int heroModifiers[6];//! Modifiers for each of the ability scores. Indices represent same traits as heroAbilityScores
	int diceRolls[6];//! Array of dice roll values obtained from character ccreation
	int numAttacks;//! Represents the number of attacks a Character can make.
	int profBonus;
	Dice charDice; //! Dice object used in certain methods of the class.
	Item backPack[7];//! Contains 7 additional items picked up by the hero.
	Item equippedItems[7]; //! 0:Helmet; 1:Armor; 2:Shield; 3:Ring; 4:Belt; 5:Boots; 6:Weapon;

protected:
	DECLARE_SERIAL(Character)

};
