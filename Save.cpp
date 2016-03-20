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
    if (params.size() == 3)
    {
        //std::cout << "Save Befehl mit diesem Parameter: " << params[1] << std::endl;
        board.saveFile(params[1]);
    }
    else
    {
        std::cout << "Error: Wrong parameter count!" << std::endl;
    }
    
    return 1;
}