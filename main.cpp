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

#include <iostream>
#include <string>

#include "Game.h"
#include "Quit.h"



//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//

int main(int argc, char **argv)
{
    Game pokemon;
    
    
    if(argc == 3)
    {
        if (strcmp(argv[1], "-s") == 0)
        {
            pokemon.setSaveMode(true);
            pokemon.setSaveFileName(argv[2]);
            
        }
        else if (strcmp(argv[1], "-m") == 0)
        {
            pokemon.setLoadMode(true);
            pokemon.loadFile(argv[2]);
        }
        else
        {
            std::cout << "Wrong usage: ./basic [-s <filename1>] [-m <filename2>]" << std::endl;
            return 2;
        }
    }
    
    if(argc == 5)
    {
        pokemon.setLoadMode(true);
        pokemon.setSaveMode(true);
    }
    
    if(argc == 4 || argc == 2)
    {
        std::cout << "Wrong usage: ./basic [-s <filename1>] [-m <filename2>]" << std::endl;
        return 2;
    }
    
    try
    {
        pokemon.run();
    }
    catch(std::bad_alloc& ba)
    {
        std::cout << "Error: Out of memory!" << std::endl;
    }
    
    return 0;
}