#ifndef SHOW_H
#define SHOW_H

#include "Command.h"
#include <string>
#include <vector>
#include <iostream>


class Game;

class Command;

class Show : public Command
{
	
public:
	//--------------------------------------------------------------------------
	// Quit::Quit() constructor
	// @param none
	// @return none
	//
	Show();
	
	Show(std::string name);
	
	//--------------------------------------------------------------------------
	// Quit::execute() method
	// Quits the game
	// @param Game &board
	// @param std::vector<std::string> &params
	// @return int 0 at program quit
	// @return int 1 if wrong number of parameters have been input
	//
	virtual int execute(Game &board, std::vector<std::string> &params);
	
	//--------------------------------------------------------------------------
	// Quit::Quit() destructor
	// @param none
	// @return none
	//
	virtual ~Show();
	
};

#endif
