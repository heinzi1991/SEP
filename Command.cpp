//------------------------------------------------------------------------------
// Filename:		Command.cpp
// Description:     Class representing a general command
// Authors:			Anja Reibenbacher   (1330231)
//					Adam Ujvari         (1232056)
//					Martin Zagar		(1131246)
// Tutor:			Christoph Hack
// Group:			2
// Created:			27.03.2015
// Last change:     27.03.2015
//------------------------------------------------------------------------------

#include "Command.h"


//------------------------------------------------------------------------------
Command::Command(std::string name) : command_name_(name)
{
}

//------------------------------------------------------------------------------
Command::~Command()
{
}

//------------------------------------------------------------------------------
const std::string &Command::getName() const
{
    return command_name_;
}