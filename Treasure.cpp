//! Treasure Implementation File

#include "Treasure.h"
#include <afx.h>



//! Defualt Constructor
Treasure::Treasure()
{
}

// Destructor
Treasure::~Treasure()
{
}

// A method to get items from Chest
Item* Treasure::getItemFromTreasure() 
{
	return treasureItems[0];
}

//! Method to determin random item;
void Treasure::setTreasureContents() {

	srand(time(NULL));
	int random = (rand() % 8 + 1);
	switch (random) {
	case 1:
	{loot = new Item("Light Armor",2,0,0,0,0,0,0,1); break; }
	case 2:
	{loot = new Item("Medium Belt",0,2,1,0,0,0,0,4); break; }
	case 3:
	{loot = new Item("Quick Boots", 1,0,0,2,0,0,0,5); break; }
	case 4:
	{loot = new Item("Helm of Suffering",2,0,0,0,0,2,1,0 ); break; }
	case 5:
	{loot = new Item("Fancy Ring",1,2,2,1,2,0,1,3); break; }
	case 6:
	{loot = new Item("Sheild of Blocking",2,0,0,0,0,0,0,2); break; }
	case 7:
	{loot = new Item("Sword of Pummeling", 0,0,0,0,0,0,0,6); break; }
	default:
	{	loot = NULL;
		delete loot;
		cout << "No Items Here!" << endl; }
	}
	treasureItems[0] = loot;
}

//! method to display the chest contents
void Treasure::display() {
	cout << "CHEST CONTENTS:" << endl;
	for (int i = 0; i < treasureItems.size(); i++) {

		if (treasureItems.at(i) == NULL) {
			continue;
		}
		if (treasureItems.at(i) != NULL) {
			cout << "Item #" << (i + 1) << " " << treasureItems[i]->getItemName() << endl;
		}

	}
}




