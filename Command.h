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

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <vector>

class Game;

class Command
{
private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    
    Command(const Command& original);
    
    //--------------------------------------------------------------------------
    // Private assignment operator
    
    Command& operator=(const Command& original);
    
    //--------------------------------------------------------------------------
    /// Name of this command
    std::string command_name_;
    
public:
    //--------------------------------------------------------------------------
    // Constructor
    
    Command(std::string name);
    
    //--------------------------------------------------------------------------
    // Destructor
    
    virtual ~Command();
    
    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    
    virtual int execute(Game& board, std::vector<std::string>& params) = 0;
    
    //--------------------------------------------------------------------------
    // Getter Methods
    const std::string& getName() const;
};

#endif //COMMAND_H_INCLUDED