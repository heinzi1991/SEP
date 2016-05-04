//------------------------------------------------------------------------------
// Filename:				Fastmove.cpp
// Description:
// Authors:					Tina Promitzer			(1311885)
//									Martin Zagar			(1131246)
// Tutor:						Christoph Maurer
// Group:						6
// Created:					18.03.2016
// Last change:     04.05.2016
//------------------------------------------------------------------------------

#include "Fastmove.h"
#include "Game.h"

//------------------------------------------------------------------------------
Fastmove::~Fastmove()
{
	
}

//------------------------------------------------------------------------------
Fastmove::Fastmove(std::string name) : Command(name)
{
	
}

//------------------------------------------------------------------------------
int Fastmove::execute(Game &board, std::vector <std::string> &params)
{
	/*if (board.getCurrentSteps() - (int) params[1].length() < 0 &&
			board.getCurrentSteps() > -1)
	{
		std::cout << "[ERR] Invalid move." << std::endl;
		board.resetTheMaze();
		return 1;
	}*/
	
	if (params.size() == 3)
	{
		if (board.checkFastMoveInput(params[1]) == false)
		{
			std::cout << "[ERR] Wrong parameter." << std::endl;
			return 1;
			
		}
		
		if (board.getLoadMode() == false)
		{
			std::cout << "[ERR] No maze loaded." << std::endl;
			return 1;
		}
		
		board.setFastMove(true);
		board.makeMoreMoves(params[1]);
		
	}
	else
	{
		std::cout << "[ERR] Wrong parameter count." << std::endl;
		return 1;
	}
	
	return 1;
}