//------------------------------------------------------------------------------
// Filename:		Reset.cpp
// Description:     Class representing a general command
// Authors:         Karim Koutp             (1314710)
//					Tina Promitzer			(1311885)
//					Martin Zagar			(1131246)
// Tutor:			Christoph Maurer
// Group:			6
// Created:			18.03.2016
// Last change:     25.03.2016
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
int Reset::execute(Game &board, std::vector<std::string> &params)
{
    if(board.getLoadMode() == false)
    {
        std::cout << "Error: No maze loaded." << std::endl;
        return 1;
    }
    
    if (params.size() == 2)
    {
        std::cout << "Reset Befehl." << std::endl;
        board.resetTheMaze();
        
    }
    else
    {
        std::cout << "Error: Wrong parameter count!" << std::endl;
    }
    
    return 1;
}