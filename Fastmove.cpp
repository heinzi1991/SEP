//------------------------------------------------------------------------------
// Filename:		Command.h
// Description:     Class representing a general command
// Authors:         Karim Koutp             (1314710)
//					Tina Promitzer			(1311885)
//					Martin Zagar			(1131246)
// Tutor:			Christoph Hack
// Group:			2
// Created:			27.03.2015
// Last change:     27.03.2015
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
int Fastmove::execute(Game &board, std::vector<std::string> &params)
{
    if(board.getLoadMode() == false)
    {
        std::cout << "Error: No maze loaded." << std::endl;
        return 1;
    }
    
    if (params.size() == 3)
    {
        board.setFastMove(true);
        board.makeMoreMoves(params[1]);
    }
    else
    {
        std::cout << "Error: Wrong parameter count!" << std::endl;
    }
    
    return 1;
}