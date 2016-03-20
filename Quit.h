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

#ifndef QUIT_H
#define QUIT_H

#include "Command.h"
#include <string>
#include <vector>
#include <iostream>



class Game;
class Command;

class Quit : public Command
{
    
public:
    //----------------------------------------------------------------------------
    // Quit::Quit() constructor
    // @param none
    // @return none
    //
    Quit();
    
    Quit(std::string name);
    
    //----------------------------------------------------------------------------
    // Quit::execute() method
    // Quits the game
    // @param Game &board
    // @param std::vector<std::string> &params
    // @return int 0 at program quit
    // @return int 1 if wrong number of parameters have been input
    //
    virtual int execute(Game& board, std::vector<std::string>& params);
    
    //----------------------------------------------------------------------------
    // Quit::Quit() destructor
    // @param none
    // @return none
    //
    virtual ~Quit();
    
};
#endif