#include "Quit.h"
#include "Game.h"

//------------------------------------------------------------------------------
Quit::~Quit()
{
	
}

//------------------------------------------------------------------------------
Quit::Quit(std::string name) : Command(name)
{
	
}

//------------------------------------------------------------------------------
int Quit::execute(Game &board, std::vector <std::string> &params)
{
	if (params.size() == 2)
	{
		board.deleteCommands();
		std::cout << "Bye!" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "[ERR] Wrong parameter count." << std::endl;
		return 1;
	}
}
