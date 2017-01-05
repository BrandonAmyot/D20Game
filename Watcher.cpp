//! @file 
//! @author Vance De Waele - 25149436
//! Concrete implementation  of the Observer class. Allows the Character class
//! to be observed in the main method at the end of this file.
//! Included Character.h, Watcher.h, iostream and string. Character.h was
//! necessary to have the class be observed. Watcher.h was included for obvious
//! reasons. String and iostream were included to allow certain functionalities
//! in the main method and the member methods.


#include "Watcher.h"
#include "Character.h"
#include "gfx.h"
#include "dice.h"
#include <string>
#include <iostream>
#include <fstream>
#include "makeCharacter.h"
#include "BullyBuilder.h"
#include "NimbleBuilder.h"
#include "TankBuilder.h"
#include "Item.h"


using namespace std;

//! Default constructor. Does not need definition as it is never used.
Watcher::Watcher() {};

//! Constructor that takes a pointer to a Character(subject) and attaches
//! it to this Watcher class (obeserver).
Watcher::Watcher(Character* hero) {
	_subject = hero;
	_subject->Attach(this);
}

//! Constructor that takes a pointer to a Dice Object and attaches it to a
//! this watcher class
Watcher::Watcher(Dice* dice) {
	_diceSubject = dice;
	_diceSubject->Attach(this);
}

//! Destructor that detaches this Watcher (observer) from its subject.
Watcher::~Watcher() {
	//_subject->Detach(this);
	_diceSubject->Detach(this);
	
}

//! Method that updates observers of the subject. It calls for the
//! update to use the display function to verify the update.
void Watcher::Update() {
	string diceState = _diceSubject->getState();
	outputToFile(diceState);
	//Display();
}

//! Method that displays the attributes of a subject. In this case,
//! it calls on the getScores method of the Character class to show
//! the values stored by the object.
void Watcher::Display() {
	_subject->getScores();
}
//! Method that allows an observer to find out the level of a Character.
//! It uses the attached subject and checks the level it has and returns
//! its value as an integer.
int Watcher::findOutLevel() {
	return _subject->getLevel();
}
//! Method that allows an observer to find out if a Character is still alive.
//! It verifies if the Character object's hit points are above 0 and displays
//! a message in the console to declare if a Character is alive or dead. Though
//! it returns an integer for numercial comparison in tests, it can be refactored
//! in the future to return a boolean or simply nothing.
int Watcher::characterIsDead() {
	if (_subject->getHitPoints() > 0) {
		cout << "Still alive!";
		return 1;
	}
	else
		cout << "They are no longer part of this world.";
	return 0;
}
//! Method used to sort 4 dice rolls made by the dice class and to obtain the summ of the highest 3 scores.
int sortScoresAndSum(int* diceRolls) {
	int temp = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (diceRolls[i] > diceRolls[j]) {
				temp = diceRolls[i];
				diceRolls[i] = diceRolls[j];
				diceRolls[j] = temp;
			}
		}
	}
	int rollSum = diceRolls[0] + diceRolls[1] + diceRolls[2];
	return rollSum;
}
//! Method for creating a Character object using user input.
Character* Watcher:: createHero() {
	
	outputToFile("GAME PHASE: CHARACTER CREATION.");
	
	cout << "*********************************************************************************************************" << endl;
	cout << "                                         CHARACTER BUILDER " << endl;
	cout << "*********************************************************************************************************" << endl;
	cout << "Welcome to the Character builder! Here, you can create your character for the Dungeons and Dragons Game! " << endl;
	cout << "Alternatively, if you already have a saved character, you can load it here before starting the game." << endl;
	string createOrLoad;
	cout << "\nFirst of all, would you like to create or load a character: ";
	cin >> createOrLoad;

	if (createOrLoad == "create") {
		cout << "\nLet's begin by rolling for our character's ABILITY SCORES! These scores determine your hero's abilities" << endl;
		cout << "in the world of Dungeons and Dragons. To get the scores, we will roll a D6 dice 4 times and take the sum" << endl;
		cout << "of the highest 3 rolls as your scores. After the 6 scores are determined, we will assign them to the type" << endl;
		cout << "of character you wish to make. In this case, one of the 3 subclasses of the FIGHTER class." << endl;
		system("PAUSE");

		Dice* heroDice = new Dice();
		int rollScores[4];
		int heroScores[6];
		int k = 0;

		outputToFile("Player Creates Character.");
		cout << ("Do you want to record the Dice rolls for Posterity?(yes/no)") << endl;
		string ans;
		cin >> ans;
		Watcher* diceWatcher;
		if (ans == "yes" || ans == "Yes") {
			diceWatcher = new Watcher(heroDice);
		}

		do {
			cout << "Let's roll! " << endl;
			for (int i = 0; i < 4; i++) {
				rollScores[i] = heroDice->Roll("1d6");
				heroDice->Reset();
			}
			heroScores[k] = sortScoresAndSum(rollScores);
			cout << "Your score is: " << heroScores[k] << endl;
			std::string p = std::to_string(heroScores[k]);
			outputToFile("Total Dice Roll score: " + p);
			k++;
			system("PAUSE");
		} while (k < 6);

		cout << "\nHere are the 6 scores you've rolled: [" << heroScores[0] << ", " << heroScores[1] << ", " << heroScores[2] << ", "
			<< heroScores[3] << ", " << heroScores[4] << ", " << heroScores[5] << "] " << endl;
		cout << "Great! Now we have our six SCORES! But before they can become ABILITY SCORES, we need to know what kind" << endl;
		cout << "of character you would prefer. There a 3 types of fighters to choose from...\n" << endl;
		cout << "The BULLY fighter favors the STRENGTH attribute." << endl;
		cout << "The NIMBLE fighter favors the DEXTERITY attribute." << endl;
		cout << "The TANK fighter favors the CONSTITUTION attribute." << endl;
		cout << "\nNow it's time to choose which type of fighter you want! Enter 1 for BULLY, 2 for NIMBLE or 3 for TANK: ";

		int choice, level;
		cin >> choice;
		while (choice < 1 || choice > 3) {
			cout << "I'm sorry, please try again: ";
			cin >> choice;
			outputToFile("Player Enters Incorrect Input.");
		}
		cout << "Great! Now what level (1-20) would you like the character to be?: ";
		cin >> level;
		while (level < 1 || level > 20) {
			cout << "I'm sorry, please try again: ";
			cin >> level;
			outputToFile("Player Enters Incorrect Input.");
		}
		string heroName;
		cout << "Finally, let's give this hero a name: ";
		cin >> heroName;
		cout << "\nAlright! Let's do this!" << endl;
		outputToFile("Player Creates Character: " + heroName);
		system("PAUSE");

		MakeCharacter maker;
		CharacterBuilder* player1111;

		switch (choice) {
		case 1: {
			player1111 = new BullyBuilder;
			player1111->createNewCharacter(); //! For some reason, without this line of code in each call to a builder, there were null pointers. Added it in.
			maker.setCharacterBuilder(player1111);
			maker.constructCharacter(heroName, level, heroScores);
			outputToFile("Player Creates Bully Character.");
			break;
		}
		case 2: {
			player1111 = new NimbleBuilder;
			player1111->createNewCharacter();
			maker.setCharacterBuilder(player1111);
			maker.constructCharacter(heroName, level, heroScores);
			outputToFile("Player Creates Nimble Character.");
			break;
		}
		case 3: {
			player1111 = new TankBuilder;
			player1111->createNewCharacter();
			maker.setCharacterBuilder(player1111);
			maker.constructCharacter(heroName, level, heroScores);
			outputToFile("Player Creates Tank Character.");
			break;
		}
		default: {
			cout << "Unknown error...shutting down" << endl;
			outputToFile("Unknown error...shutting down");
			system("PAUSE");
			exit(1);
		}
		}

		Character* myHero = maker.getCharacter();
		cout << "Here is your hero: " << endl;
		myHero->getScores();
		cout << "But alas! They are NAKED! They need a few pieces of armor and a weapon! Let's give them some basics..." << endl;
		system("PAUSE");

		Item basicHelm, basicWeapon, basicArmor, basicShield, basicBoots;
		basicHelm = Item("Helm of Basicness", 1, 0, 0, 0, 0, 1, 0, 0);
		basicWeapon = Item("Sword of Wimpiness", 1, 1, 0, 0, 0, 0, 0, 6);
		basicArmor = Item("Breastplate of Coveringness", 1, 0, 1, 0, 0, 0, 0, 1);
		basicShield = Item("Shield of Hilpme Maummy", 1, 0, 1, 0, 0, 0, 0, 2);
		basicBoots = Item("Boots of Sexiness", 1, 0, 0, 0, 1, 0, 0, 5);

		myHero->equipItem(basicHelm);
		myHero->equipItem(basicWeapon);
		myHero->equipItem(basicArmor);
		myHero->equipItem(basicShield);
		myHero->equipItem(basicBoots);

		cout << "That's a bit better!" << endl;
		myHero->getScores();
		myHero->displayWornItems();
		cout << "Thanks for creating a character! Good luck on your quest!" << endl;
		system("PAUSE");

		CFile characterSave;
		characterSave.Open((CString(myHero->getName().c_str())), CFile::modeCreate | CFile::modeWrite);
		CArchive archive(&characterSave, CArchive::store);
		myHero->Serialize(archive);

		ofstream outputfilestream;
		outputfilestream.open("Characters.txt", ios::app);//Switch to make work please
		outputfilestream << myHero->getName() << endl;
		outputfilestream.close();
		outputToFile("Saving Character: " + myHero->getName());
		if (ans == "yes" || ans == "Yes") {
			delete heroDice;
		}


		archive.Close(); characterSave.Close();
		return myHero;
		delete player1111;
	}
	else if (createOrLoad == "load") {
		cout << "\nHere are the names of the saved characters: " << endl;
		string names;
		ifstream inputfilestream;
		inputfilestream.open("Characters.txt");
		while (inputfilestream >> names) {
			cout << names << endl;
		}

		cout << "\nPlease type in the name of the character you wish to load: " << endl;
		string enterFile;
		cin >> enterFile;
		CString loadThis = (CString(enterFile.c_str()));
		CFile loadFile;
		loadFile.Open((loadThis), CFile::modeRead);
		CArchive otherArchive(&loadFile, CArchive::load);

		Character* myHero2 = new Character();
		myHero2->Serialize(otherArchive);
		otherArchive.Close(); loadFile.Close();
		myHero2->getScores();
		myHero2->displayWornItems();
		outputToFile("Player Loads Character: " + myHero2->getName());
		cout << "There's your character! Good luck on your quest!" << endl;
		system("PAUSE");
		return myHero2;
	}
	else {
		cout << "I'm sorry, that selection is invalid. Shutting down...";
		system("PAUSE");
		exit(12);
	}
}

void Watcher::outputToFile(string output) {
	ofstream myFile;
	myFile.open("GrandUnifiedLog.txt", ios::app);
	myFile << output << endl;
	myFile << endl;
	myFile.close();
}
