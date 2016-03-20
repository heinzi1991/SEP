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
        std::cout << "Debug Mode - Überprüfung des zweiten Parameters" << std::endl;
    
    }
    
    if(argc == 5)
    {
        std::cout << "Debug Mode - Alle Parameter wurden eingetragen" << std::endl;
        
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