#include "Save.h"
#include "Game.h"

//------------------------------------------------------------------------------
Save::~Save()
{
	
}

//------------------------------------------------------------------------------
Save::Save(std::string name) : Command(name)
{
	
}

//------------------------------------------------------------------------------
int Save::execute(Game &board, std::vector <std::string> &params)
{
	if (board.getFinishMaze())
	{
		return 1;
	}
	
	if (params.size() == 3)
	{
		if (board.checkCommandSaveInput(params[1]) == true)
		{
			board.saveFile(params[1]);
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
		return 1;
	}
	
	if (board.getLoadMode() == false)
	{
		std::cout << "[ERR] No maze loaded." << std::endl;
		return 1;
	}
	
	return 1;
}
