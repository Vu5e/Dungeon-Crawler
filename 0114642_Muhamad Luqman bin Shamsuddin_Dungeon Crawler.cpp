#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int row = 10;
const int col = 10;
const int traps = 6;
const int monsters = 6;
string dungeonBoard[row][col];
int playerPosition[2];
int trapPosition[traps][2];
int monsterPosition[monsters][2];

void InitDungeon();
void DisplayDungeon();
void SpawnTraps();
void SpawnMonsters();
void MonsterMovement();
void PlayerMovement(string key);
void DisplayTitle();

bool PlayerMovementCheck(string key);
bool HitTrapOrMonster();
 
int main() 
{
	bool isExit = false;
	
	do
	{
		srand(time(NULL));
		InitDungeon();
		SpawnTraps();
		SpawnMonsters();
		dungeonBoard[0][0] = " P";
		playerPosition[0] = 0;
		playerPosition[1] = 0;
		dungeonBoard[9][9] = " X";
		int counter = 0;
		
		while(true)
		{
			DisplayTitle();
			DisplayDungeon();
			cout << endl;
			
			cout << "Steps :" << counter << endl;
			cout << "Choose which direction you want to move by (W/A/S/d):";
			string k;
			cin >> k;
			
			while(!PlayerMovementCheck(k))
			{
				cout << "Wrong input, please try again with (W/A/S/D):";
				cin >> k;
			}
			
			int oldPlayerPos[2];
			for(int i = 0; i < 2; i++)
			{
				oldPlayerPos[i] = playerPosition[i];
			}
			
			PlayerMovement(k);
			
			if(HitTrapOrMonster())
				break;
				
			else if (playerPosition[0] == 9 && playerPosition[1] == 9)
			{
				cout << endl << "The treasure has been found by you, but no celebration cause you are forever alone." << "Completed in g" << counter + 1 << " steps!" << endl;
				break;
			}
			
			if((oldPlayerPos[0] != playerPosition[0]) || (oldPlayerPos[1] != playerPosition[1]))
			{
				counter++;
				MonsterMovement();
			}
			system("cls");
		}
		
		cout << "Do you want to play again? (Y/N):";
		string k;
		cin >> k;
		cout << endl;
		
		if (k != "y" && k != "Y")
		{
			cout << "Please play again if you want to be a loner!" << endl;
			isExit = true;
		}
		else
			system("cls");
			
	}while(!isExit);
	
	system("pause");
	return 0;
}

void InitDungeon()
{
	for(int i = 0; i < col; i++)
	{
		for (int j = 0; j <row; j++)
		{
			dungeonBoard[j][i] = " -";
		}
	}
}

void DisplayDungeon()
{
	for(int i = 0; i < col; i++)
	{
		for (int j = 0; j <row; j++)
		{
			cout << dungeonBoard[j][i];
		}
		cout << endl;
	}
}

void SpawnTraps()
{
	for (int i = 0; i < traps; i++)
	{
		
		bool isExit = false;
		do
		{
			int x = rand() % (row - 2) + 1;
			int y = rand() % (col - 2) + 1;
			
			if(dungeonBoard[x][y] == " -")
			{
				dungeonBoard[x][y] = " T";
				trapPosition[i][0] = x;
				trapPosition[i][1] = y;
				isExit = true;
			}
			
		}while(!isExit);
	}
}

void SpawnMonsters()
{
	for (int i = 0 ; i < monsters; i++)
	{
		bool isExit = false;
		
		do
		{
			int x = rand() % (row - 2) + 1;
			int y = rand() % (row - 2) + 1;
			
			if(dungeonBoard[x][y] == " -")
			{
				dungeonBoard[x][y] = " M";
				monsterPosition[i][0] = x;
				monsterPosition[i][1] = y;
				isExit = true;
			}
		}while(!isExit);
	}
}

void MonsterMovement()
{
	for(int i = 0; i < monsters; i++)
	{
		dungeonBoard[monsterPosition[i][0]][monsterPosition[i][1]] = " -";
	}
	SpawnMonsters();
}

void PlayerMovement(string input)
{
	if (input == "w" || input == "W")
	{
		dungeonBoard[playerPosition[0]][playerPosition[1]] = " -";
		playerPosition[1] -= 1;
		dungeonBoard[playerPosition[0]][playerPosition[1]] = " P";
	}
	else if (input == "a" || input == "A")
	{
		dungeonBoard[playerPosition[0]][playerPosition[1]] = " -";
		playerPosition[0] -= 1;
		dungeonBoard[playerPosition[0]][playerPosition[1]] = " P";
	}
	else if (input == "s" || input == "S")
	{
		dungeonBoard[playerPosition[0]][playerPosition[1]] = " -";
		playerPosition[1] += 1;
		dungeonBoard[playerPosition[0]][playerPosition[1]] = " P";
	}
	else if (input == "d" || input == "D")
	{
		dungeonBoard[playerPosition[0]][playerPosition[1]] = " -";
		playerPosition[0] += 1;
		dungeonBoard[playerPosition[0]][playerPosition[1]] = " P";
	}
}


bool PlayerMovementCheck(string input)
{
	if ((input == "w" || input == "W") && playerPosition[1] == 0)
	{
		cout << "This is the most top you can ever reach in your life." << endl;
		cout << "Please choose the other direction." << endl;
		return false;
	}
	else if ((input == "a" || input == "A") && playerPosition[0] == 0)
	{
		cout << "This the most left you can ever reach in your life." << endl;
		cout << "Please choose other direction." << endl;
		return false;
	}
	else if ((input == "s" || input == "S") && playerPosition[1] == 9)
	{
		cout << "You have reach the bottom of your life." << endl;
		cout << "Please choose other direction." << endl;
		return false;
	}
	else if ((input == "d" || input == "D") && playerPosition[0] == 9)
	{
		cout << "You have reached the right way of your life but still stuck." << endl;
		cout << "Pity but please choose other direction." << endl;
		return false;
	}
	
	return true;	
}

bool HitTrapOrMonster()
{
	for(int i = 0; i < traps; i ++)
	{
		if ((playerPosition[0] == trapPosition[i][0]) && (playerPosition[1] == trapPosition[i][1]))
		{
			cout << endl << "Fallen into the trap and you lost your legs, dead from shock!" << endl;
			return true;
		}
	}
	
	for(int j = 0; j < monsters; j++)
	{
		if ((playerPosition[0] == monsterPosition[j][0]) && (playerPosition[1] == monsterPosition[j][1]))
		{
			cout << endl << "Monsters from the other realm and you're dead!" << endl;
			return true;
		}
	}
	
	return false;
}

void DisplayTitle()
{
	cout << "==============================" << endl;
	cout << ">>                          <<" << endl;
	cout << " >>                        << " << endl;
	cout << "  >>    DUNGEON CRAWLER   <<  " << endl;
	cout << " >>         Not for        << " << endl;
	cout << ">>           NOOBS          <<" << endl;
	cout << "==============================" << endl;
	cout << endl;
}

