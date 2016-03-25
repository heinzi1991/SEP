//------------------------------------------------------------------------------
// Filename:		Save.cpp
// Description:     Class representing a general command
// Authors:         Karim Koutp             (1314710)
//					Tina Promitzer			(1311885)
//					Martin Zagar			(1131246)
// Tutor:			Christoph Maurer
// Group:			6
// Created:			18.03.2016
// Last change:     25.03.2016
//------------------------------------------------------------------------------

#include "Save.h"
#include "Game.h"

//------------------------------------------------------------------------------
Save::~Save()
{
    
}

//------------------------------------------------------------------------------
Save::Save(std::string name) : Command(name)
{
    
}

//------------------------------------------------------------------------------
int Save::execute(Game &board, std::vector<std::string> &params)
{
    if(board.getLoadMode() == false)
    {
        std::cout << "Error: No maze loaded." << std::endl;
        return 1;
    }
    
    if(board.getFinishMaze())
    {
        return 1;
    }
    
    if (params.size() == 3)
    {
        board.saveFile(params[1]);
    }
    else
    {
        std::cout << "Error: Wrong parameter count!" << std::endl;
    }
    
    return 1;
}