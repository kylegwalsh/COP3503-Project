#include "MapCreator.h"

int main()
{
	MapCreator mc(3);
	mc.printMap();
	return 0;
}

void MapCreator::printMap()
{
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<columns; j++)
		{
			std::cout << map[(i*columns)+j];
		}
		std::cout << "\n";
	}
}

MapCreator::MapCreator()
{
	MapCreator(1);
}

MapCreator::MapCreator(int level)
{
	mapLevel = level;
	assignHeightWidth();
	bossX = columns/2;
	createBasicMap();
	assignAreaAmounts();
	addEnvironment();
	save();
}

void MapCreator::assignHeightWidth()
{
	columns = 30;
	rows = 10;
	switch (mapLevel)
	{
		case 2: columns = 50; 
				rows = 15;
				break;

		case 3: columns = 70; 
				rows = 20;
				break;
	}
	if (mapLevel>3)
	{
		columns = 70;
		rows = 20;
	}
}

void MapCreator::assignAreaAmounts()
{
	gatoradeMachines = 2;
	houseNum = 3;
	barracksNum = 0;
	towerNum = 0;
	switch (mapLevel)
	{
		case 2: gatoradeMachines = 2;
				houseNum = 4;
				barracksNum = 0;
				towerNum = 2;
				break;
		case 3: gatoradeMachines = 6;
				houseNum = 6;
				barracksNum = 5;
				towerNum = 7;
				break;
	}
	if (mapLevel>3)
	{
		gatoradeMachines = 2;
		houseNum = 1;
		barracksNum = 0;
		towerNum = 0;
	}
}

void MapCreator::createBasicMap()
{

	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<columns; j++)
		{
			map.push_back("\\");
		}
	}
}

void MapCreator::addEnvironment()
{
	addObstacles();
	map[bossX] = "B"; // inserting the boss
	int objectsToInsert[] = {gatoradeMachines, houseNum, barracksNum, towerNum}; //number of each object type to be inserted
	char symbols[] = {'G', 'H', 'M', 'T'}; //each object's symbol notation with aligned index
	int tempX, tempY; //changing x-y values for insertion
	srand(time(0)); //seeding the random number generator
	for (int i=0; i<(sizeof(objectsToInsert)/sizeof(int)); i++) //for each in objectsToInsert
	{
		while (objectsToInsert[i]>0) //while that index still has more to place
		{
			tempX = (rand()%columns); //get random x value within 0 to columns
			tempY = (rand()%rows); //get random y value within 0 to rows
			if (isIsolated(tempX, tempY)) //if that index is isolated
			{
				map[(tempY*columns)+tempX] = symbols[i]; //insert the symbol
				objectsToInsert[i]--; //decrement 
			}
		}
	}
}
/*
* If the row(r) and column(c) location are within 2 spaces of a border, or
* two spaces within another object (house, etc.) left and right, top and bottom, or
* within one diagonal from another object then the object to be places is NOT isolated
*/
bool MapCreator::isIsolated(int c, int r)
{
	if ((rows-r)<=2 || (rows-r)>=(rows-2) || (columns-c)<=2 || (columns-c)>=(columns-2))
	{
		return false;
	}
	else
	{
		return 
		(
			map[(r*columns)+c].compare("\\")==0 && //at index
			map[(r*columns)+(c-1)].compare("\\")==0 && map[(r*columns)+(c+1)].compare("\\")==0 && //left and right 1
			map[(r*columns)+(c-2)].compare("\\")==0 && map[(r*columns)+(c+2)].compare("\\")==0 && //left and right 2
			map[((r+1)*columns)+c].compare("\\")==0 && map[((r-1)*columns)+c].compare("\\")==0 && //top and bottom 1
			map[((r+2)*columns)+c].compare("\\")==0 && map[((r-2)*columns)+c].compare("\\")==0 && //top and bottom 2
			map[((r-1)*columns)+(c-1)].compare("\\")==0 && map[((r-1)*columns)+(c+1)].compare("\\")==0 && //top diagonals
			map[((r+1)*columns)+(c-1)].compare("\\")==0 && map[((r+1)*columns)+(c+1)].compare("\\")==0 //bottom diagonals
		);
	}
}

void MapCreator::save()
{
	std::string outFileName = "maplevel";
	outFileName += std::to_string(mapLevel);
	std::ofstream saveFile(outFileName, std::ios::trunc);
	if (!saveFile)
	{
		std::cout << "Error saving the maps!";
	}
	else
	{
		saveFile << "#" << rows << "$" << columns;
		saveFile << "\n";
		for (int i=0; i<rows; i++)
		{
			for (int j=0; j<columns; j++)
			{
				saveFile << map[(i*j)+j];
			}
			saveFile << "\n";
		}
	}
	saveFile.close();
}

void MapCreator::addObstacles()
{
	//todo
}
