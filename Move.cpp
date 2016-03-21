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

#include "Move.h"
#include "Game.h"

//------------------------------------------------------------------------------
Move::~Move()
{
    
}

//------------------------------------------------------------------------------
Move::Move(std::string name) : Command(name)
{
    
}

//------------------------------------------------------------------------------
int Move::execute(Game &board, std::vector<std::string> &params)
{
    if (params.size() == 3)
    {
        if(params[1] == "down" || params[1] == "up" || params[1] == "right" || params[1] == "left")
        {
            board.makeMoveInDirection(params[1]);
        }
        else
        {
            std::cout << "Error: Wrong parameter." << std::endl;
        }
    }
    else
    {
        std::cout << "Error: Wrong parameter count!" << std::endl;
    }
    
    return 1;
}