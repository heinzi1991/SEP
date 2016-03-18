//------------------------------------------------------------------------------
// Filename:		Command.h
// Description:     Class representing a general command
// Authors:         Karim Koutp             (1314710)
//					Tina Promitzer			(???????)
//					Martin Zagar			(1131246)
// Tutor:			Christoph Hack
// Group:			2
// Created:			27.03.2015
// Last change:     27.03.2015
//------------------------------------------------------------------------------


#ifndef GAME_H
#define GAME_H

#include <map>
#include <vector>
#include <string>


class Command;



class Game
{
private:
    std::map<std::string, Command*> possible_commands_;

    
    
    
public:
    //----------------------------------------------------------------------------
    // Game::Game() constructor
    // @param none
    // @return none
    //
    Game();
    
    //----------------------------------------------------------------------------
    // Game::Game() destructor
    // @param none
    // @return none
    //
    ~Game();
    
    //----------------------------------------------------------------------------
    // Game::run() method
    // Keeps basic program functions on while the game is running.
    // Checks for false user input.
    // @param none
    // @return none
    //
    void run();
    
    //----------------------------------------------------------------------------
    //Game::deleteCommands() method
    //
    //
    //@param none
    //@return none
    //
    void deleteCommands();
    
    //----------------------------------------------------------------------------
    // Game::initCommands() method
    // Handles user input commands
    // @param none
    // @return none
    //
    void initCommands();
    
    //----------------------------------------------------------------------------
    // Game::toLower(std::string word) method
    // Handles uppercase / lowercase string input
    // @param std::string word
    // @return std::string result
    //
    std::string toLower(std::string word);
    
    //----------------------------------------------------------------------------
    // Game::splitCommand(std::string s) method
    // @param std::string s
    // @return std::string result
    //
    std::vector<std::string>splitCommand(std::string s);
    
};

#endif