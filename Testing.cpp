
int horizontalPad; 
int verticalPad;


printMap()
{
	for (int i=0; i<verticalPad; i++)
	{
		std::cout << "\n";
	}

	for (int i=0; i<rows; i++)
	{
		for (int p=0; p<horizontalPad; p++)
		{
			std::cout << " ";
		}
		for (int j=0; j<columns; j++)
		{
			std::cout << map[i][j];
		}
	}
}