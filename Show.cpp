#include "Show.h"
#include "Game.h"

//------------------------------------------------------------------------------
Show::~Show()
{
	
}

//------------------------------------------------------------------------------
Show::Show(std::string name) : Command(name)
{
	
}

//------------------------------------------------------------------------------
int Show::execute(Game &board, std::vector <std::string> &params)
{
	if (params.size() == 2)
	{
		if (board.getLoadMode() == false)
		{
			std::cout << "[ERR] No maze loaded." << std::endl;
			return 1;
		}
		
		board.showMaze("noMore");
	}
	else if (params.size() == 3)
	{
		if (params[1] == "more")
		{
			if (board.getLoadMode() == false)
			{
				std::cout << "[ERR] No maze loaded." << std::endl;
				return 1;
			}
			
			board.showMaze("more");
		}
		else
		{
			std::cout << "[ERR] Wrong parameter." << std::endl;
			return 1;
		}
	}
	else
	{
		std::cout << "[ERR] Wrong parameter count." << std::endl;
	}
	
	return 1;
}
