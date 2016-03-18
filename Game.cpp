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

#include <iostream>
#include <string>
#include <map>
#include <sstream>


#include "Game.h"
#include "Command.h"
#include "Load.h"
#include "Save.h"
#include "Fastmove.h"
#include "Move.h"
#include "Show.h"
#include "Reset.h"
#include "Quit.h"




//------------------------------------------------------------------------------
Game::Game()
{
    
}


//------------------------------------------------------------------------------
Game::~Game()
{
    /*for (auto iter = possible_commands_.begin(); iter != possible_commands_.end(); ++iter)
    {
        delete iter->second;
        possible_commands_.erase(iter);
    }*/
    
}

//------------------------------------------------------------------------------
void Game::deleteCommands()
{
    for (auto iter=possible_commands_.begin();
         iter != possible_commands_.end();
         ++iter)
    {
        delete iter->second;
        possible_commands_.erase(iter);
    }
}

//------------------------------------------------------------------------------
void Game::run()
{
    enum states { ABORT = 0, KEEP_RUNNING = 1 };
    bool state = KEEP_RUNNING;
    
    std::string input_;
    initCommands();
    std::vector<std::string> splitted_input_;
    
    while (state == KEEP_RUNNING)
    {
        std::cout << "sep> ";
        getline(std::cin, input_);
        
        if (input_ != "")
        {
            splitted_input_ = splitCommand(input_);
            
            if (possible_commands_.find(splitted_input_[0]) ==
                possible_commands_.end())
            {
                std::cout << "Error: Unknown command!" << std::endl;
            }
            else
            {
                state = possible_commands_[splitted_input_[0]] ->
                execute(*this, splitted_input_);
            }
        }
    }
}


//------------------------------------------------------------------------------
std::string Game::toLower(std::string word)
{
    int difference = 'A' - 'a';
    std::string result = "";
    
    for (auto c : word)
    {
        if (c <= 'Z' && c >= 'A')
        {
            result += (c - difference);
        }
        else
        {
            result += c;
        }
    }
    return result;
}

//------------------------------------------------------------------------------
std::vector<std::string>Game::splitCommand(std::string s)
{
    std::vector<std::string> result;
    std::string word;
    std::stringstream stream(s);
    
    while (stream >> word)
    {
        result.push_back(toLower(word));
    }
    
    result.push_back(s);
    return result;
}

//------------------------------------------------------------------------------
void Game::initCommands()
{
    std::vector<Command*> command_objects_;
    
    try
    {
        Load *load_command_ = new Load("load");
        Save *save_command_ = new Save("save");
        Fastmove *fastmove_command_ = new Fastmove("fastmove");
        Move *move_command_ = new Move("move");
        Show *show_command_ = new Show("show");
        Reset *resest_command_ = new Reset("reset");
        Quit *quit_command_ = new Quit("quit");
        
        
        command_objects_ = {load_command_,
                            save_command_,
                            fastmove_command_,
                            move_command_,
                            show_command_,
                            resest_command_,
                            quit_command_};
    }
    catch (std::bad_alloc& ba)
    {
        std::cout << "Handle exception... BAD ALLOC IN initCommands" << std::endl;
    }
    
    for (auto command : command_objects_)
    {
        possible_commands_[command->getName()] = command;
    }
}