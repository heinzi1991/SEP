//------------------------------------------------------------------------------
// Filename:				Load.cpp
// Description:
// Authors:					Tina Promitzer			(1311885)
//									Martin Zagar			(1131246)
// Tutor:						Christoph Maurer
// Group:						6
// Created:					18.03.2016
// Last change:     04.05.2016
//------------------------------------------------------------------------------

#include "Game.h"
#include "Load.h"

//------------------------------------------------------------------------------
Load::~Load()
{
	
}

//------------------------------------------------------------------------------
Load::Load(std::string name) : Command(name)
{
	
}

//------------------------------------------------------------------------------
int Load::execute(Game &board, std::vector <std::string> &params)
{
	if (params.size() == 3)
	{
		board.loadFile(params[1]);
	}
	else
	{
		std::cout << "[ERR] Wrong parameter count." << std::endl;
	}
	
	return 1;
}