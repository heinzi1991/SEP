//------------------------------------------------------------------------------
// Filename:				Command.cpp
// Description:
// Authors:					Tina Promitzer			(1311885)
//									Martin Zagar			(1131246)
// Tutor:						Christoph Maurer
// Group:						6
// Created:					18.03.2016
// Last change:     04.05.2016
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