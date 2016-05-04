//------------------------------------------------------------------------------
// Filename:				Reset.cpp
// Description:
// Authors:					Tina Promitzer			(1311885)
//									Martin Zagar			(1131246)
// Tutor:						Christoph Maurer
// Group:						6
// Created:					18.03.2016
// Last change:     04.05.2016
//------------------------------------------------------------------------------

#include "Reset.h"
#include "Game.h"

//------------------------------------------------------------------------------
Reset::~Reset()
{
	
}

//------------------------------------------------------------------------------
Reset::Reset(std::string name) : Command(name)
{
	
}

//------------------------------------------------------------------------------
int Reset::execute(Game &board, std::vector <std::string> &params)
{
	if (params.size() == 2)
	{
		if (board.getLoadMode() == false)
		{
			std::cout << "[ERR] No maze loaded." << std::endl;
			return 1;
		}
		
		board.resetTheMaze();
	}
	else
	{
		std::cout << "[ERR] Wrong parameter count." << std::endl;
	}
	
	return 1;
}