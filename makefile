SavingAlberta: MapCreator.o Map.o Character.o Game.o Driver.o
	g++ -Wall -std=c++0x -o SavingAlberta MapCreator.o Map.o Character.o Game.o Driver.cpp

Driver.o: Driver.cpp MapCreator.h game.h
	g++ -Wall -c -std=c++0x -o Driver.o Driver.cpp

MapCreator.o: MapCreator.cpp MapCreator.h
	g++ -Wall -c -std=c++0x -o MapCreator.o MapCreator.cpp

Map.o: Map.cpp Map.h
	g++ -Wall -c -std=c++0x -o Map.o Map.cpp

Character.o: character.cpp character.h
	g++ -Wall -c -std=c++0x -o Character.o character.cpp

Game.o: game.cpp game.h Map.h character.h
	g++ -Wall -c -std=c++0x -o Game.o game.cpp

Clean: 
	\rm *.o *~ SavingAlberta.o