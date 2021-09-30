#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>

#include "Player.h"

using namespace std;

/*
checkIntIn takes an integer and checks to see that an integer was inputed. If cin failed pulling a non-integer,
it is cleared and -1 is returned. Otherwise, the integer is returned.

@param checkMe: the integer that is to be checked. 
@return: Either -1 or the integer that was passed in if an integer was succesfully stored initially.
*/
int checkIntIn(int checkMe)
{
	if (cin.fail())
	{
		cin.clear();
		checkMe = -1;
	}
	cin.ignore(1000, '\n');
	return checkMe;
}

/*
findPlayer finds a player in a vector of type Player* and returns the index location.

@param inVector: The vector to be searched.
@param name: the name of the player that is being looked for.
@return: The index location of the player if found. otherwise, -1.
*/
int findPlayer(vector<Player*> inVector, string name)
{
	for (int i = 0; i < inVector.size(); i++)
	{
		if (name == inVector[i]->getName())
		{
			return i;
		}
	}
	return -1;
}

/*
showPlayers displays the contents of all Player objects referenced by a vector of type Player*.

@param allPlayers: the vector of type Player* to be displayed
@return: VOID
*/
void showPlayers(vector<Player*> allPlayers)
{
	if (allPlayers.size() == 0)
	{
		cout << "\nNo Players Found.\n";
	}
	else
	{
		for (int i = 0; i < allPlayers.size(); i++)
		{
			cout << allPlayers[i]->toString();
		}
	}
	cout << endl;
	return;
}

/*
addPlayer takes a player name and checks to see if a player with an identical name is in the vector. If it is not,
a new player is added with that name. Otherwise, an error is thrown.

@param allPlayers: The vector of type Player* to be added to.
@param point: The pointer that will be used as a swap location while pointers are loaded into the vector.
@return: VOID
*/
void addPlayer(vector<Player*>& allPlayers, Player*& point)
{
	cout << "\nEnter New Player Name: ";
	string name;
	getline(cin, name);
	int playerLoc = findPlayer(allPlayers, name);
	if (playerLoc == -1)
	{
		point = new Player(name);
		allPlayers.push_back(point);
		cout << "\nPlayer Successfully Added\n\n";
	}
	else
	{
		cout << "\nERROR. NAME ALREADY IN USE. \n\n";
	}
	return;
}

/*
addToLineUp takes a name from the user and checks to see if it is in the allPlayers vector. If it is, then it is added 
to the lineUp vector. If not, an error is thrown.

@param allPlayers: The vector of type Player* that values will be taken from.
@param lineUp: The vector of type Player* to be added to
@param point: The pointer that will be used as a swap location while pointers are loaded into the vector.
@return: VOID
*/
void addToLineUp(vector<Player*>& allPlayers, vector<Player*>& lineUp, Player* point)
{
	cout << "\nPlayer name to add to line-up: ";
	string name;
	getline(cin, name);
	int playerLoc = findPlayer(allPlayers, name);
	if (playerLoc == -1)
	{
		cout << "\nERROR. PLAYER NOT FOUND. \n\n";
	}
	else
	{
		point = allPlayers[playerLoc];
		lineUp.push_back(point);
		cout << "\nPlayer added to line-up.\n\n";
	}
	return;
}

/*
rockOrPaperOrScissors takes an integer and checks to see if it is 0, 1, or 2. It then returns a string value of rock,
paper or scissors based on that integer.

@param value: the integer that is to be checked.
@return: a string of "rock", "paper", or"scissors"
*/
string rockOrPaperOrScissors(int value)
{
	const int ROCK = 0;
	const int PAPER = 1;
	if (value == ROCK)
	{
		return "rock";
	}
	else if (value == PAPER)
	{
		return "paper";
	}
	else
	{
		return "scissors";
	}
}

/*
letTheBattleBegin takes the first two players in the vector of type Player* and has them randomly select an RPS 
throw. The throws are compared and wins, losses and ties are incremented accordingly. If the same player is in 
the queue twice, it is an automatic tie. The players are then removed from the contender vector.

@param lineUp: The vector of type Player* that supplies players to battle.
@return: VOID
*/
void letTheBattleBegin(vector<Player*>& contenders)
{
	const int PLAYERS_PER_MATCH = 2;
	if (contenders.size() < PLAYERS_PER_MATCH)
	{
		cout << "\nERROR. INSUFFICIENT NUMBER OF PLAYERS\n\n";
		return;
	}
	const string ROCK = "rock";
	const string PAPER = "paper";
	const string SCISSORS = "scissors";
	Player* first = contenders[0];
	Player* second = contenders[1];
	string firstThrow = "";
	string secondThrow = "";
	for (int i = 0; i < PLAYERS_PER_MATCH; i++)
	{
		for (int j = 0; j < contenders.size() - 1; j++)
		{
			contenders[j] = contenders[j + 1];
		}
		contenders.pop_back();
	}
	firstThrow = rockOrPaperOrScissors(first->getRPSThrow());
	secondThrow  = rockOrPaperOrScissors(second->getRPSThrow());
	stringstream ss;
	ss << "\nLET THE MATCH BEGIN!\n\n"
		<< first->getName() << " shouts, \"I CHOOSE YOU, " << firstThrow << "!!\"\n"
		<< second->getName() << " replies, \"I CHOOSE YOU, " << secondThrow << "!!\"\n";

	if (first == second)
	{
		first->tie();
		cout << "\nLET THE MATCH BEGIN!\n\n" << first->getName() << " vs " << first->getName() << " is an automatic tie.\n\n";
		return;
	}
	else if (firstThrow == secondThrow)
	{
		first->tie();
		second->tie();
		cout << ss.str() << "\nIt's " << firstThrow << " vs. " << secondThrow << ". . . A clear tie.";
	}
	else if (firstThrow == ROCK && secondThrow == SCISSORS)
	{
		first->winner();
		second->loser();
		cout << ss.str() << endl << first->getName() << "'s " << firstThrow << " uses CRUSH. It's super-effective. " 
			<< second->getName() << "'s " << secondThrow << " have been defeated.";
	}
	else if (firstThrow == SCISSORS && secondThrow == ROCK)
	{
		first->loser();
		second->winner();
		cout << ss.str() << endl << second->getName() << "'s " << secondThrow << " uses CRUSH. It's super-effective. "
			<< first->getName() << "'s " << firstThrow << " have been defeated.";
	}
	else if (firstThrow == PAPER && secondThrow == ROCK)
	{
		first->winner();
		second->loser();
		cout << ss.str() << endl << first->getName() << "'s " << firstThrow << " uses COVER. It's super-effective. "
			<< second->getName() << "'s " << secondThrow << " has been defeated.";
	}
	else if (firstThrow == ROCK && secondThrow == PAPER)
	{
		first->loser();
		second->winner();

		cout << ss.str() << endl << second->getName() << "'s " << secondThrow << " uses COVER. It's super-effective. "
			<< first->getName() << "'s " << firstThrow << " has been defeated.";
	}
	else if (firstThrow == SCISSORS && secondThrow == PAPER)
	{
		first->winner();
		second->loser();
		cout << ss.str() << endl << first->getName() << "'s " << firstThrow << " uses CUT. It's super-effective. "
			<< second->getName() << "'s " << secondThrow << " has been defeated.";
	}
	else if (firstThrow == PAPER && secondThrow == SCISSORS)
	{
		first->loser();
		second->winner();
		cout << ss.str() << endl << second->getName() << "'s " << secondThrow << " uses CUT. It's super-effective. "
			<< first->getName() << "'s " << firstThrow << " has been defeated.";
	}
	cout << "\n\n";
}


/*
main contains the main menu for the program.

@return: 0, if the program closes successfully.
*/
int main()
{
	srand(time(NULL));
	Player* p = NULL;
	vector<Player*> allPlayers;
	vector<Player*> contenders;
	int menuSelect = 0;
	while (menuSelect != 6)
	{
		cout << "* * * MAIN MENU * * *\n\n"
			<< "1 - Show Players\n"
			<< "2 - Add Player\n"
			<< "3 - Add To Line-up\n"
			<< "4 - Show Line-up\n"
			<< "5 - Fight\n"
			<< "6 - Quit\n"
			<< "Please Select a Menu Option [1-6]: ";
		cin >> menuSelect;
		menuSelect = checkIntIn(menuSelect);
		switch (menuSelect)
		{
		case 1:
			cout << "\n* * * Show Players and Stats * * *\n";
			showPlayers(allPlayers);
			break;
		case 2:
			cout << "\n* * * Add Player * * *\n";
			addPlayer(allPlayers, p);
			break;
		case 3:
			cout << "\n* * * Add To Line-up * * *\n";
			addToLineUp(allPlayers, contenders, p);
			break;
		case 4:
			cout << "\n* * * Show Line-up * * *\n";
			showPlayers(contenders);
			break;
		case 5:
			cout << "\n* * * Fight * * *\n";
			letTheBattleBegin(contenders);
			break;
		case 6:
			cout << "\nThanks for playing! Goodbye.";
			break;
		default:
			cout << "\n\nINVALID INPUT. Returning to main menu.... \n\n";
			break;
		}
	}
	return 0;
}