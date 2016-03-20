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
    if (params.size() == 2)
    {
        //std::cout << "Show Befehl ohne Parameter." << std::endl;
        board.showMaze("noMore");
        
    }
    else if (params.size() == 3)
    {
        //std::cout << "Show Befehl mit <more> Parameter." << std::endl;
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