//! @file
//! Implementation of the Character class. Modified the class by adding some methods
//! needed for the implementation of the Builder Pattern and the various requirements
//! of this assignment.

#include <iostream>
#include "Character.h"
#include <cstddef>
#include "dice.h"
using namespace std;
IMPLEMENT_SERIAL(Character, CObject, 1);

//! Default necessary for Serialization
Character::Character() {
	
}
//! Constructor that takes 7 integers (provided by dice roll and inputted level) & assigns them
//! to the ability scores for the hero. The modifiers are calculated with the rule that
//! they are equal to the (score-10)/2 and rounding down (taken care of by int divivsion)
Character::Character(string givenName, int lvl, int s, int d, int c, int i, int w, int h) {
	name = givenName;
	level = lvl;
	setStrength(s);
	setDexterity(d);
	setConstitution(c);
	setIntelligence(i);
	setWisdom(w);
	setCharisma(h);
	setHitPoints(10);
	setArmorClass();
	setAttackBonus();
	setDamageBonus();
	setProfBonus();
	setLevelDependencies(lvl);
	setNumAttacks();
}
//! Destructor that now deletes and nullifies the pointer members
Character::~Character() { 
	
}

//! Method used to level up a Character.
void Character::levelUp() {
	charDice = Dice();
	if (level == 1 && 300 <= expPoints && expPoints < 900) {
		level = 2; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 2 && 900 <= expPoints && expPoints < 2700) {
		level = 3; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 3 && 2700 <= expPoints && expPoints < 6500) {
		level = 4; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 4 && 6500 <= expPoints && expPoints < 14000) {
		level = 5; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 5 && 14000 <= expPoints && expPoints < 23000) {
		level = 6; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 6 && 23000 <= expPoints && expPoints < 34000) {
		level = 7; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 7 && 34000 <= expPoints && expPoints < 48000) {
		level = 8; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 8 && 48000 <= expPoints && expPoints < 64000) {
		level = 9; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 9 && 64000 <= expPoints && expPoints < 85000) {
		level = 10; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 10 && 85000 <= expPoints && expPoints < 100000) {
		level = 11; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 11 && 100000 <= expPoints && expPoints < 120000) {
		level = 12; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 12 && 120000 <= expPoints && expPoints < 140000) {
		level = 13; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 13 && 140000 <= expPoints && expPoints < 165000) {
		level = 14; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 14 && 165000 <= expPoints && expPoints < 195000) {
		level = 15; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 15 && 195000 <= expPoints && expPoints < 225000) {
		level = 16; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 16 && 225000 <= expPoints && expPoints < 265000) {
		level = 17; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 17 && 265000 <= expPoints && expPoints < 305000) {
		level = 18; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 18 && 305000 <= expPoints && expPoints < 355000) {
		level = 19; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;
	}
	if (level == 19 && 355000 <= expPoints) {
		level = 20; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]); attackBonus++;		
	}
	setNumAttacks();
	setProfBonus();
	outputToFile("Character: " + getName() + " levels up!");
}

//! Method that sets score for strength and its modifier
void Character::setStrength(int s) {
	heroAbility[0] = s;
	heroModifiers[0] = (s - 10) / 2;
}
//! Method that sets score for dexterity and its modifier
void Character::setDexterity(int d) {
	heroAbility[1] = d;
	heroModifiers[1] = (d - 10) / 2;
}
//! Method that sets score for constitution and its modifier
void Character::setConstitution(int c) {
	heroAbility[2] = c;
	heroModifiers[2] = (c - 10) / 2;
}
//! Method that sets score for intelligence and its modifier
void Character::setIntelligence(int i) {
	heroAbility[3] = i;
	heroModifiers[3] = (i - 10) / 2;
}
//! Method that sets score for wisdom and its modifier
void Character::setWisdom(int w) {
	heroAbility[4] = w;
	heroModifiers[4] = (w - 10) / 2;
}
//! Method that sets score for charisma and its modifier
void Character::setCharisma(int h) {
	heroAbility[5] = h;
	heroModifiers[5] = (h - 10) / 2;
}
//! Method that sets the number of attacks for a Character based on its level.
void Character::setNumAttacks() {
	if (level >= 1 && level < 6)
		numAttacks = 1;
	if (level >= 6 && level < 11)
		numAttacks = 2;
	if (level >= 11 && level < 16)
		numAttacks = 3;
	if (level >= 16 && level <= 20)
		numAttacks = 4;
}
void Character::setProfBonus(){
	if (level >= 1 && level <= 4)
		profBonus = 2;
	if (level >= 5 && level <= 8)
		profBonus = 3;
	if (level >= 9 && level <= 12)
		profBonus = 4;
	if (level >= 13 && level <= 16)
		profBonus = 5;
	if (level >= 17 && level <= 20)
		profBonus = 6;
}
//! Method that takes in an array integers representing dice rolls and sorts them in decreasing order. The rolls are stored
//! in the 'diceRolls' array.
void Character::setDiceRolls(int* rolls) {
	for (int i = 0; i < 6; i++) {
		diceRolls[i] = rolls[i];
	}
	int temp=0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (diceRolls[i] > diceRolls[j]) {
				temp = diceRolls[i];
				diceRolls[i] = diceRolls[j];
				diceRolls[j] = temp;
			}
		}
	}
}

//! Method that sets the experience points based on level of the hero. This should ONLY be invoked in the initial creation of a 
//! Character. For a modification of a Character while questing, the levelUp method should be used.
void Character::setLevelDependencies(int lvl) {
	charDice = Dice();
	switch (lvl) {
		case 1: {expPoints = 0; hitPoints = 10 + heroModifiers[2]; break; }
		case 2: {expPoints = 300; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 2; attackBonus += 1; break; }
		case 3: {expPoints = 900; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 3; attackBonus += 2; break; }
		case 4: {expPoints = 2700; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 4; attackBonus += 3; break; }
		case 5: {expPoints = 6500; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 5; attackBonus += 4; break; }
		case 6: {expPoints = 14000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 6; attackBonus += 5; break; }
		case 7: {expPoints = 23000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 7; attackBonus += 6; break; }
		case 8: {expPoints = 34000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 8; attackBonus += 7; break; }
		case 9: {expPoints = 48000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 9; attackBonus += 8; break; }
		case 10: {expPoints = 64000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 10; attackBonus += 9; break; }
		case 11: {expPoints = 85000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 11; attackBonus += 10; break; }
		case 12: {expPoints = 100000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 12; attackBonus += 11; break; }
		case 13: {expPoints = 120000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 13; attackBonus += 12; break; }
		case 14: {expPoints = 140000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 14; attackBonus += 13; break; }
		case 15: {expPoints = 165000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 15; attackBonus += 14; break; }
		case 16: {expPoints = 195000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 16; attackBonus += 15; break; }
		case 17: {expPoints = 225000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 17; attackBonus += 16; break; }
		case 18: {expPoints = 265000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 18; attackBonus += 17; break; }
		case 19: {expPoints = 305000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 19; attackBonus += 18; break; }
		case 20: {expPoints = 355000; hitPoints += (charDice.Roll("1d10") + heroModifiers[2]) * 20; attackBonus += 19; break; }
		default: {cout << "Error in creating character"; exit(11); }
	}
}
//! Method that checks if the character is valid.
bool Character::isValidCharacter() {
	for (int i = 0; i <= 5; i++){
		if (heroAbility[i] < 3 || heroAbility[i]>18) {
			cout << "Bad character";
			return false;
		}
	}
	return true;
}
//! Method that allows a character to receive a hit, modifying its hit points
//! New feature: method now notifies the observer. Identified in code below.
void Character::receiveAttack(int hit) {
	hitPoints = hitPoints - hit;
	Notify(); //Subject method
	
}
boolean Character::isAlive() {
	if (hitPoints > 0)
		return true;
	else
		return false;
}
//! Method for serialization
void Character::Serialize(CArchive& archive) {
	CObject::Serialize(archive);

	if (archive.IsStoring()) {
		archive << CString(name.c_str());
		archive << level;
		archive << hitPoints;
		archive << expPoints;
		archive << attackBonus;
		archive << damageBonus;
		for (int i = 0; i < 6; i++) {
			archive << heroAbility[i];
		}
		for (int i = 0; i < 7; i++) {
			backPack[i].Serialize(archive);
		}
		for (int i = 0; i < 7; i++) {
			equippedItems[i].Serialize(archive);
		}
	}		
	else {
		CString csName;		
		archive >> csName;
		CT2CA pszConvertedAnsiString(csName);
		std::string strStd(pszConvertedAnsiString);
		name = strStd;

		archive >> level;
		archive >> hitPoints;
		archive >> expPoints;
		archive >> attackBonus;
		archive >> damageBonus;
		for (int i = 0; i < 6; i++) {
			archive >> heroAbility[i];			
		}
		setStatsFromLoad();
		setNumAttacks();
		setArmorClass();
		setProfBonus();
		for (int i = 0; i < 7; i++) {
			backPack[i].Serialize(archive);
		}
		for (int i = 0; i < 7; i++) {
			equippedItems[i].Serialize(archive);
			updateMods(i);
		}		
	}	
}
//! Simple method used in the driver to output the properties of a character including
//! modifiers that are determined by the scores entered or generated.
void Character::getScores() {
	cout << "Name: " << name << endl;
	cout << "Level: " << level << endl; // Name output needed
	cout << "Hit Points: \t" << hitPoints << endl;
	cout << "Experience: \t" << expPoints << endl;
	cout << "Strength: \t" << heroAbility[0] << "\tModifier: " << heroModifiers[0] << endl;
	cout << "Dexterity: \t" << heroAbility[1] << "\tModifier: " << heroModifiers[1] << endl; 
	cout << "Constitution: \t" << heroAbility[2] << "\tModifier: " << heroModifiers[2] << endl;
	cout << "Intelligence: \t" << heroAbility[3] << "\tModifier: " << heroModifiers[3] << endl;
	cout << "Wisdom: \t" << heroAbility[4] << "\tModifier: " << heroModifiers[4] << endl;
	cout << "Charisma: \t" << heroAbility[5] << "\tModifier: " << heroModifiers[5] << endl;
	cout << "Armor Class: \t" << armorClass << endl;
	cout << "Attack Bonus: \t" << attackBonus << endl;
	cout << "Damage Bonus: \t" << damageBonus << endl;
	cout << "Prof. Bonus: \t" << profBonus << endl;
	cout << "Num. attacks: \t" << numAttacks << endl;
}
//! Overloading of the '<<' operator necessary for serialization
ostream& operator<<(ostream& out, Character& buddy)
{	out << "Name: " << buddy.getName() << endl;
	out << "Level: " << buddy.getLevel() << endl;
	out << "Hit Points: \t" << buddy.getHitPoints() << endl;
	out << "Experience: \t" << buddy.getExpPoints() << endl;
	out << "Strength: \t" << buddy.getStrength() << "\tModifier: " << buddy.getModifier(0) << endl;
	out << "Dexterity: \t" << buddy.getDexterity() << "\tModifier: " << buddy.getModifier(1) << endl;
	out << "Constitution: \t" << buddy.getConstitution() << "\tModifier: " << buddy.getModifier(2) << endl;
	out << "Intelligence: \t" << buddy.getIntelligence() << "\tModifier: " << buddy.getModifier(3) << endl;
	out << "Wisdom: \t" << buddy.getWisdom() << "\tModifier: " << buddy.getModifier(4) << endl;
	out << "Charisma: \t" << buddy.getCharisma()<< "\tModifier: " << buddy.getModifier(5) << endl;
	out << "Armor Class:\t" << buddy.getArmorClass() << endl;
	out << "Attack Bonus: \t" << buddy.getAttackBonus() << endl;
	out << "Damage Bonus: \t" << buddy.getDamageBonus() << endl;
	out << "Prof. Bonus: \t" << buddy.getProfBonus() << endl;
	out << "Num. attacks: \t" << buddy.getNumAttacks() << endl;
	return out;
}
//! Method that adds an item to the inventory of a hero
//This needs to be reworked.
void Character::addToInventory(Item& item) {
	int i = 0;
	while (backPack[i].getItemName() != "Nothing") {
		i++;
		if (i >= 7){
			cout << "No more room! Discard Item? (Type y/n): ";
			string answer;
			cin >> answer;
			if (answer == "y"){
				cout << "Gonna throw this thing away then..." << endl;
				break;
			}
			if (answer == "n"){
				cout << "/nWell we gotta get rid of something! SHOW ME WHAT YOU GOT!" << endl;
				displayInventory();
				cout << "/nWhat are we ditching from here then? Enter the slot number: ";
				int index;
				cin >> index;
				backPack[index - 1] = Item(0);
				i = 0;
			}
		}
		if (i < 7 && backPack[i].getItemName()=="Nothing"){
			backPack[i] = item;
			break;
		}
	}
	if (backPack[i].getItemName() == "Nothing"){
		backPack[i] = item;
	}
	outputToFile("Player Adds an Item to Inventory.");
}

//!Method that equips an item from the inventory
void Character::equipInventory() {
	int index;
	cout << "ENTER THE ITEM # YOU WANT TO EQUIP" << endl;
	displayInventory();
	cin >> index;
	if (index == 0 || index > 7) {
		cout << "Item Does not Exist" << endl;
		return;
	}
	int checkSpace = 0;
	for (int i = 0; i < 6; i++){
		if (equippedItems[i].getItemID() == backPack[index - 1].getItemID()){
			checkSpace = i;
		}
	}
	if (equippedItems[checkSpace].getItemID() == backPack[index-1].getItemID() && equippedItems[checkSpace].getItemName()!="Nothing"){
		cout << "You're already wearing something there! Replace it with the item from your backpack? (y/n)" << endl;
		string answer;
		cin >> answer;
		if (answer == "y"){
			negativeMods(checkSpace);
			equipItem(backPack[index - 1]);
			backPack[index - 1] = Item(0);
		}
		if (answer == "n"){
			cout << "Well we'll just leave things as they are then" << endl;
		}
	}
	else {
		equippedItems[checkSpace] = backPack[index - 1];
		backPack[index - 1] = Item(0);
		updateMods(checkSpace);
		outputToFile("Player Equips an Item to From Inventory.");
	}	
}
//! Method that displays the items in the inventory
void Character::displayInventory() {
	cout << "YOU HAVE THE FOLLOWING ITEMS IN YOUR BACKPACK:" << endl;
	for (int i = 0; i < 7; i++) {
		cout << "SLOT #" << (i + 1) << " " << backPack[i].getItemName() << endl;
	}
}
//! Method that allows an item to be equipped
void Character::equipItem(Item& item) {
	int itemID = item.getItemID();
	switch (itemID) {
		case 0:	{equippedItems[0] = item; break; }
		case 1: {equippedItems[1] = item; break; }
		case 2: {equippedItems[2] = item; break; }
		case 3: {equippedItems[3] = item; break; }
		case 4: {equippedItems[4] = item; break; }
		case 5: {equippedItems[5] = item; break; }
		case 6: {equippedItems[6] = item; break; }
		default: cout << "Invalid Item" << endl;
	}
	updateMods(itemID);
	outputToFile("Player Equips an Item.");
}
//! Method that removes an item
void Character::removeItem() {
	int index;
	cout << "ENTER THE SLOT NUMBER YOU WOULD LIKE TO REMOVE:" << endl;
	displayWornItems();
	cin >> index;
	if (index == 0 || index > 7) {
		cout << "ITEM DOES NOT EXIST" << endl;
		return;
	}
	negativeMods(index - 1);
	addToInventory(equippedItems[index - 1]);
	equippedItems[index - 1] = Item(index-1);
	outputToFile("Player Removes an Item to Inventory");
}
//! Method that displays the items worn by a character.
void Character::displayWornItems() {
	cout << "YOU ARE WEARING THE FOLLOWING ITEMS:" << endl;
	for (int i = 0; i < 7; i++) {
		cout << "SLOT #" << (i + 1) << " " << equippedItems[i].getItemName() << endl;
	}
}
//! Method to update the modifiers when an item is worn.
void Character::updateMods(int x) {
		heroModifiers[0] += equippedItems[x].getStrengthMod();
		heroModifiers[1] += equippedItems[x].getDexterityMod();
		heroModifiers[2] += equippedItems[x].getConstitutionMod();
		heroModifiers[3] += equippedItems[x].getIQMod();
		heroModifiers[4] += equippedItems[x].getWisdomMod();
		heroModifiers[5] += equippedItems[x].getCharismaMod();
		armorClass += equippedItems[x].getArmorClass();
		damageBonus = heroModifiers[0];
}
//! Method to update the modifiers when an item is worn.
void Character::negativeMods(int x) {
	heroModifiers[0] -= equippedItems[x].getStrengthMod();
	heroModifiers[1] -= equippedItems[x].getDexterityMod();
	heroModifiers[2] -= equippedItems[x].getConstitutionMod();
	heroModifiers[3] -= equippedItems[x].getIQMod();
	heroModifiers[4] -= equippedItems[x].getWisdomMod();
	heroModifiers[5] -= equippedItems[x].getCharismaMod();
	armorClass -= equippedItems[x].getArmorClass();
	damageBonus = heroModifiers[0];
}

//! Method that instantiates the Items to a default value in the Character.
void Character::setItems() {
	for (int i = 0; i < 7; i++)
		equippedItems[i] = Item(i);
	for (int i = 0; i < 7; i++)
		backPack[i] = Item(0);
}
//Method used in conjunction wiht the loading process to set stats that are not saved
void Character::setStatsFromLoad(){
	for (int i = 0; i < 6; i++){
		heroModifiers[i] = (heroAbility[i] - 10) / 2;
	}
}
void Character::outputToFile(string output) {
	ofstream myFile;
	myFile.open("GrandUnifiedLog.txt", ios::app);
	myFile << output << endl;
	myFile << endl;
	myFile.close();
}
