#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class Player
{
private:
	int wins;
	int losses;
	int draws;
	string name;

public:

	/*
	The constructor and deconstructor for objects of type Player.

	@param inName: The name of the new player.
	*/
	Player(string inName);
	virtual ~Player();

	/*
	getName returns the name of the player.
	
	@return: The name of the player
	*/
	string getName();
	
	/*
	getWins returns the number of wins the player has had.

	@return: The number of wins the player has had.
	*/
	int getWins();

	/*
	getLosses returns the number of losses the player has had.

	@return: The number of losses the player has had.
	*/
	int getLosses();

	/*
	getWins returns the number of draws the player has had.

	@return: The number of draws the player has had.
	*/
	int getDraws();

	/*
	tie increments the number for number of ties.

	@return: VOID
	*/
	void tie();

	/*
	loser increments the number for number of losses.

	@return: VOID
	*/
	void loser();

	/*
	winner increments the number for number of wins.

	@return: VOID
	*/
	void winner();

	/*
	toString returns a single string containing all player informtaion
	
	@return: A data string about this player
	*/
	string toString();
	
	/*
	getRPSThrow Randomly generates an integer between 0-2 and returns that number.

	@return: an integer between 0-2
	*/
	int getRPSThrow();
	
	/*
	getWinRecord returns calculates the percent wins and returns that as a decimal.

	@return: The proportion of wins as a decimal.
	*/
	double getWinRecord();

};