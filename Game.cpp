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
bool Game::getLoadMode()
{
    return load_mode_;
}



//------------------------------------------------------------------------------
void Game::setLoadMode(bool loadMode)
{
    load_mode_ = loadMode;
}

//------------------------------------------------------------------------------
void Game::setSaveMode(bool saveMode)
{
    save_mode_ = saveMode;
}

//------------------------------------------------------------------------------
void Game::setSaveFileName(std::string saveFileName)
{
    save_file_name_ = saveFileName;
}

void Game::setFastMove(bool fastMoveMode)
{
    fast_move_activeted_ = fastMoveMode;
}













//------------------------------------------------------------------------------
void Game::deleteCommands()
{
    for (auto iter = possible_commands_.begin();
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

//------------------------------------------------------------------------------
void Game::loadFile(std::string fileName)
{
    if(fileName.length() > 255)
    {
        std::cout << "Error: Wrong parameter." << std::endl;
        return;
    }
    
    for(int counter = 0; counter < fileName.length(); counter++)
    {
        if((fileName.at(counter) >= 32 &&  fileName.at(counter) < 46) || (fileName.at(counter) >= 58 && fileName.at(counter) < 65) || (fileName.at(counter) > 90 && fileName.at(counter) < 97) || (fileName.at(counter) > 122 && fileName.at(counter) < 127))
        {
            std::cout << "Error: Wrong parameter." << std::endl;
            return;
        }
    }
    

    int lineNumber = 0;
    std::ifstream inf(fileName);
    
    if(!inf)
    {
        std::cout << "Error: File could not be opened." << std::endl;
        return;
    }
    
    while (inf)
    {
        std::string strInput;
        getline(inf, strInput);
        
        if(lineNumber == 0)
        {
            input_moves_ = strInput;
        }
        
        if(lineNumber == 1)
        {
            maximum_steps_ = std::stoi(strInput);
        }
        
        if(strInput.length() > 0 && lineNumber >= 2) {
            
            writeToCheckMap(strInput, lineNumber);
        }
        
        lineNumber++;
    }
    
    maze_height_ = (int)check_map_.size();
    
    if(checkIfValidMaze())
    {
        if(fix_game_map_.size() == 0)
        {
            load_mode_ = true;
            writeFixMaze();
        }
        else
        {
            fix_game_map_.clear();
            load_mode_ = true;
            writeFixMaze();
        }
        
        current_steps_ = maximum_steps_;
        current_position_x_ = start_position_x_;
        current_position_y_ = start_position_y_;
        
        saveAllTeleports();
        
        if(input_moves_.length() > 0)
        {
            if(checkIfValidPath(input_moves_))
            {
                current_steps_ = maximum_steps_ - (int)input_moves_.length();
                showMaze("noMore");
            }
            else
            {
                load_mode_ = false;
                fix_game_map_.clear();
                std::cout << "Error: Invalid path." << std::endl;
            }
        }
        else
        {
            showMaze("noMore");
        }
    }
    else
    {
       std::cout << "Error: Invalid file." << std::endl;
    }
}

//------------------------------------------------------------------------------
void Game::saveFile(std::string fileName)
{
    if(fileName.length() > 255)
    {
        std::cout << "Error: Wrong parameter." << std::endl;
        return;
    }
    
    for(int counter = 0; counter < fileName.length(); counter++)
    {
        if((fileName.at(counter) >= 32 &&  fileName.at(counter) < 46) || (fileName.at(counter) >= 58 && fileName.at(counter) < 65) || (fileName.at(counter) > 90 && fileName.at(counter) < 97) || (fileName.at(counter) > 122 && fileName.at(counter) < 127))
        {
            std::cout << "Error: Wrong parameter." << std::endl;
            return;
        }
    }

    
    std::ofstream onf(fileName);
    
    if(onf.is_open())
    {
        onf << input_moves_ << std::endl;
        onf << maximum_steps_ << std::endl;
        
        for(int counter = 0; counter < fix_game_map_.size(); counter++)
        {
            std::vector<char> buffer = fix_game_map_.at(counter);
            
            for(int counter2 = 0; counter2 < buffer.size(); counter2++)
            {
                onf << buffer.at(counter2);
            }
            
            onf << std::endl;
        }
        
    }
    else
    {
        std::cout << "Error: File could not be written." << std::endl;
    }
    
    onf.close();
}


//------------------------------------------------------------------------------
void Game::writeToCheckMap(std::string oneLine, int lineNumber)
{
    maze_width_ = (int)oneLine.length();
    
    std::vector<char> buffer;
    
    for(int counter = 0; counter < oneLine.length(); counter++)
    {
        buffer.push_back(oneLine.at(counter));
    }
    
    check_map_.push_back(buffer);
}

//------------------------------------------------------------------------------
bool Game::checkIfValidMaze()
{
    int startFieldCounter = 0;
    int targetFieldCounter = 0;
    int tempLineCount = 0;
    int fieldCounter = 1;
    std::map<char, int> teleportMap;
    int fieldArray[] = {32, 35, 43, 60, 62, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 94, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 111, 118, 120};
    
    
    for(int counter = 0; counter < input_moves_.length(); counter++)
    {
        if(input_moves_.at(counter) != 'u' && input_moves_.at(counter) != 'd' && input_moves_.at(counter) != 'l' && input_moves_.at(counter) != 'r')
        {
            std::cout << "wrong short moves" << std::endl;
            return false;
        }
    }
    
    for(int counter = 0; counter < check_map_.size(); counter++)
    {
        if(counter == 0)
        {
            tempLineCount = (int)check_map_.at(counter).size();
        }
        
        if(tempLineCount > (int)check_map_.at(counter).size() || tempLineCount < (int)check_map_.at(counter).size())
        {
            std::cout << "lines different size" << std::endl;
            return false;
        }
    }
    
    for(int counter = 0; counter < check_map_.size(); counter++)
    {
        std::vector<char> buffer = check_map_.at(counter);
        
        for(int counter2 = 0; counter2 < buffer.size(); counter2++)
        {
            for(int counter3 = 0; counter3 < 44; counter3++)
            {
                if((int)buffer.at(counter2) == fieldArray[counter3])
                {
                    fieldCounter++;
                }
            }
        }
    }
    
    if(fieldCounter != (maze_height_ * maze_width_))
    {
        std::cout << "invalid field" << std::endl;
        return false;
    }

    
    for(int counter = 0; counter < check_map_.size(); counter++)
    {
        std::vector<char> buffer = check_map_.at(counter);
        
        for(int counter2 = 0; counter2 < buffer.size(); counter2++)
        {
            if (buffer.at(counter2) == 'o')
            {
                if(startFieldCounter == 0)
                {
                    start_position_x_ = counter;
                    start_position_y_ = counter2;
                    startFieldCounter++;
                }
                else
                {
                    std::cout << "more startfields" << std::endl;
                    return false;
                }
            }
            
            if(buffer.at(counter2) == 'x')
            {
                if(targetFieldCounter == 0)
                {
                    targetFieldCounter++;
                }
                else
                {
                    std::cout << "more targetfields" << std::endl;
                    return false;
                }
            }
            
            if(buffer.at(counter2) >= 'A' && buffer.at(counter2) <= 'Z')
            {
                teleportMap[buffer.at(counter2)] += 1;
            }
        }
    }
    
    for(std::map<char, int>::iterator it = teleportMap.begin(); it != teleportMap.end(); it++)
    {
        if(it -> second != 2)
        {
            std::cout << "not 2 teleports" << std::endl;
            return false;
        }
    }
    
    std::vector<char> firstMazeRow = check_map_.at(0);
    std::vector<char> lastMazeRow = check_map_.at(check_map_.size() - 1);
    
    for(std::vector<char>::iterator it = firstMazeRow.begin(); it != firstMazeRow.end(); it++)
    {
        if(*it != '#')
        {
            std::cout << "first row no hashtag" << std::endl;
            return false;
        }
    }
    
    for(std::vector<char>::iterator it = lastMazeRow.begin(); it != lastMazeRow.end(); it++)
    {
        if(*it != '#')
        {
            std::cout << "last row no hashtag" << std::endl;
            return false;
        }
    }
    
    for(int counter = 0; counter < check_map_.size(); counter++)
    {
        std::vector<char> buffer = check_map_.at(counter);
        
        if(buffer.at(0) != '#' || buffer.at(buffer.size() - 1) != '#')
        {
            std::cout << "left and right no hashtag" << std::endl;
            return false;
        }
    }
    
    return true;
}

//------------------------------------------------------------------------------
bool Game::checkIfValidPath(std::string inputMoves)
{
    fast_move_activeted_ = true;
    std::map<char, std::string> directionMap;
    
    directionMap['d'] = "down";
    directionMap['u'] = "up";
    directionMap['l'] = "left";
    directionMap['r'] = "right";
    
    
    for(int counter = 0; counter < input_moves_.length(); counter++)
    {
        makeMoveInDirection(directionMap[input_moves_.at(counter)]);
    }
    
    if(fast_move_counter_ != input_moves_.length())
    {
        return false;
    }
    
    return true;
}

//------------------------------------------------------------------------------
void Game::writeFixMaze()
{
    for(int counter = 0; counter < check_map_.size(); counter++)
    {
        std::vector<char> buffer = check_map_.at(counter);
        std::vector<char> bufferIn;
        
        for(int counter2 = 0; counter2 < buffer.size(); counter2++)
        {
            bufferIn.push_back(buffer.at(counter2));
        }
        
        fix_game_map_.push_back(bufferIn);
    }
    
    check_map_.clear();
}

//------------------------------------------------------------------------------
void Game::showMaze(std::string parameter)
{
    if(parameter == "noMore")
    {
        for(int counter = 0; counter < fix_game_map_.size(); counter++)
        {
            std::vector<char> buffer = fix_game_map_.at(counter);
            
            for(int counter2 = 0; counter2 < buffer.size(); counter2++)
            {
                if(counter == current_position_x_ && counter2 == current_position_y_)
                {
                    std::cout << "*";
                }
                else
                {
                    std::cout << buffer.at(counter2);
                }
            }
            
            std::cout << std::endl;
        }
    }
    else {
        
        std::cout << "Remaining Steps: " << current_steps_ << std::endl;
        std::cout << "Moved Steps: " << input_moves_ << std::endl;
        
        for(int counter = 0; counter < fix_game_map_.size(); counter++)
        {
            std::vector<char> buffer = fix_game_map_.at(counter);
            
            for(int counter2 = 0; counter2 < buffer.size(); counter2++)
            {
                if(counter == current_position_x_ && counter2 == current_position_y_)
                {
                    std::cout << "*";
                }
                else
                {
                    std::cout << buffer.at(counter2);
                }
            }
            
            std::cout << std::endl;
        }
    }
}

//------------------------------------------------------------------------------
void Game::saveAllTeleports()
{
    std::map<char, std::pair<std::pair<int, int>, std::pair<int, int>>>::iterator it;
    std::map<char, int> testMap;
    
    for(char counter = 'A'; counter <= 'Z'; counter++)
    {
        testMap[counter] = 0;
    }

    for(int counter = 0; counter < fix_game_map_.size(); counter++)
    {
        std::vector<char> buffer = fix_game_map_.at(counter);
        
        for(int counter2 = 0; counter2 < buffer.size(); counter2++)
        {
            if(buffer.at(counter2) >= 'A' && buffer.at(counter2) <= 'Z' && testMap[buffer.at(counter2)] == 0)
            {
                testMap[buffer.at(counter2)] += 1;
                std::pair<int, int> firstTuple = std::make_pair(counter, counter2);
                std::pair<int, int> secondTuple = searchSecondPosition(counter, counter2 + 1, buffer.at(counter2));
                all_teleports_map_[buffer.at(counter2)] = std::make_pair(firstTuple, secondTuple);
            }
        }
    }
}

//------------------------------------------------------------------------------
std::pair<int, int>Game::searchSecondPosition(int firstCount, int secondCount, char searchChar)
{
    std::pair<int, int> returnPair;
    int buffCounter;
    
    for(int counter = firstCount; counter < fix_game_map_.size(); counter++)
    {
        std::vector<char> buffer = fix_game_map_.at(counter);
        
        (counter == firstCount) ? (buffCounter = secondCount) : (buffCounter = 0);
        
        for(int counter2 = buffCounter; counter2 < buffer.size(); counter2++)
        {
            if(buffer.at(counter2) == searchChar)
            {
                returnPair.first = counter;
                returnPair.second = counter2;
            }
        }
    }
    
    return returnPair;
}

//------------------------------------------------------------------------------
void Game::makeMoveInDirection(std::string direction)
{
    std::map<std::string, char> shortDirectionMap;
    
    shortDirectionMap["down"] = 'd';
    shortDirectionMap["up"] = 'u';
    shortDirectionMap["left"] = 'l';
    shortDirectionMap["right"] = 'r';
    
    /*if(current_steps_ == 0)
    {
        std::cout << "Error: No more steps possible." << std::endl;
        resetTheMaze();
        return;
    }*/
    
    
    if(checkOneWayField(direction) == false)
    {
        std::cout << "Invalid move. (onewayField)" << std::endl;
        return;
    }
    
    
    if(checkValidMove(direction))
    {
        makeOneMove(direction);
        
        if(fast_move_activeted_ == false)
        {
            input_moves_ += shortDirectionMap[direction];
            current_steps_--;
            showMaze("noMore");
        }
        else
        {
            fast_move_counter_++;
        }
    }
    else
    {
        if(fast_move_activeted_ == false)
        {
            std::cout << "Invalid move." << std::endl;
        }
    }
    
}

//------------------------------------------------------------------------------
void Game::makeMoreMoves(std::string moves)
{
    std::map<char, std::string> directionMap;
    
    directionMap['d'] = "down";
    directionMap['u'] = "up";
    directionMap['l'] = "left";
    directionMap['r'] = "right";
    
    int tempX = current_position_x_;
    int tempY = current_position_y_;
    
    
    for(int counter = 0; counter < moves.length(); counter++)
    {
        makeMoveInDirection(directionMap[moves.at(counter)]);
    }
    
    if(fast_move_counter_ == moves.length())
    {
        input_moves_ += moves;
        current_steps_ = current_steps_ - (int)moves.length();
        showMaze("noMore");
        fast_move_counter_ = 0;
    }
    else
    {
        current_position_x_ = tempX;
        current_position_y_ = tempY;
        
        std::cout << "Error: Invalid move." << std::endl;
    }
    
    
}

//------------------------------------------------------------------------------
bool Game::checkValidMove(std::string orientation)
{
    if(orientation == "down")
    {
        if(fix_game_map_.at(current_position_x_ + 1).at(current_position_y_) != '#')
        {
            return true;
        }
    }
    else if(orientation == "up")
    {
        if(fix_game_map_.at(current_position_x_ - 1).at(current_position_y_) != '#')
        {
            return true;
        }
        
    }
    else if(orientation == "left")
    {
        if(fix_game_map_.at(current_position_x_).at(current_position_y_ - 1) != '#')
        {
            return true;
        }
    }
    else
    {
        if(fix_game_map_.at(current_position_x_).at(current_position_y_ + 1) != '#')
        {
            return true;
        }
    }
    
    return false;
}

//------------------------------------------------------------------------------
void Game::makeOneMove(std::string orientation)
{
    if(orientation == "down")
    {
        current_position_x_ = current_position_x_ + 1;
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) == '+')
        {
            while (checkValidMove("down"))
            {
                makeOneMove(orientation);
                break;
            }
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'A' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'Z')
        {
            teleportThePlayer(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'a' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'e')
        {
            increaseCurrentSteps(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'f' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'j')
        {
            reduceCurrentSteps(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
    }
    else if(orientation == "up")
    {
        current_position_x_ = current_position_x_ - 1;
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) == '+')
        {
            while (checkValidMove("up"))
            {
                makeOneMove(orientation);
                break;
            }
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'A' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'Z')
        {
            teleportThePlayer(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'a' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'e')
        {
            increaseCurrentSteps(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'f' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'j')
        {
            reduceCurrentSteps(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
    }
    else if(orientation == "left")
    {
        current_position_y_ = current_position_y_ - 1;
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) == '+')
        {
            while (checkValidMove("left"))
            {
                makeOneMove(orientation);
                break;
            }
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'A' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'Z')
        {
            teleportThePlayer(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'a' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'e')
        {
            increaseCurrentSteps(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'f' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'j')
        {
            reduceCurrentSteps(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
    }
    else
    {
        current_position_y_ = current_position_y_ + 1;
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) == '+')
        {
            while (checkValidMove("right"))
            {
                makeOneMove(orientation);
                break;
            }
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'A' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'Z')
        {
            teleportThePlayer(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'a' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'e')
        {
            increaseCurrentSteps(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
        
        if(fix_game_map_.at(current_position_x_).at(current_position_y_) >= 'f' && fix_game_map_.at(current_position_x_).at(current_position_y_) <= 'j')
        {
            reduceCurrentSteps(fix_game_map_.at(current_position_x_).at(current_position_y_));
        }
    }
}

//------------------------------------------------------------------------------
void Game::teleportThePlayer(char teleportField)
{
    std::pair<std::pair<int, int>, std::pair<int, int>> teleportPair;
    std::pair<int, int> firstField;
    std::pair<int, int> secondField;
    
    teleportPair = all_teleports_map_[teleportField];
    
    firstField = teleportPair.first;
    secondField = teleportPair.second;
    
    if(current_position_x_ == firstField.first && current_position_y_ == firstField.second)
    {
        current_position_x_ = secondField.first;
        current_position_y_ = secondField.second;
    }
    else if(current_position_x_ == secondField.first && current_position_y_ == secondField.second)
    {
        current_position_x_ = firstField.first;
        current_position_y_ = firstField.second;
    }
    else
    {
        return;
    }
}

//------------------------------------------------------------------------------
bool Game::checkOneWayField(std::string orientation)
{
    if(fix_game_map_.at(current_position_x_).at(current_position_y_) == '>')
    {
        if(orientation != "right")
        {
            return false;
        }
    }
    else if(fix_game_map_.at(current_position_x_).at(current_position_y_) == '<')
    {
        if(orientation != "left")
        {
            return false;
        }
    }
    else if(fix_game_map_.at(current_position_x_).at(current_position_y_) == 'v')
    {
        if(orientation != "down")
        {
            return false;
        }
    }
    else if(fix_game_map_.at(current_position_x_).at(current_position_y_) == '^')
    {
        if(orientation != "up")
        {
            return false;
        }
    }
    
    return true;
}

//------------------------------------------------------------------------------
void Game::reduceCurrentSteps(char reduceField)
{
    std::map<char, int> reduceMap;
    
    reduceMap['f'] = 1;
    reduceMap['g'] = 2;
    reduceMap['h'] = 3;
    reduceMap['i'] = 4;
    reduceMap['j'] = 5;
    
    fix_game_map_.at(current_position_x_).at(current_position_y_) = ' ';
    
    if(current_steps_ - reduceMap[reduceField] < 0)
    {
        current_steps_ = 0;
    }
    else
    {
        current_steps_ = current_steps_ - reduceMap[reduceField];
    }
}

//------------------------------------------------------------------------------
void Game::increaseCurrentSteps(char increaseField)
{
    std::map<char, int> increaseMap;
    
    increaseMap['a'] = 1;
    increaseMap['b'] = 2;
    increaseMap['c'] = 3;
    increaseMap['d'] = 4;
    increaseMap['e'] = 5;
    
    fix_game_map_.at(current_position_x_).at(current_position_y_) = ' ';
    current_steps_ = current_steps_ + increaseMap[increaseField];
}

//------------------------------------------------------------------------------
void Game::resetTheMaze()
{
    input_moves_ = "";
    current_position_x_ = start_position_x_;
    current_position_y_ = start_position_y_;
    current_steps_ = maximum_steps_;
}