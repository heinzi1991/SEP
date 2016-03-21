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


#ifndef GAME_H
#define GAME_H

#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <utility>


class Command;



class Game
{
private:
    std::map<std::string, Command*> possible_commands_;
    std::vector<std::vector<char>> check_map_;
    std::vector<std::vector<char>> fix_game_map_;
    std::map<char, std::pair<std::pair<int, int>, std::pair<int, int>>> all_teleports_map_;
    
    std::string input_moves_;
    std::string save_file_name_;
    
    
    int maximum_steps_;
    int current_steps_;
    int start_position_x_;
    int start_position_y_;
    int current_position_x_;
    int current_position_y_;
    int maze_width_;
    int maze_height_;
    
    bool save_mode_ = false;
    bool load_mode_ = false;
    
    
    
    
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
    // Getter Methods
    //
    
    
    
    //----------------------------------------------------------------------------
    // Setter Methods
    //
    
    void setSaveMode(bool saveMode);
    void setLoadMode(bool loadMode);
    void setSaveFileName(std::string saveFileName);
    
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
    
    //---------------------------------------------------------------------------
    void loadFile(std::string fileName);
    
    //---------------------------------------------------------------------------
    void saveFile(std::string fileName);
    
    //---------------------------------------------------------------------------
    void writeToCheckMap(std::string oneLine, int lineNumber);
    
    //---------------------------------------------------------------------------
    bool checkIfValidMaze();
    
    //---------------------------------------------------------------------------
    bool checkIfValidPath();
    
    //---------------------------------------------------------------------------
    void writeFixMaze();
    
    //---------------------------------------------------------------------------
    void showMaze(std::string parameter);
    
    //---------------------------------------------------------------------------
    void saveAllTeleports();
    
    //---------------------------------------------------------------------------
    std::pair<int, int> searchSecondPosition(int firstCount, int secondCount, char searchChar);
    
    //---------------------------------------------------------------------------
    void makeMoveInDirection(std::string direction);
    
    //---------------------------------------------------------------------------
    bool checkValidMove(std::string orientation);
    
    //---------------------------------------------------------------------------
    void resetTheMaze();
    
    
};

#endif