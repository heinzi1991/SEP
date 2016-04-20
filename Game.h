//------------------------------------------------------------------------------
// Filename:		Game.h
// Description:
// Authors:         Karim Koutp             (1314710)
//					Tina Promitzer			(1311885)
//					Martin Zagar			(1131246)
// Tutor:			Christoph Maurer
// Group:			6
// Created:			18.03.2016
// Last change:     25.03.2016
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
    std::map<char, std::pair<std::pair<int, int>, std::pair<int, int>>>
    all_teleports_map_;
    
    std::string input_moves_;
    std::string save_file_name_;
    
    int maximum_steps_;
    int current_steps_;
    int start_position_x_;
    int start_position_y_;
    int target_position_x_;
    int target_position_y_;
    int current_position_x_;
    int current_position_y_;
    int maze_width_;
    int maze_height_;
    int fast_move_counter_ = 0;
    
    bool save_mode_ = false;
    bool load_mode_ = false;
    bool fast_move_activeted_;
    bool finish_maze_ = false;
    bool last_move_of_series = false;
    
public:
    //--------------------------------------------------------------------------
    // Game::Game() constructor
    // @param none
    // @return none
    //
    Game();
    
    //--------------------------------------------------------------------------
    // Game::Game() destructor
    // @param none
    // @return none
    //
    ~Game();
    
    //--------------------------------------------------------------------------
    // Getter Methods
    //
    bool getLoadMode();
    bool getFinishMaze();
    int getCurrentSteps();
    
    //--------------------------------------------------------------------------
    // Setter Methods
    //
    
    void setSaveMode(bool saveMode);
    void setLoadMode(bool loadMode);
    void setSaveFileName(std::string saveFileName);
    void setFastMove(bool fastMoveMode);
    
    //--------------------------------------------------------------------------
    // Game::run() method
    // Keeps basic program functions on while the game is running.
    // Checks for false user input.
    // @param none
    // @return none
    //
    void run();
    
    //--------------------------------------------------------------------------
    //Game::deleteCommands() method
    //
    //
    //@param none
    //@return none
    //
    void deleteCommands();
    
    //--------------------------------------------------------------------------
    // Game::initCommands() method
    // Handles user input commands
    // @param none
    // @return none
    //
    void initCommands();
    
    //--------------------------------------------------------------------------
    // Game::toLower(std::string word) method
    // Handles uppercase / lowercase string input
    // @param std::string word
    // @return std::string result
    //
    std::string toLower(std::string word);
    
    //--------------------------------------------------------------------------
    // Game::splitCommand(std::string s) method
    // @param std::string s
    // @return std::string result
    //
    std::vector<std::string>splitCommand(std::string s);
    
    //--------------------------------------------------------------------------
    // Game::loadFile(std::string fileName) method
    //
    // @param std::string fileName
    // @return none
    //
    void loadFile(std::string fileName);
    
    //--------------------------------------------------------------------------
    // Game::saveFile(std::string fileName) method
    //
    // @param std::string fileName
    // @return none
    //
    void saveFile(std::string fileName);
    
    //--------------------------------------------------------------------------
    // Game::writeToCheckMap(std::string oneLine, int lineNumber) method
    //
    // @param std::string
    // @param int lineNumber
    // @return none
    //
    void writeToCheckMap(std::string oneLine, int lineNumber);
    
    //--------------------------------------------------------------------------
    // Game::checkIfValidMaze() method
    //
    // @param none
    // @return bool
    //
    bool checkIfValidMaze();
    
    //--------------------------------------------------------------------------
    // Game::checkIfValidPath(std::string inputMoves) method
    //
    // @param std::string inputMoves
    // @return bool
    //
    bool checkIfValidPath(std::string inputMoves);
    
    //--------------------------------------------------------------------------
    // Game::writeFixMaze() method
    //
    // @param none
    // @return none
    //
    void writeFixMaze();
    
    //--------------------------------------------------------------------------
    // Game::showMaze(std::string parameter) method
    //
    // @param std::string parameter
    // @return none
    //
    void showMaze(std::string parameter);
    
    //--------------------------------------------------------------------------
    // Game::saveAllTeleports() method
    //
    // @param none
    // @return none
    //
    void saveAllTeleports();
    
    //--------------------------------------------------------------------------
    // Game::searchSecondPostion(int firstCount, int secondCount,
    //                           char searchChar) method
    //
    // @param int firstCount
    // @param int secondCount
    // @param char searchChar
    // @return std::pair<int, int>
    //
    std::pair<int, int> searchSecondPosition(int firstCount, int secondCount,
                                             char searchChar);
    
    //--------------------------------------------------------------------------
    // Game::makeMoveInDirection(std::string direction) method
    //
    // @param std::string direction
    // @return none
    //
    void makeMoveInDirection(std::string direction);
    
    //--------------------------------------------------------------------------
    // Game::makeMoreMoves(std::string moves) method
    //
    // @param std::string moves
    // @return none
    //
    void makeMoreMoves(std::string moves);
    
    //--------------------------------------------------------------------------
    // Game::checkValidMoves(std::string orientation) method
    //
    // @param std::string orientation
    // @return bool
    //
    bool checkValidMove(std::string orientation);
    
    //--------------------------------------------------------------------------
    // Game::makeOneMove(std::string orientation) method
    //
    // @param std::string orientation
    // @return none
    //
    void makeOneMove(std::string orientation);
    
    //--------------------------------------------------------------------------
    // Game::teleportThePlayer(char teleportField) method
    //
    // @param char teleportField
    // @return none
    //
    void teleportThePlayer(char teleportField);
    
    //--------------------------------------------------------------------------
    // Game::reduceCurrentSteps(char reduceField) method
    //
    // @param char reduceField
    // @return none
    //
    void reduceCurrentSteps(char reduceField);
    
    //--------------------------------------------------------------------------
    // Game::increaseCurrentSteps(char increaseField) method
    //
    // @param char increaseField
    // @return none
    //
    void increaseCurrentSteps(char increaseField);
    
    //--------------------------------------------------------------------------
    // Game::checkOneWayField(std::string orientation) method
    //
    // @param std::string orientation
    // @return bool
    //
    bool checkOneWayField(std::string orientation);
    
    //--------------------------------------------------------------------------
    // Game::makeWin(char direction) method
    //
    // @param char direction
    // @return none
    //
    void makeWin(char direction);
    
    //--------------------------------------------------------------------------
    // Game::resetTheMaze() method
    //
    // @param none
    // @return none
    //
    void resetTheMaze();
    
    
};

#endif