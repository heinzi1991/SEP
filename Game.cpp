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
#include <fstream>


#include "Game.h"
#include "Command.h"
#include "Load.h"
#include "Save.h"
#include "Fastmove.h"
#include "Move.h"
#include "Show.h"
#include "Reset.h"
#include "Quit.h"

///Users/martinzagar/Dropbox/SEP/test.txt


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
std::string Game::getInputMoves()
{
    return input_moves_;
}

//------------------------------------------------------------------------------
int Game::getMaximumSteps()
{
    return maximum_steps_;
}

//------------------------------------------------------------------------------
int Game::getCurrentSteps()
{
    return current_steps_;
}

//------------------------------------------------------------------------------
int Game::getStartPositionX()
{
    return start_position_x_;
}

//------------------------------------------------------------------------------
int Game::getStartPositionY()
{
    return start_position_y_;
}

//------------------------------------------------------------------------------
int Game::getCurrentPositionX()
{
    return current_position_x_;
}

//------------------------------------------------------------------------------
int Game::getCurrentPositionY()
{
    return current_position_y_;
}

//------------------------------------------------------------------------------
int Game::getMazeWidth()
{
    return maze_width_;
}

//------------------------------------------------------------------------------
int Game::getMazeHeight()
{
    return maze_height_;
}








//------------------------------------------------------------------------------
void Game::setInputMoves(std::string inputMoves)
{
    input_moves_ = inputMoves;
}

//------------------------------------------------------------------------------
void Game::setMaximumSteps(int maximumSteps)
{
    maximum_steps_ = maximumSteps;
}

//------------------------------------------------------------------------------
void Game::setCurrentSteps(int currentSteps)
{
    current_steps_ = currentSteps;
}

//------------------------------------------------------------------------------
void Game::setStartPositionX(int startPositionX)
{
    start_position_x_ = startPositionX;
}

//------------------------------------------------------------------------------
void Game::setStartPositionY(int startPositionY)
{
    start_position_y_ = startPositionY;
}

//------------------------------------------------------------------------------
void Game::setCurrentPositionX(int currentPositionX)
{
    current_position_x_ = currentPositionX;
}

//------------------------------------------------------------------------------
void Game::setCurrentPositionY(int currentPositionY)
{
    current_position_y_ = currentPositionY;
}

//------------------------------------------------------------------------------
void Game::setMazeWidth(int mazeWidth)
{
    maze_width_ = mazeWidth;
}

//------------------------------------------------------------------------------
void Game::setMazeHeight(int mazeHeight)
{
    maze_height_ = mazeHeight;
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
        if(toLower(word) == "load" || toLower(word) == "save" || toLower(word) == "fastmove" || toLower(word) == "move" || toLower(word) == "show" || toLower(word) == "reset" || toLower(word) == "quit")
        {
            result.push_back(toLower(word));
        }
        else
        {
            result.push_back(word);
        }
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

//-----------------------------------------------------------------------------
void Game::loadFile(std::string fileName)
{
    int lineNumber = 0;
    std::ifstream inf(fileName);
    
    if(!inf)
    {
        
        std::cout << "Error: File could not be opened." << std::endl;
    }
    
    while (inf)
    {
        
        std::string strInput;
        getline(inf, strInput);
        
        if(lineNumber == 0)
        {
            setInputMoves(strInput);
        }
        
        if(lineNumber == 1)
        {
            setMaximumSteps(std::stoi(strInput));
        }
        
        if(strInput.length() > 0 && lineNumber >= 2) {
            
            writeInAnalyzeArray(strInput, lineNumber);
        }
        
        lineNumber++;
    }
    
    setMazeHeight(lineNumber - 3);
    
    if(checkIfValidMaze())
    {
        setCurrentSteps(getMaximumSteps());
        writeFixMaze();
    }
    else
    {
        std::cout << "fail" << std::endl;
    }
}

//--------------------------------------------------------------------------------
void Game::writeInAnalyzeArray(std::string oneLine, int lineNumber)
{
    setMazeWidth((int)oneLine.length());
    
    for(int counter = 0; counter < oneLine.length(); counter++)
    {
        analyzeMaze[lineNumber - 2][counter] = oneLine.at(counter);
    }
}

//--------------------------------------------------------------------------------
bool Game::checkIfValidMaze()
{
    
    int startFieldCounter = 0;
    int targetFieldCounter = 0;
    std::map<char, int> teleportMap;
    std::map<char, int>::iterator it;
    
    
    for(int counter = 0; counter < getInputMoves().length(); counter++)
    {
        if(getInputMoves().at(counter) != 'u' && getInputMoves().at(counter) != 'd' && getInputMoves().at(counter) != 'l' && getInputMoves().at(counter) != 'r')
        {
            std::cout << "Error: Invalid file. (inputMoves)" << std::endl;
            return false;
        }
    }

    for(int counter = 0; counter < getMazeHeight(); counter++)
    {
        for(int counter2 = 0; counter2 < getMazeWidth(); counter2++)
        {
            if(analyzeMaze[counter][counter2] == 'o')
            {
                if(startFieldCounter == 0)
                {
                    setStartPositionX(counter);
                    setStartPositionY(counter2);
                    startFieldCounter++;
                }
                else
                {
                    std::cout << "Error: Invalid file. (two startfields)" << std::endl;
                    return false;
                }
            }
            
            if(analyzeMaze[counter][counter2] == 'x')
            {
                if(targetFieldCounter == 0)
                {
                    targetFieldCounter++;
                }
                else
                {
                    std::cout << "Error: Invalid file. (two targetfields)" << std::endl;
                    return false;
                }
            }
            
            if(analyzeMaze[counter][counter2] >= 'A' && analyzeMaze[counter][counter2] <= 'Z')
            {
                teleportMap[analyzeMaze[counter][counter2]] += 1;
            }
        }
    }
    
    for(it = teleportMap.begin(); it != teleportMap.end(); it++)
    {
        if(it -> second != 2)
        {
            std::cout << "Error: Invalid file. (no two teleport)" << std::endl;
            return false;
        }
    }
    
    for(int counter = 0; counter < getMazeWidth(); counter++)
    {
        if(analyzeMaze[0][counter] != '#' || analyzeMaze[getMazeHeight() - 1][counter] != '#')
        {
            std::cout << "Error: Invalid file. (up and down hashtag)" << std::endl;
            return false;
        }
    }
    
    for(int counter; counter < getMazeHeight(); counter++)
    {
        if(analyzeMaze[counter][0] != '#' || analyzeMaze[counter][getMazeWidth() - 1] != '#')
        {
            std::cout << "Error: Invalid file. (left and right hashtag)" << std::endl;
        }
    }
    
    return true;
}

//--------------------------------------------------------------------------------
void Game::writeFixMaze()
{
    for(int counter = 0; counter < getMazeHeight(); counter++)
    {
        for(int counter2 = 0; counter2 < getMazeWidth(); counter2++)
        {
            fixMaze[counter][counter2] = analyzeMaze[counter][counter2];
        }
    }
}

//--------------------------------------------------------------------------------
void Game::showMaze(std::string parameter)
{
    if(parameter == "noMore")
    {
        for(int counter = 0; counter < getMazeHeight(); counter++)
        {
            for(int counter2 = 0; counter2 < getMazeWidth(); counter2++)
            {
                std::cout << fixMaze[counter][counter2];
            }
            
            std::cout << std::endl;
        }
    }
    else {
        
        std::cout << "Remaining Steps: " << getCurrentSteps() << std::endl;
        std::cout << "Moved Steps: " << getInputMoves() << std::endl;
        
        for(int counter = 0; counter < getMazeHeight(); counter++)
        {
            for(int counter2 = 0; counter2 < getMazeWidth(); counter2++)
            {
                std::cout << fixMaze[counter][counter2];
            }
            
            std::cout << std::endl;
        }
    }
    
    
}



