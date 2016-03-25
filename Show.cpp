//------------------------------------------------------------------------------
// Filename:		Show.cpp
// Description:     Class representing a general command
// Authors:         Karim Koutp             (1314710)
//					Tina Promitzer			(1311885)
//					Martin Zagar			(1131246)
// Tutor:			Christoph Maurer
// Group:			6
// Created:			18.03.2016
// Last change:     25.03.2016
//------------------------------------------------------------------------------

#include "Show.h"
#include "Game.h"

//------------------------------------------------------------------------------
Show::~Show()
{
    
}

//------------------------------------------------------------------------------
Show::Show(std::string name) : Command(name)
{
    
}

//------------------------------------------------------------------------------
int Show::execute(Game &board, std::vector<std::string> &params)
{
    if(board.getLoadMode() == false)
    {
        std::cout << "Error: No maze loaded." << std::endl;
        return 1;
    }
    
    
    
    
    if (params.size() == 2)
    {
        board.showMaze("noMore");
        
    }
    else if (params.size() == 3)
    {
        if(params[1] == "more")
        {
            board.showMaze("more");
        }
        else
        {
            std::cout<< "Error: Wrong parameter." << std::endl;
        }
        
    }
    else
    {
        std::cout << "Error: Wrong parameter count!" << std::endl;
    }
    
    return 1;
}