#include "MapCreator.h"

//CONSTRUCTOR
MapCreator::MapCreator()
{
	mapLevel = 1;
}

//creates a new map for the level
void MapCreator::createNewLevel()
{
	map.clear();
	assignHeightWidth();
	createBasicMap();
	assignAreaAmounts();
	addEnvironment();
	save();
}

//Increments the level
void MapCreator::addLevel()
{
	mapLevel += 1;
}

/*
 * Assigns the height and width
 * AKA the rows and columns for the map
 */
void MapCreator::assignHeightWidth()
{
	columns = (30 / 2);
	rows = 10;
	switch (mapLevel)
	{
	case 2:
		columns = (50 / 2);
		rows = 15;
		break;

	case 3:
		columns = (70 / 2);
		rows = 20;
		break;
	}
	if (mapLevel > 3)
	{
		columns = (70 / 2);
		rows = 20;
	}
}

/*
 * Based on level sets vars to proper number
 */
void MapCreator::assignAreaAmounts()
{
	//places to be assigned for the first map
	gatoradeMachines = 2;
	houseNum = 3;
	barracksNum = 0;
	towerNum = 1;
	switch (mapLevel)
	{
	//places to be assigned for the second map
	case 2:
		gatoradeMachines = 5;
		houseNum = 4;
		barracksNum = 3;
		break;
	//places to be assigned for the third map
	case 3:
		gatoradeMachines = 6;
		houseNum = 7;
		barracksNum = 5;
		break;
	}
	if (mapLevel > 3)
	{
		gatoradeMachines = 2;
		houseNum = 1;
		barracksNum = 0;
	}
}

//creates a map filled with "\\"
void MapCreator::createBasicMap()
{

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			map.push_back("\\");
		}
	}
}

//distributes the places to each map while their are still unassigned places
void MapCreator::addEnvironment()
{
	map[columns / 2] = "B"; // inserting the boss
	int objectsToInsert[] =
	{ gatoradeMachines, houseNum, barracksNum, towerNum }; //number of each object type to be inserted
	std::string symbols[] =
	{ "G", "H", "M", "T" }; //each object's symbol notation with aligned index
	int tempX, tempY; //changing x-y values for insertion
	srand(time(0)); //seeding the random number generator
	for (int i = 0; i < ((sizeof(objectsToInsert) / sizeof(int))); i++) //for each in objectsToInsert
	{
		while (objectsToInsert[i] > 0) //while that index still has more to place
		{
			tempX = (rand() % (columns - 3) + 2); //get random x value within 0 to columns
			tempY = (rand() % (rows - 3) + 2); //get random y value within 0 to rows
			if (isIsolated(tempX, tempY)) //if that index is isolated
			{
				map[(tempY * columns) + tempX] = symbols[i]; //insert the symbol
				objectsToInsert[i]--; //decrement
			}
			else
			{
				continue;
			}
		}
	}
}

/*
 * Returns a boolean that is true if there is nothing already stored at the location and false if there is
 */
bool MapCreator::isIsolated(int c, int r)
{
	return (map[(r * columns) + c].compare("\\") == 0);
}

/*
 * Saves the columnns and rows as well as map data to a file named: maplevel+(the current level)
 * Rows are flagged by a '#' columns are flagged by a "$"
 * Map is saved in formatted matrix form
 */
void MapCreator::save()
{
	char lev = mapLevel + '0';
	std::string outFileName = "maplevel";
	outFileName += lev;
	std::ofstream saveFile(outFileName, std::ios::trunc);
	if (!saveFile)
	{
		std::cout << "Error saving the maps!";
	}
	else
	{
		saveFile << "#" << rows << std::endl;
		saveFile << "$" << columns;
		saveFile << "\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				saveFile << map[(i * columns) + j];
			}
			saveFile << "\n";
		}
	}
	saveFile.close();
}
