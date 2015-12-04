#include <iostream>
#include <string>
using namespace std;

//prints the outline of max screen for the player to resize their console 
void ResizeScrn(){
	for(int i=0; i<30; i++){
		if(i==0||i==29){
			cout << "|================================================================================|";
			if(i==0){
				cout << endl;
			}
		}
		if(i==14){
			cout << "|         Please resize the console so that the square fills the console.        |\n";
		}
		if(i==15){
			cout << "|                          (Press any key to continue)                           |\n";
		}
		if((i>0&&i<14)||(15>13&&i<29)){
			cout << "|                                                                                |\n";
		}
	}
	//Insert key capture stuff
}


//prints the start screen
void StartScrn(){
  /*|================================================================================|
	|                .^^^\ ../~/\        .==...==.                                   |
	|              .^\ /\  \    --------- O    O,                                    |
	|             / \  \/    ---         ,..-----,                                   |
	|            / \_\-          _,v.v^V^ ,/\^^^/                                    |
	|           | \/       /^v^V^   _,.-^^  .,,/                                     |
	|            \-\   (   \..,^^--^   .---^                                         |
	|             \--.__________.---'^^                  Saving Alberta              |
	|          .-----.__________.-------,._                                          |
	|      _,=^\                            ".                                       |
	|    .^             |||||||||||           '                                      |
	|   /  \             ||      ||   )   /    \                                     |
	|  | -      /        ||           )''\,... |                                     |
	|  | ,,../^^\        ||||||       /  /     \                                     |
	|  |^     \  \       ||          /  (      )                                     |
	|  (     \/  /\      ||         /    \/_/_/                                      |
	|   \_\_\/  |(______||||_______)|                                                |
	|                                                                                |
	|                                                                                |
	|                                                                                |
	|                                                                                |
	|                Prepare for danger as you search for Alberta and                |
	|                her kidnapers in this Gator approved adventure.                 |
	|                            (Enter any key to start)                            | 
	|                                                                                |
	|                                                                                |
	|                                                                                |
	|                                                                                |
	|                                                                                |
	|                                                                                |
	|================================================================================|*/
	cout << "|================================================================================|\n|               .^^^\\ ../~/\\        .==...==.                                    |\n|             .^\\ /\\  \\    --------- O    O,                                     |\n|            / \\  \\/    ---         ,..-----,                                    |\n|           / \\_\\-          _,v.v^V^ ,/\\^^^/                                     |\n|          | \\/       /^v^V^   _,.-^^  .,,/                                      |\n|           \\-\\   (   \\..,^^--^   .---^                                          |\n|            \\--.__________.---\'^^                  Saving Alberta               |\n|         .-----.__________.-------,._                                           |\n|     _,=^\\                            \".                                        |\n|   .^             |||||||||||           \'                                       |\n|  /  \\             ||      ||   )   /    \\                                      |\n| | -      /        ||           )\'\'\\,... |                                      |\n| | ,,../^^\\        ||||||       /  /     \\                                      |\n| |^     \\  \\       ||          /  (      )                                      |\n| (     \\/  /\\      ||         /    \\/_/_/                                       |\n|  \\_\\_\\/  |(______||||_______)|                                                 |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|                Prepare for danger as you search for Alberta and                |\n|                her kidnapers in this Gator approved adventure.                 |\n|                            (Enter any key to start)                            |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|================================================================================|";
}

//prints the level one intro screen
void Level1IntroScrn(){
	for(int i=-2; i<28; i++){
		if(i==-2||i==27){
			cout << "|================================================================================|";
			if(i==-2){
				cout << endl;
			}
		}
		if(i<0){
			cout << "|                                                                                |\n";
		}
		if(i==6){
			cout << "|                                   Chapter 1                                    |\n";
		}
		if(i==8){
			cout << "|           As the sun started to rise over the swamp, Albert the Gator          |\n";
		}
		if(i==9){
			cout << "|           awoke face down in the mud. A large bump was visible on his          |\n";
		}
		if(i==10){
			cout << "|           head, but he couldn't remember what had happened the night           |\n";
		}
		if(i==11){
			cout << "|           before (like most college kids). He looked around for a              |\n";
		}
		if(i==12){
			cout << "|           moment and realized that Princess Alberta was nowhere to             |\n";
		}
		if(i==13){
			cout << "|           be found. In her place he found a note saying \"Chomp on              |\n";
		}
		if(i==14){
			cout << "|           that\". Determined and Angry, Albert departed the swamp.              |\n";
		}
		if(i==15){
			cout << "|           He knew exactly where to start looking.                              |\n";
		}
		if(i==16){
			cout << "|                          (Enter any key to continue)                           |\n";
		}
		if((i>0&&i<6)||i==7||(i>16&&i<27)){
			cout << "|                                                                                |\n";
		}
	}
	cout<<endl; 
	string s;
	cin>>s;
}

//prints the level 2 intro screen
void Level2IntroScrn(){
	for(int i=-2; i<28; i++){
		if(i==-2||i==27){
			cout << "|================================================================================|";
			if(i==-2){
				cout << endl;
			}
		}
		if(i==7){
			cout << "|                                   Chapter 2                                    |\n";
		}
		if(i==9){
			cout << "|           As the Dragon fell to its side it called out, \"Your dear             |\n";
		}
		if(i==10){
			cout << "|           princess isn't here. If you wish to find her you must                |\n";
		}
		if(i==11){
			cout << "|           venture into the jungle, it is only there where you will             |\n";
		}
		if(i==12){
			cout << "|           discover her fate!\" The dragon then disappeared into a               |\n";
		}
		if(i==13){
			cout << "|           cloud of smoke and Albert continued on his journey,                  |\n";
		}
		if(i==14){
			cout << "|                           this time into the jungle.                           |\n";
		}
		if(i==15){
			cout << "|                          (Enter any key to continue)                           |\n";
		}
		if((i>-2&&i<7)||i==8||(i>15&&i<27)){
			cout << "|                                                                                |\n";
		}
	}
	cout<<endl;                        
	string s;
	cin>>s;
}


//prints the level 3 intro screen
void Level3IntroScrn(){
	for(int i=-2; i<28; i++){
			if(i==-2||i==27){
				cout << "|================================================================================|";
				if(i==-2){
					cout << endl;
				}
			}
			if(i==7){
				cout << "|                                    Chapter 3                                    |\n";
			}
			if(i==9){
				cout << "|           Bubbles jumped back and yelled, \"Oh no, Bubbles don't get            |\n";
			}
			if(i==10){
				cout << "|           payed enough for this, baby. The guy who took your girl              |\n";
			}
			if(i==11){
				cout << "|           went through that portal. I'm out of here!\" Then Bubbles             |\n";
			}
			if(i==12){
				cout << "|           vanished out the window and Albert was one step closer to            |\n";
			}
			if(i==13){
				cout << "|           Alberta. He stepped through the portal and into a strange            |\n";
			}
			if(i==14){
				cout << "|           land where he hoped to find his precious princess.                   |\n";
			}
			if(i==15){
				cout << "|                          (Enter any key to continue)                           |\n";
			}
			if((i>-2&&i<7)||i==8||(i>15&&i<27)){
				cout << "|                                                                                |\n";
			}
		}
	cout<<endl;                        
	string s;
	cin>>s;
}


//prints the beat the game screen
void BeatGameScrn(){
	for(int i=-2; i<28; i++){
			if(i==-2||i==27){
				cout << "|================================================================================|";
				if(i==-2){
					cout << endl;
				}
			}
			if(i==8){
				cout << "|                                Congratulations!                                |\n";
			}
			if(i==10){
				cout << "|           With the Seminole King defeated, Princess Alberta                    |\n";
			}
			if(i==11){
				cout << "|           was finally safe and the swamp returned to its once                  |\n";
			}
			if(i==12){
				cout << "|           peaceful self. The two Gators could at last return                   |\n";
			}
			if(i==13){
				cout << "|           home and live happily ever after.                                    |\n";
			}
			if(i==15){
				cout << "|                                    THE END!                                    |\n";
			}
			if((i>-2&&i<8)||i==9||i==14||(i>15&&i<27)){
				cout << "|                                                                                |\n";
			}
		}

	cout<<endl;                        
	string s;
	cin>>s;
}

//prints 50 blank lines to clear screen
void ClearScrn(){
	for(int i=0; i<50; i++){
		cout << endl;
	}
}

//prints the level up screen
void LevelUpScrn(){
	for(int i=-2; i<28; i++){
		if(i==-2||i==27){
			cout << "|================================================================================|";
			if(i==-2){
				cout << endl;
			}
		}
		if(i==11){
			cout << "|                                Congratulations!                                |\n";
		}
		if(i==13){
			cout << "|                               You've leveled up!                               |\n";
		}
		if(i==14){
			cout << "|                          (Enter any key to continue)                           |\n";
		}
		if((i>-2&&i<11)||i==12||(i>14&&i<27)){
			cout << "|                                                                                |\n";
		}
	}
	
	cout<<endl;                        
	string s;
	cin>>s;
}

//prints the game over screen
bool GameOverScrn(){

		for(int i=-2; i<28; i++){
			if(i==-2||i==27){
				cout << "|================================================================================|";
				if(i==-2){
					cout << endl;
				}
			}
			if(i==10){
				cout << "|                                   Game Over!                                   |\n";
			}
			if(i==12){
				cout << "|                                Sorry, you died.                                |\n";
			}
			if(i==13){
				cout << "|                                   Continue?                                    |\n";
			}
			if(i==14){
				cout << "|                                (1.Yes / 2. No)                                 |\n";
			}
			if((i>-2&&i<10)||i==11||(i>14&&i<27)){
				cout << "|                                                                                |\n";
			}
		}
		bool cont=true;
		cout<<endl; 
	while(1){
		string s;
		cin>>s;
		char c =s[0];
		int i= c-'0';
		if(i==1){
			return cont;
		}
		if(i==2){
			cont=false;
			return cont;
		}
		else{
				cout<<"Invalid input. Continue? (1.Yes / 2. No) "<<endl;
		}
	}
		
}