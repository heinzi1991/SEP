//------------------------------------------------------------------------------
// Filename:		Move.cpp
// Description:     Class representing a general command
// Authors:         Karim Koutp             (1314710)
//					Tina Promitzer			(1311885)
//					Martin Zagar			(1131246)
// Tutor:			Christoph Maurer
// Group:			6
// Created:			18.03.2016
// Last change:     25.03.2016
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
    if(board.getLoadMode() == false)
    {
        std::cout << "Error: No maze loaded." << std::endl;
        return 1;
    }
    
    if(board.getCurrentSteps() == 0)
    {
        std::cout << "Error: No more steps possible." << std::endl;
        board.resetTheMaze();
        return 1;
    }
    
    if (params.size() == 3)
    {
        if(params[1] == "down" || params[1] == "up" || params[1] == "right"
           || params[1] == "left")
        {
            board.setFastMove(false);
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