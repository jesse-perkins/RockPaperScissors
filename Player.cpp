#include "Player.h"

using namespace std;

Player::Player(string inName)
{
	wins = 0;
	losses = 0;
	draws = 0;
	name = inName;
}
Player::~Player(){};

string Player::getName()
{
	return name;
}

int Player::getWins()
{
	return wins;
}

int Player::getDraws()
{
	return draws;
}

int Player::getLosses()
{
	return losses;
}
void Player::tie()
{
	draws++;
}
void Player::loser()
{
	losses++;
}
void Player::winner()
{
	wins++;
}
double Player::getWinRecord()
{
	double winLoss = 0;
	if (this->losses + this->wins + this->draws > 0)
	{
		winLoss = (this->wins * 1.0) / ((this->losses + this->wins + this->draws)*1.0);
	}
	return winLoss;
}
string Player::toString()
{
	string name = this->getName();
	int currentWins = this->getWins();
	int currentLosses = this->getLosses();
	int currentDraws = this->getDraws();
	double winPercent = this->getWinRecord();
	stringstream ss;
	ss << "PLAYER NAME: " << name << endl
		<< "Wins:\t" << currentWins << endl
		<< "Draws:\t" << currentDraws << endl
		<< "Losses:\t" << currentLosses << endl
		<< "% Wins:\t" << (winPercent * 100 )<< "%\n\n";
	return ss.str();
}

int Player::getRPSThrow()
{
	return (rand() % 3);
}