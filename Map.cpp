//! @file
//! @author Tarik Azzouni - 27013701
//! @brief Implementation file for the Map class
//!
#include "Map.h"
#include "MovementStrategy.cpp"
#include "HumanStrategy.cpp"
#include "AgressorStrategy.cpp"
#include "FriendlyStrategy.cpp"
#include "Treasure.h"
using namespace std;

IMPLEMENT_SERIAL(Map, CObject, 1)
//! Default constructor, defined empty in order for the MFC serialization to work properly
Map::Map() 
{
	
}
//! Non-default constructor bulding a blank map with specified dimenions and START/END coordinates
Map::Map(int row, int col, int startX, int startY, int endX, int endY, CString name,  Character* play) 
{
	this->row = row;
	this->column = col;
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	this->mapName = name;
	this->grid = new CString*[this->row];
	this->player = play;

	for (int i = 0; i < this->row; i++)
	{
		this->grid[i] = new CString[this->column];
	}
	//! Assigning the values of each cell to empty/walkable
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->column; j++)
		{
			this->grid[i][j] = '_';
		}
	}
	//Sets the start and end coordinates
	this->grid[this->startX][this->startY] = 'S';
	this->grid[this->endX][this->endY] = 'E';
	playerX = startX;
	playerY= startY;
	nextName = "NO";
}
//! Destructor
Map::~Map()
{
	/*delete player;
	player = NULL;*/
}

//! Returns the row size
int Map::getRow()
{
	return Map::row; 
}
//! Returns the column size
int Map::getCol()
{
	return Map::column;
}
//! Returns the grid
CString** Map::getGrid()
{
	return grid;
}
//! Returns the Start x coordinate
int Map::getStartX()
{
	return Map::startX;
}
//! Returns the Start x coordinate
int Map::getStartY()
{
	return Map::startY;
}
//! Returns the End x index
int Map::getEndX()
{
	return Map::endX;
}
//! Returns the end Y index
int Map::getEndY()
{
	return Map::endY;
}
//! Sets the name of the next Map in the cmapaign
void Map:: setNextName(CString next)
{
	nextName = next;
}
bool Map::getHasNextMap()
{
	return hasNextMap;
}
void Map::setHasNextMap(bool val)
{
	this->hasNextMap = val;
}
//! Fills a cell based on 
void Map::fillCell(int x, int y, string obj) 
{
	while (true) 
	{
		/*if (x == startX || y == startY || x == endX || y == endY)
		{
			cout << "Cannot change START and END coordinates" << endl;
		}
		*/
		if (obj == "W" || obj == "O" || obj == "L" || obj == "C" || obj == "G")
		{
			cout << "Valid!" << endl;
			char c = obj[0];
			cout << "THIS IS THE CHAR: " << c << endl;
			this->grid[x][y] = c;
			break;
		}

		else
		{
			cout << "Not valid, enter new input: " << endl;
			cin >> obj;
		}
	}
	//! Gets called for use in the Observer pattern
	Notify();
	return;
}

//! Checks if a cell is filled with any other other than an empty space
bool Map::isOccupied(int x, int y)
{
	if (this->grid[x][y] != '_')
	{
		
		return false;
	}
	else
	{
		return true;
	}
	
}
//! Prints the Map grid
void Map::printMap()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			//! Since each cell is composed of CStrings, I converted the CString to a 
			//! string with this small code
			CString cs = grid[i][j];
			CT2CA pszConvertedAnsiString(cs);
			string strStd(pszConvertedAnsiString);
			cout << strStd << " ";
		}
		cout << endl;
	}
	if (grid[startX][startY] == "_")
	{
		grid[startX][startY] = "S";
	}
	outputToFile("Printing Map to Screen...");
}

//! Verifies that there is a winning path form the start to end
bool Map::validatePath(int x, int y)
{
	// If x, y is outside maze, return false.
	if (x < 0 || x > row - 1 || y < 0 || y > column - 1)
		return false;

	// If x,y is the goal, return true.
	if (grid[x][y] == 'E') {
		// restore the map
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (grid[i][j] == '+')
					grid[i][j] = '_';
			}
		}
		grid[startX][startY] = 'S';
		grid[endX][endY] = 'E';
		return true;
	}

	// If x,y is occupied or has been visited
	if (grid[x][y] == 'W' || grid[x][y] == '+')
		return false;

	// Mark where the algorithm has gone; ignore Monsters and Chests
	if (grid[x][y] == 'O') 
	{
		grid[x][y] = 'O';
	}
	else if (grid[x][y] == 'G')
	{
		grid[x][y] = 'G';
	}
	else if (grid[x][y] == 'L')
	{
		grid[x][y] = 'L';
	}
	else if (grid[x][y] == 'C')
		grid[x][y] = 'C';
	else
		grid[x][y] = '+';

	// If right of x,y is open, go right.
	if (validatePath(x, y + 1) == true) {
		return true;
	}
	// If down north of x,y is open, go down.
	else if (validatePath(x + 1, y) == true) {
		return true;
	}
	// If up of x,y is open, go straight.
	else if (validatePath(x - 1, y) == true) {
		return true;
	}
	// If left of x,y is open, go left.
	else if (validatePath(x, y - 1) == true) {
		return true;
	}
	else {
		if (grid[x][y] == '+')
			grid[x][y] = '_';
		return false;
	}
	outputToFile("Validating Path of Map...");
}
//! Serialized and saves the Map Object to a text file
void Map::save()
{
	//! Makes a new CFile
	CFile theFile;
	//! Opens thein outputmode
	theFile.Open(mapName, CFile::modeCreate | CFile::modeWrite);
	//! Creates a CArchive output 
	CArchive archive(&theFile, CArchive::store);
	//! Serializes this instance of the Map to the archive
	this->Serialize(archive);
	archive.Close();
	theFile.Close();
	outputToFile("Saving Map To File.");
}
//! Deserailizes and loads a Map object
Map* Map::load(string name)
{
	
	CFile theOtherFile;
	//! Opens a specified file in input mode
	theOtherFile.Open(CString(name.c_str()), CFile::modeRead);
	//! Creates a CArchive and connect it to the file
	CArchive otherArchive(&theOtherFile, CArchive::load);
	//! Serializes this instance of the Map to the archive
	this->Serialize(otherArchive);
	otherArchive.Close();
	theOtherFile.Close();
	outputToFile("Loading Map From File.");
	return this;

}

//! Creates a map based on user input, which includes text prompts
Map* Map::createMap(Character* player, int count, CString name)
{
	cout << "*********************************************************************************" << endl;
	cout << "        --------------- Create your Dungeon --------------" << endl;
	cout << "*********************************************************************************" << endl;
	string nextFileName;
	ofstream outStream;
	string ans;
	string fileName;
	Map* map1;
	if(count == 0)
	{
		cout << "Enter a file name: ";
	
		cin >> fileName;
	}
		
	//! Assuming perfect user input
	cout << "\nMap Creation:" << endl;
	int row;
	int col;
	int startX, startY;
	int endX, endY;
	do 
	{
		cout << "\nEnter width of map: ";
		cin >> row;
		cout << "\nEnter length of map: ";
		cin >> col;
		cout << "\nEnter Start coordinates (row followed by column) Indexed by 0!: ";
		cin >> startX;
		cin >> startY;
		while (startX < 0 || startY < 0 || startX > row - 1 || startY > col - 1) {
			cout << "Out of bounds, enter new values: " << endl;
			cin >> startX;
			cin >> startY;
		}
		cout << "\nEnter End coordinates (row followed by column) Indexed by 0!: ";
		cin >> endX;
		cin >> endY;
		while (endX < 0 || endY < 0 || endX > row - 1 || endY > col - 1) {
			cout << "Out of bounds, enter new values: " << endl;
			cin >> endX;
			cin >> endY;
		}
		if (row < 0 || col < 0 || startX < 0 || startY < 0 || endX < 0 || endY < 0)
		{
			cout << " Values must be positive! Try again." << endl;
		}
	} while (row < 0 || col < 0 || startX < 0 || startY < 0 || endX < 0 || endY < 0);
	

	//! If this is the first map
	if (count == 0)
	{
		map1 = new Map(row, col, startX, startY, endX, endY, CString(fileName.c_str()), player);
		map1->outputToFile("GAME PHASE: CREATING DUNGEON");

		//! Converts map name to String. Ouputs to a file.
		CString cs = map1->getMapName();
		CT2CA pszConvertedAnsiString(cs);
		string mName(pszConvertedAnsiString);
		map1->outputToFile("Map is created: " + mName);
	}
	//! Is this is another map, then its name is already defined
	else
	{
		map1 = new Map(row, col, startX, startY, endX, endY, name, player);
		map1->outputToFile("GAME PHASE: CREATING DUNGEON");
	}
	string obj;
	int x = 0;
	int y = 0;
		do
		{
			map1->outputToFile("GAME PHASE: EDITING MAP");
			cout << "\n-----Displaying Current map-------" << endl;
			map1->printMap();
			cout << "\nEnter the cell coordinate you would like to change (row followed by column) Indexed by 0!, or Enter a negative numbers to stop: ";
			cin >> x;
			cin >> y;
			while (x > row || y > col)
			{
				cout << "Enter only positive numbers between your grid dimensions." << endl;
			}

			if (x < 0 || y < 0)
			{
				break;
			}
			cout << "\nEnter game object to add, [W: Wall, C: Chest, G: Goblin, L: Gnoll, O: Ogre]: ";
			cin >> obj;
			map1->fillCell(x, y, obj);
			map1->outputToFile("Player Adds an Object to the Map");

			while (!(map1->validatePath(startX, startY)))
			{
				map1->printMap();
				cout << "There is no clear winning path!" << endl;
				cout << "\n Please change the cell in order to make a clear path: ";
				cin >> x;
				cin >> y;

			}

		} while (true);

		map1->printMap();

		cout << "Do you want to create another level in this campaign (y/n)?: ";
		cin >> ans;
		if (ans == "y")
		{
			cout << "\nPlease enter a name for the next map: ";
			cin >> nextFileName;
			map1->nextName = CString(nextFileName.c_str());
			cout << "Creating next map with the same character" << endl;
			map1->setHasNextMap(true);
			map1->outputToFile("Player Creates another Level in the Campaign.");
		}
		else
		{
			map1->setHasNextMap(false);
		}
		
		CT2CA pszConvertedAnsiString(map1->mapName);
		string strStd(pszConvertedAnsiString);
		outStream.open("Maps.txt", std::ios_base::app);
		outStream << fileName << endl;
		outStream.close();
		map1->save();


	if (map1->getHasNextMap()==true)
	{
		cout << "\nCreating next level in the campaign..." << endl;
		map1->outputToFile("GAME PHASE: Creating Next Level.");
	}
	else if (map1->getHasNextMap() == false)
	{
		cout << "\nCampaign finished!" << endl;
		map1->outputToFile("GAME PHASE: End of Dungeon Creation.");
	}
	return map1;
}

//! Edits an existing Map, based on user input
Map* Map::editMap(Map* map)
{	
	map->outputToFile("GAME PHASE: EDITING AN EXISTING MAP");
	CString cs = map->getMapName();
	CT2CA pszConvertedAnsiString(cs);
	string strStd(pszConvertedAnsiString);
	cout << "\nEditing " << strStd<< " map" << endl;;
	int i = 0;
	int j = 0;
	string obj;
	do
	{
		cout << "\n-----Displaying Current map-------" << endl;
		map->printMap();
		cout << "\nEnter the cell coordinate you would like to change (x followed by y) or Enter a negative numbers to stop: ";
		cin >> i;
		cin >> j;
		if (i < 0 || j < 0)
			break;
		cout << "\nEnter game object to add, [W: Wall, C: Chest, G: Goblin, L: Gnoll, O: Ogre]: ";
		cin >> obj;
		map->fillCell(i, j, obj);
		map->outputToFile("Player places an object on the map.");
	} while (true);
	map->save();
	cout << "Changes have been saved!" << endl;
	return map;
}  

//! Serializes and deserializes a Map object to a Text file
void Map::Serialize(CArchive & archive)
{
	CObject::Serialize(archive);

	//!Serializes
	if (archive.IsStoring())
	{
		archive << row << column << startX << startY << endX << endY << mapName << nextName<<hasNextMap<<playerX<<playerY << player;
		 for (int i = 0; i < row ; i++)
		 {
			 for (int j = 0; j < column ; j++)
			 {
				 archive << grid[i][j];
			 }
		 }
	}
	//! Deseriliazes
	else
	{
		archive >> row;
		archive >> column;

		archive >> startX >> startY >> endX >> endY >> mapName >> nextName>> hasNextMap>>playerX>>playerY >>player;
		grid = new CString*[row];
		for (int i = 0; i < row; i++)
		{
			grid[i] = new CString[column];
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				
				archive >> grid[i][j];
			}
		}
	}	
}
//! Moves the player P to a desired location, tracks 1 move and 1 attack per turn
void Map::move()
{
	printMap();
	cout << "Enter W, A, S, D to move, B to fight a monster, I to check inventory or E to end your turn." << endl;

	bool hasMoved = false; // to track if player has moved this turn
	bool hasAttacked = false; // to track if player has attacked this turn
	int monsterX, monsterY;
	string input;

	while (true) {
		// if the player has used all their moves this turn
		if (hasMoved == true && hasAttacked == true) {
			outputToFile("Player's Turn Ends.");
			break;
		}
		cout << "Enter what you would like to do: " << endl;
		cin >> input;
		outputToFile("Start Of Player's Turn.");

		//! Checks if you can go Up
		if (input == "W" || input == "w")
		{
			outputToFile("Player Moves Up");
			if (hasMoved == true) {
				cout << "You have already moved this turn!" << endl;
			}
			else {
				// player cannot walk through walls, or monsters
				if (playerX - 1 < 0 || grid[playerX - 1][playerY] == 'W' || grid[playerX - 1][playerY] == 'G' || grid[playerX - 1][playerY] == 'L' || grid[playerX - 1][playerY] == 'O')
				{
					cout << "There's something in the way!\n";
				}
				// if the player walks into a chest, will generate an item
				else if (grid[playerX - 1][playerY] == 'C')
				{
					outputToFile("Player Encounters A Chest!");
					grid[playerX - 1][playerY] = '_';
					Treasure t = Treasure();
					t.setTreasureContents();
					if (t.getItemFromTreasure()) {
						player->addToInventory(*(t.getItemFromTreasure()));
					}
					else {
						continue;
					}
					//player->addToInventory(*(t.getItemFromTreasure()));
					cout << "You picked up: ";
					outputToFile("Player Picks Up Item.");
					t.display();
					cout << endl;
				}
				else
				{
					// move the player and replace the old cell with an empty cell
					int temp1 = playerX;
					playerX -= 1;
					grid[temp1][playerY] = '_';
					grid[playerX][playerY] = 'P';
					printMap();
					hasMoved = true;
				}
			}
		}
		//! Checks if you can go down
		if (input == "S" || input == "s")
		{
			outputToFile("Player Moves Down.");
			if (hasMoved == true) {
				cout << "You have already moved this turn!" << endl;
			}
			else {
				// player cannot walk through walls, or monsters
				if (playerX + 1 > row - 1 || grid[playerX + 1][playerY] == 'W' || grid[playerX + 1][playerY] == 'G' || grid[playerX + 1][playerY] == 'L' || grid[playerX + 1][playerY] == 'O')
				{
					cout << "There's something in the way!\n";
				}
				// if the player walks into a chest, will generate an item
				else if (grid[playerX + 1][playerY] == 'C')
				{
					outputToFile("Player Encounters A Chest!");
					grid[playerX + 1][playerY] = '_';
					Treasure t = Treasure();
					t.setTreasureContents();
					if (t.getItemFromTreasure()) {
						player->addToInventory(*(t.getItemFromTreasure()));
					}
					else {
						continue;
					}
					
					//player->addToInventory(*(t.getItemFromTreasure()));
					cout << "You picked up: ";
					outputToFile("Player Picks Up Item");
					t.display();
					cout << endl;
				}
				else
				{
					// move the player and replace the old cell with an empty cell
					int temp1 = playerX;
					playerX += 1;
					grid[temp1][playerY] = '_';
					grid[playerX][playerY] = 'P';
					printMap();
					hasMoved = true;
				}
			}
		}
		//! Checks if you can go right
		if (input == "D" || input == "d")
		{
			outputToFile("Player Moves Right.");
			if (hasMoved == true) {
				cout << "You have already moved this turn!" << endl;
			}
			else {
				// player cannot walk through walls, or monsters
				if (playerY + 1 > column - 1 || grid[playerX][playerY + 1] == 'W' || grid[playerX][playerY + 1] == 'G' || grid[playerX][playerY + 1] == 'L' || grid[playerX][playerY + 1] == 'O')
				{
					cout << "There's something in the way!\n";
				}
				// if the player walks into a chest, will generate an item
				else if (grid[playerX][playerY + 1] == 'C')
				{
					outputToFile("Player Encounters a Chest!");
					grid[playerX][playerY + 1] = '_';
					Treasure t = Treasure();
					t.setTreasureContents();
					if (t.getItemFromTreasure()) {
						player->addToInventory(*(t.getItemFromTreasure()));
					}
					else {
						continue;
					}
					
					//player->addToInventory(*(t.getItemFromTreasure()));
					cout << "You picked up: ";
					outputToFile("Player Picks Up Item");
					t.display();
					cout << endl;
				}
				else
				{
					// move the player and replace the old cell with an empty cell
					int temp1 = playerY;
					playerY += 1;
					grid[playerX][temp1] = '_';
					grid[playerX][playerY] = 'P';
					printMap();
					hasMoved = true;
				}

			}
		}
		//! Checks if you can go left
		if (input == "A" || input == "a")
		{
			outputToFile("Player Moves Left.");
			if (hasMoved == true) {
				cout << "You have already moved this turn!" << endl;
			}
			else {
				// player cannot walk through walls, or monsters
				if (playerY - 1 < 0 || grid[playerX][playerY - 1] == 'W' || grid[playerX][playerY - 1] == 'G' || grid[playerX][playerY - 1] == 'L' || grid[playerX][playerY - 1] == 'O')
				{
					cout << "There's something in the way!\n";
				}
				// if the player walks into a chest, will generate an item
				else if (grid[playerX][playerY - 1] == 'C')
				{
					outputToFile("Player Encounters a Chest!");
					grid[playerX][playerY - 1] = '_';
					Treasure t = Treasure();
					t.setTreasureContents();
					
					if (t.getItemFromTreasure()) {
						player->addToInventory(*(t.getItemFromTreasure()));
					}
					else {
						continue;
					}
					//player->addToInventory(*(t.getItemFromTreasure()));
					cout << "You picked up: ";
					outputToFile("Player Picks Up Item");
					t.display();
					cout << endl;
				}
				else
				{
					// move the player and replace the old cell with an empty cell
					int temp1 = playerY;
					playerY -= 1;
					grid[playerX][temp1] = '_';
					grid[playerX][playerY] = 'P';
					printMap();
					hasMoved = true;
				}
			}
		}
		// display inventory
		if (input == "I" || input == "i")
		{ //!!!! Equip From Inventory Does not Work!!!!!
			player->getScores();
			player->displayWornItems();
		//	player->displayInventory();
			player->equipInventory();
			outputToFile("Player Displays Inventory.");
			printMap();
		}
		// commence battle sequence
			if (input == "B" || input == "b") {
				outputToFile("Player Enters a Battle!");
				cout << "Enter the direction the monster you would like to attack (W, A, S, D): ";
				cin >> input;
				switch (input[0]) {
				case 'w':
				case 'W': attack(playerX - 1, playerY); break;
				case 'a':
				case 'A': attack(playerX, playerY - 1); break;
				case 'd':
				case 'D': attack(playerX, playerY + 1); break;
				case 's':
				case 'S': attack(playerX + 1, playerY); break;
				default: cout << "Your eyes have deceived you, there is no monster there..." << endl << endl;
				}
				hasAttacked = true;
				printMap();
			}


		// end turn
		if (input == "E" || input == "e") {
			outputToFile("Player's Turn Ends");
			break;
		}
	}
	Notify();
}

//! Moves the monster on the map towards the player
void Map::monsterMove()
{	
	//! Moves monsters
	for (int i = 0; i < getRow(); i++)
	{
		for (int j = 0; j < getCol(); j++)
		{
			if (grid[i][j] == "G") 
			{
				moveHelper(playerX, playerY, i, j, "G");
			}
			else if (grid[i][j] == "L") 
			{
				moveHelper(playerX, playerY, i, j, "L");
			}
			else if (grid[i][j] == "O") 
			{
				moveHelper(playerX, playerY, i, j, "O");
			}
			else 
			{
				
			}
		}
	}
	Notify();
}

 //! moves the friendly NPCs around the character
void Map::friendlyMove()
{
	// move NPCS
	for (int i = 0; i < getRow(); i++) {
		for (int j = 0; j < getCol(); j++) {
			if (grid[i][j] == "N") {
				moveHelper(playerX, playerY, i, j, "N");
			}
			else {
				// do nothing
			}
		}
	}
	Notify();
}

//! Helper method to move the monsters around the map
void Map::moveHelper(int playerX, int playerY, int monsterX, int monsterY, CString monster) {
	//! Moves monster up towards player
	if (monsterX > playerX)
	{
		// if the monster encounters a player, fights it
		if (grid[monsterX - 1][monsterY] == "P") {
			outputToFile("Monster Enters Battle With the Player.");
			battle(monsterX, monsterY);
			return;
		}
		else if (grid[monsterX - 1][monsterY] == "_")
		{
			grid[monsterX][monsterY] = "_";
			grid[monsterX - 1][monsterY] = monster;
			return;
		}
		else {
			// do nothing
		}
	}
	//! Moves monster left towards player
	if (monsterY > playerY)
	{
		// if the monster encounters a player, fights it
		if (grid[monsterX][monsterY - 1] == "P") {
			outputToFile("Monster Enters Battle With the Player.");
			battle(monsterX, monsterY);
			return;
		}
		else if (grid[monsterX][monsterY - 1] == "_")
		{
			grid[monsterX][monsterY] = "_";
			grid[monsterX][monsterY - 1] = monster;
			return;
		}
		else {
			// do nothing
		}
	}
	//! Moves monster down towards player
	if (monsterX < playerX)
	{
		// if the monster encounters a player, fights it
		if (grid[monsterX + 1][monsterY] == "P") {
			outputToFile("Monster Enters Battle With the Player.");
			battle(monsterX, monsterY);
			return;
		}
		else if (grid[monsterX + 1][monsterY] == "_")
		{
			grid[monsterX][monsterY] = "_";
			grid[monsterX + 1][monsterY] = monster;
			return;
		}
		else {
			//do nothing
		}
	}
	//! Moves monster right towards player
	if (monsterY < playerY)
	{
		// if the monster encounters a player, fights it
		if (grid[monsterX][monsterY + 1] == "P") {
			outputToFile("Monster Enters Battle With the Player.");
			battle(monsterX, monsterY);
			return;
		}
		else if (grid[monsterX][monsterY + 1] == "_")
		{
			grid[monsterX][monsterY] = "_";
			grid[monsterX][monsterY + 1] = monster;
			return;
		}
		else {
			// do nothing
		}
	}
}

//! Manages the changing tunrs of monsters and player
void Map::turnEngine(Map* map) {

	//! Initliazes the playerMovement, monstermovement, and friendlyMovement
	MovementStrategy playerMovement(new HumanStrategy);
	MovementStrategy monsterMovement(new AgressorStrategy);
	MovementStrategy friendlyMovement(new FriendlyStrategy); 
	do 
	{
		cout << "It's your turn..." << endl;
		playerMovement.executeStrategy(map);
		if (grid[endX][endY] == "P")
		{
			if (hasNextMap==true)
			{
				cout << " You have completed the dungeon! Moving to the next dungeon! " << endl;
				outputToFile("Player Completes Dungeon. Moving on to the Next...");
				break;
			}
			else
			{
				cout << "All dungeons have been cleared, you are victorious!" << endl;
				outputToFile("Player Clears All Dungeons! HE IS VICTORIOUS ON THE PLANES OF VALHALLA!");
				break;
			}
			
		}
		cout << "It's the monsters' turn..." << endl;
		outputToFile("Monster's Turn.");
		monsterMovement.executeStrategy(map);
		cout << "It's the friendly's turn..." << endl;
		outputToFile("Friendly's turn.");
		friendlyMovement.executeStrategy(map);



	} while (true);
	
}

//! Controls combat sequence for human player.
void Map::attack(int monsterX, int monsterY) {
	Dice* dice = new Dice();
	Character* monster;
	Watcher* diceWatcher = NULL;
	int hitOrMiss;
	int damageRoll;

	
	
	
	if (grid[monsterX][monsterY] == 'G') {
		monster = new Goblin(player->getLevel());
		cout << "You are attacking a Goblin." << endl;
		monster->getScores();
	}
	else if (grid[monsterX][monsterY] == 'L') {
		monster = new Gnoll(player->getLevel());
		cout << "You are attacking a Gnoll." << endl;
		monster->getScores();
	}
	else if (grid[monsterX][monsterY] == 'O') {
		monster = new Ogre(player->getLevel());
		cout << "You are attacking an Ogre." << endl;
		monster->getScores();
	}
	else {
		return;
	}

	cout << "Do you want to record the dice rolls for posterity?(yes/no)" << endl;
	string ans;
	cin >> ans;
	if (ans == "Yes" || ans == "yes") {
		diceWatcher = new Watcher(dice);
	}

	while (monster->isAlive() && player->isAlive()) {
		// HUMAN ATTACK PHASE
		cout << endl << "Your attack phase" << endl;
		outputToFile("Start of Player Attack Phase.");

		hitOrMiss = dice->Roll("1d20");
		dice->Reset();
		// critical hit
		if (hitOrMiss == 20) {
			cout << "Critical Hit!!!" << endl;
			damageRoll = dice->Roll("2d6") + player->getDamageBonus();
			monster->receiveAttack(damageRoll);
			outputToFile("Monster Recieves Critical Hit");
			dice->Reset();
		}
		// automatic miss
		if (hitOrMiss == 1) {
			cout << "The attack missed!" << endl;
			outputToFile("Player's Attack Missed.");
		}
		// check if attack hits, calculate damage and hit points
		else if ((hitOrMiss + player->getModifier(0)/*+ getProfBonus()*/) >= (monster->getArmorClass() + monster->getModifier(1))) {
			cout << "You landed a hit!" << endl;
			damageRoll = dice->Roll("1d6") + player->getDamageBonus();
			monster->receiveAttack(damageRoll);
			cout << "You dealt " << damageRoll << " damage" << endl;
			outputToFile("Monster gets damaged.");
			dice->Reset();
		}
		// blocked attack
		else {
			cout << "Your attack was blocked!" << endl;
			outputToFile("Player's Attack Blocked");

		}
		// check if the monster was killed
		if (!monster->isAlive()) {
			player->setSpecificExp(player->getExpPoints() + monster->giveHeroExp());
			cout << "You defeated an enemy! You have gained: " << monster->giveHeroExp() << endl << endl;
			grid[monsterX][monsterY] = '_';
			outputToFile("Player Defeats Enemy.");
			break;
		}
		system("PAUSE");
		cout << endl;

		// MONSTER ATTACK PHASE
		cout << endl << "Monster's attack phase" << endl;
		outputToFile("Start Of Monster's attack Phase.");

		hitOrMiss = dice->Roll("1d20");
		dice->Reset();
		// critical hit
		if (hitOrMiss == 20) {
			cout << "Critical Hit!!!" << endl;
			damageRoll = dice->Roll("2d6") + monster->getDamageBonus();
			player->receiveAttack(damageRoll);
			cout << "You took " << damageRoll << " damage!" << endl;
			outputToFile("Player's Receives Critical Hit!");

			dice->Reset();
		}
		// automatic miss
		if (hitOrMiss == 1) {
			cout << "The attack missed!" << endl;
			outputToFile("Monster's Attack Missed.");

		}
		// check if attack hits, calculate damage and hit points
		else if ((hitOrMiss + monster->getModifier(0)) >= (player->getArmorClass() + player->getModifier(1))) {
			cout << "You get hit!" << endl;
			damageRoll = dice->Roll("1d6") + monster->getDamageBonus();
			player->receiveAttack(damageRoll);
			cout << "You took " << damageRoll << " damage!" << endl;
			outputToFile("Player gets damaged.");
			dice->Reset();
		}
		//blocked attack
		else {
			cout << "You blocked the attack!" << endl;
			outputToFile("Player Blocks Monster's Attack");

		}
		//check if player is alive
		if (!player->isAlive()) {
			cout << "You have died... Your adventure ends here." << endl;
			outputToFile("Player Dies...");

			break;
		}
		system("PAUSE");
		cout << endl;

	}
	if (ans == "yes" || ans == "Yes") {
		delete diceWatcher;
	}
	delete dice;
	delete monster;
	Notify();
}

//! Manages battles between the player and monsters
void Map::battle(int monsterX, int monsterY)
{
	Dice* dice = new Dice();
	Character* monster;
	Watcher* diceWatcher = NULL;
	int hitOrMiss;
	int damageRoll;

	

	if (grid[monsterX][monsterY] == 'G') {
		monster = new Goblin(player->getLevel());
		cout << "You are being attacking by a Goblin." << endl;
		monster->getScores();
		cout << endl << endl;
	}
	else if (grid[monsterX][monsterY] == 'L') {
		monster = new Gnoll(player->getLevel());
		cout << "You are being attacking by a Gnoll." << endl;
		monster->getScores();
		cout << endl << endl;
	}
	else if (grid[monsterX][monsterY] == 'O') {
		monster = new Ogre(player->getLevel());
		cout << "You are being attacking by an Ogre." << endl;
		monster->getScores();
		cout << endl << endl;
	}
	else {
		return;
	}

	cout << "Do you want to record the dice rolls for posterity?(yes/no)" << endl;
	string ans;
	cin >> ans;

	if (ans == "Yes" || ans == "yes") {
		diceWatcher = new Watcher(dice);
	}
	while (monster->isAlive() && player->isAlive()) {
		// MONSTER ATTACK PHASE
		cout << endl << "Monster's attack phase" << endl;
		outputToFile("Start of Monster's Attack Phase.");
		hitOrMiss = dice->Roll("1d20");
		dice->Reset();
		// critical hits
		if (hitOrMiss == 20) {
			cout << "Critical Hit!!!" << endl;
			damageRoll = dice->Roll("2d6") + monster->getDamageBonus();
			player->receiveAttack(damageRoll);
			cout << "You took " << damageRoll << " damage!" << endl;
			outputToFile("Player Receives Critical Hit!");
			dice->Reset();
		}
		// automatic miss
		if (hitOrMiss == 1) {
			cout << "The attack missed!" << endl;
			outputToFile("Monster's Attack Missed!");
		}
		// check if attack hits, calculate damage and hit points
		else if ((hitOrMiss + monster->getModifier(0)) >= (player->getArmorClass() + player->getModifier(1))) {
			cout << "You got hit!" << endl;
			damageRoll = dice->Roll("1d6") + monster->getDamageBonus();
			player->receiveAttack(damageRoll);
			cout << "You took " << damageRoll << " damage!" << endl;
			outputToFile("Player gets damaged.");
			dice->Reset();
		}
		// blocked attack
		else {
			cout << "You blocked the attack!" << endl;
			outputToFile("Player Blocks Attack");
		}
		// check if the player was killed
		if (!player->isAlive()) {
			cout << "You have died... Your adventure ends here." << endl;
			outputToFile("Player Dies");
			return;
		}
		system("PAUSE");
		cout << endl;

		// HUMAN ATTACK PHASE
		cout << endl << "Your attack phase" << endl;
		outputToFile("Start Of Player Attack Phase.");
		hitOrMiss = dice->Roll("1d20");
		dice->Reset();
		if (hitOrMiss == 20) {
			cout << "Critical Hit!!!" << endl;
			damageRoll = dice->Roll("2d6") + player->getDamageBonus();
			monster->receiveAttack(damageRoll);
			cout << "You dealt " << damageRoll << " damage." << endl;
			outputToFile("Monster Recieves a Critical Hit.");
			dice->Reset();
		}
		// automatic miss
		if (hitOrMiss == 1) {
			cout << "The attack missed!" << endl;
			outputToFile("Player Attack Misses.");
		}
		// check if attack hits, calculate damage and hit points
		else if ((hitOrMiss + player->getModifier(0)/*+ getProfBonus()*/) >= (monster->getArmorClass() + monster->getModifier(1))) {
			cout << "You landed a hit!" << endl;
			damageRoll = dice->Roll("1d6") + player->getDamageBonus();
			monster->receiveAttack(damageRoll);
			cout << "You dealt " << damageRoll << " damage." << endl;
			outputToFile("Monster gets damaged.");
			dice->Reset();
		}
		// blocked attack
		else {
			cout << "Your attack was blocked!" << endl;
			outputToFile("Player's Attack was Blocked!");
		}
		// check if the monster was killed
		if (!monster->isAlive()) {
			player->setSpecificExp(player->getExpPoints() + monster->giveHeroExp());
			cout << "You defeated an enemy! You have gained: " << monster->giveHeroExp() << endl << endl;
			grid[monsterX][monsterY] = '_';
			outputToFile("Player Defeats Monster!");
			break;
		}
		system("PAUSE");
	}
	if (ans == "yes" || ans == "Yes") {
		delete diceWatcher;
	}
	delete dice;
	delete monster;
	Notify();
}
//! Game logs
void Map::outputToFile(string output) {
	ofstream myFile;
	myFile.open("GrandUnifiedLog.txt", ios::app);
	myFile << output << endl;
	myFile << endl;
	myFile.close();
}
