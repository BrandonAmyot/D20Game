//! @file 
//! @brief Implementation file for the Map class  
//!
//! The map class which is the main hub for all classes.


#pragma once
#include <afx.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Subject.h"
#include "Character.h"
#include "Gnoll.h"
#include "Goblin.h"
#include "Ogre.h"
#include "Watcher.h"
using namespace std;

//! Class implementing a game map.
class Map : public CObject, public  Subject
{
public:
	//! Needed for MFC serialization.
	DECLARE_SERIAL(Map);
	//! Default constructor.
	Map();
	//! Non=default constructor.
	Map(int row, int col, int startX, int startY, int endX, int endY, CString name,  Character* play);
	//! Destructor.
	~Map();
	//! Getter for the column variable.
	int getCol();
	//! Getter for the row variable.
	int getRow();
	//Getter for the map grid.
	CString** getGrid();
	//void setGrid(char c);
	//! Getter for the startX coordinate.
	int getStartX();
	//! Getter for the startY coordinate.
	int getStartY();
	//! Getter for the endX coordinate.
	int getEndX();
	//! Getter for the endY coordinate.
	int getEndY();
	void setNextName(CString name);
	CString getMapName() { return mapName; };
	//! Fills the map grid.
	void fillCell(int x, int y, string obj);
	//! Checks if the cell in a grid is empty or not.
	bool isOccupied(int x, int y);
	//! Prints the map grid.
	void printMap();
	//! Checks the map to make sure there is a winning path.
	bool validatePath(int x, int y);
	//! Saves a Map object to text file.
	void save();
	//! Loads a Map object from text file.
	Map* load(string name);
	//! Creates a Map objec based on user input, and saves the object.
	static Map*  createMap(Character* player, int num, CString name);
	//! Loads a Map object from a text file, edits it based on user input and saves it back to a text file.
	static Map* editMap(Map* map1);
	//! Serializes a Map object.
	void Serialize(CArchive& archive);
	//! Moves a player on the Map grid
	void move();
	//! Moves a monster on the Map grid
	void monsterMove();
	//! Moves an NPC on the map grid towards the player
	void friendlyMove();
	//! Helper method for monsterMove();
	void moveHelper(int playerX, int playerY, int monsterX, int monsterY, CString monster);
	//! Operates the turns
	void turnEngine(Map* map);

	//! Operates the combat sequences
	void battle(int playerX, int playerY);
	//! Human attack method
	void attack(int monsterX, int monsterY);
	//! Returns the map object's Character instance variable
	Character* getPlayer() { return player; };

	//! Sets the Character instance variable
	void setPlayer(Character* pl) { player = pl; };
	//! Returns the boolean value of hasNextMap
	bool getHasNextMap();
	void setHasNextMap(bool val);
	//! Returns a map's next name
	CString getNextName() { return nextName; };
	//! Game logs
	void outputToFile(string output);
private:
	//! Number of rows
	int row;
	//! Number of columns
	int column;
	//! An Array of pointers, pointing to CStrings (in order to be serailized)
	CString** grid;
	//! Start x coordinate
	int startX;
	//! Start y coordinate
	int startY;
	//! End x coordinate
	int endX;
	//! End Y coordinate
	int endY;
	//! The Map Object's name 
	CString mapName;
	//! Name of the next Map int he campaign.
	CString nextName;
	//! boolean value which checks for the next map
	bool hasNextMap;
	//! Character
	Character* player;
	int playerX;
	int playerY;
};


