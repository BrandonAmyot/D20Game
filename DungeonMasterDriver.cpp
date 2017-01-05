#include "Map.h"
#include "Watcher.h"
#include "gfx.h"

int main()
{
	cout << "*********************************************************************************" << endl;
	cout << "        --------------- Welcome to DUNGEONS & DRAGONS --------------" << endl;
	cout << "*********************************************************************************" << endl << endl;
	Map* mapMain = new Map();
	Map* mapSecond = new Map();
	Character* tempCharacter;
	Watcher* test = new Watcher();
	mapMain->setPlayer(test->createHero());
	tempCharacter = mapMain->getPlayer();
	cout << "Do you want to create or load map?" << endl;
	string ans;
	cin >> ans;

	if (ans == "create")
	{
		mapMain = Map::createMap(mapMain->getPlayer(), 0, "yo");
		mapMain->printMap();
		mapMain->getPlayer()->getScores();

		if (mapMain->getHasNextMap())
		{
			Character* character1 = new Character();

			CString tempName = mapMain->getNextName();
			do
			{
				mapSecond = Map::createMap(mapMain->getPlayer(), 1, tempName);
				tempName = mapSecond->getNextName();

			} while (mapSecond->getHasNextMap());
			/*delete mapSecond;
			mapSecond = NULL;*/
		}


		cout << "Starting campaign..." << endl;
		system("PAUSE");
		cout << endl;
		cout << "*********************************************************************************" << endl;
		cout << "        --------------- Get ready to play! --------------" << endl;
		cout << "*********************************************************************************" << endl;
		cout << "CONTROLS: Press W to move UP, Press S to move DOWN, Press A to move LEFT, Press D to move RIGHT\n Pess I to access the player's scores and Inventory" << endl;

		mapMain->turnEngine(mapMain);


		//! Loads the next map in the campagin
		if (mapMain->getHasNextMap() == true)
		{
			CT2CA pszConvertedAnsiString(mapMain->getNextName());
			string strStd(pszConvertedAnsiString);
			mapSecond->load(strStd);
			mapSecond->setPlayer(mapMain->getPlayer());
			mapSecond->turnEngine(mapSecond);
			//! loads consecutive maps in the campaign after the first one is loaded

			while (mapSecond->getHasNextMap() == true)
			{
				tempCharacter = mapSecond->getPlayer();
				CT2CA pszConvertedAnsiString(mapSecond->getNextName());
				string strStd(pszConvertedAnsiString);
				mapSecond->load(strStd);
				//! Setting the player to the one originally created/loaded
				mapSecond->setPlayer(tempCharacter);
				mapSecond->turnEngine(mapSecond);
			}
			cout << "\nCreate DONEEEEE!" << endl;

		}

	}
	//! If the user chose load
	else if (ans == "load")
	{
		ifstream inStream;
		string list;
		cout << "List of saved maps: " << endl;
		inStream.open("Maps.txt");
		while (inStream >> list) {
			cout << list << endl;
		}
		inStream.close();
		cout << "Enter the Map name you would like to load" << endl;
		string input;
		cin >> input;
		cout << "**********LOADING*************" << endl;
		//Map* mapMain2 = new Map();
		mapMain->load(input);
		mapMain->printMap();
		mapMain->getPlayer()->getScores();
		cout << "\nDo you want to use the character you just created? (y/n): ";
		cin >> input;
		if (input == "y")
		{
			mapMain->setPlayer(tempCharacter);
		}
		mapMain->getPlayer()->getScores();
		cout << "Do you want to edit this map/save this character to this map? (y/n): " << endl;
		cin >> input;
		if (input == "y")
		{
			//! starting here
			mapMain = Map::editMap(mapMain);
			mapMain->printMap();
			mapMain->getPlayer()->getScores();
			mapMain->turnEngine(mapMain);
			//! If there is a S map, load it
			if (mapMain->getHasNextMap() == true)
			{
				Map* map2 = new Map();
				CT2CA pszConvertedAnsiString(mapMain->getNextName());
				string strStd(pszConvertedAnsiString);
				map2->load(strStd);
				map2->setPlayer(mapMain->getPlayer());
				map2->turnEngine(map2);

				//! loads consecutive maps in the campaign after the first one is loaded
				while (map2->getHasNextMap() == true)
				{
					tempCharacter = map2->getPlayer();
					CT2CA pszConvertedAnsiString(map2->getNextName());
					string strStd(pszConvertedAnsiString);
					map2->load(strStd);
					//! Setting the player to the one originally created/loaded
					map2->setPlayer(tempCharacter);
					map2->turnEngine(map2);
				}
				cout << "\nLoad TEST DONEEEEE!" << endl;
				delete map2;
				map2 = NULL;

			}


		}
		else
		{
			mapMain->turnEngine(mapMain);
			//! If there is a next map, load it
			if (mapMain->getHasNextMap() == true)
			{
				Map* map2 = new Map();
				CT2CA pszConvertedAnsiString(mapMain->getNextName());
				string strStd(pszConvertedAnsiString);
				map2->load(strStd);
				map2->setPlayer(mapMain->getPlayer());
				map2->turnEngine(map2);

				//! loads consecutive maps in the campaign after the first one is loaded
				while (map2->getHasNextMap() == true)
				{
					tempCharacter = map2->getPlayer();
					CT2CA pszConvertedAnsiString(map2->getNextName());
					string strStd(pszConvertedAnsiString);
					map2->load(strStd);
					//! Setting the player to the one originally created/loaded
					map2->setPlayer(tempCharacter);
					map2->turnEngine(map2);
				}
				cout << "\nTEST DONEEEEE!" << endl;
				delete map2;
				map2 = NULL;
			}

		}

	}
	//	}
	/*Character* c= new Character();
	Map* mapMain = new Map(5, 5, 1, 1, 4, 4,"name", c);
	mapMain->fillCell(3, 3, "O");
	mapMain->fillCell(3, 4, "L");
	mapMain->fillCell(2, 3, "G");
	cout << "This is the lvl: "<<mapMain->getPlayer()->getLevel() << endl;
	mapMain->move(5);*/
	delete mapSecond;
	mapSecond = NULL;
	delete mapMain;
	mapMain = NULL;
	return 0;
}