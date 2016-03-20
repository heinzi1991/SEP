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

#include "Quit.h"

//------------------------------------------------------------------------------
Quit::~Quit()
{
    
}

//------------------------------------------------------------------------------
Quit::Quit(std::string name) : Command(name)
{
    
}

//------------------------------------------------------------------------------
int Quit::execute(Game &board, std::vector<std::string> &params)
{
    if (params.size() == 2)
    {
        std::cout << "Bye!" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Error: Wrong parameter count!" << std::endl;
        return 1;
    }
}