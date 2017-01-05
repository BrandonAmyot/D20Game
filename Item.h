#pragma once

#include <string>
#include <iostream>
#include <afx.h>

using namespace std;
//!Class to create different types of items



class Item : public CObject
{

private:

	//! Instance Variables for enchantments
	std::string itemName;
	int armorClass;
	int strengthEnchantment;
	int constitutionEnchantment;
	int wisdomEnchantment;
	int IQenchantment;
	int charismaEnchantment;
	int dexterityEnchantment;

	int damageBonus;
	int attackBonus;

	

	int itemID;

	
public:


	Item();
	Item(int x);
	Item(std::string name, int armor, int strength, int constitution, int dexterity, int charisma, int IQ, int wisdom, int itemID);
	virtual ~Item();

	//!Setters & Getters for enchantments
	void setItemName(std::string setName);
	std::string getItemName();

	void setArmorClass(int setArmor);
	int getArmorClass() { return armorClass; };

	void setStrengthMod(int setStrength);
	int getStrengthMod() { return strengthEnchantment; };

	void setConstitutionMod(int setConst);
	int getConstitutionMod(){return constitutionEnchantment;};

	void setWisdomMod(int setWisdom);
	int getWisdomMod() { return wisdomEnchantment; };

	void setIQMod(int setIQ);
	int getIQMod() { return IQenchantment; };

	void setCharismaMod(int setCharisma);
	int getCharismaMod() { return charismaEnchantment; };

	void setDexterityMod(int setDexterity);
	int getDexterityMod() { return dexterityEnchantment; };

	

	void display();

	int getAttackBonus() { return attackBonus; };
	void setAttackBonus(int attack);
	
	int getDamageBonus() { return damageBonus; };
	void setDamageBonus(int damage);


	int getItemID();
	void setItemID(int setID);

	


	void Serialize(CArchive& archive);

	friend ostream& operator<<(ostream&, const Item&);
	const Item& Item::operator=(const Item& item);

	Item* itemCreation();
	
protected:
	DECLARE_SERIAL(Item)
};

