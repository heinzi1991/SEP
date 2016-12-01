#include "Move.h"
#include "Game.h"

//------------------------------------------------------------------------------
Move::~Move()
{
	
}

//------------------------------------------------------------------------------
Move::Move(std::string name) : Command(name)
{
	
}

//------------------------------------------------------------------------------
int Move::execute(Game &board, std::vector <std::string> &params)
{
	if (board.getFinishMaze() == true)
	{
		std::cout << "[ERR] Invalid move." << std::endl;
		return 1;
	}
	
	if (board.getCurrentSteps() == 0)
	{
		std::cout << "[ERR] No more steps possible." << std::endl;
		board.resetTheMaze();
		return 1;
	}
	
	if (params.size() == 3)
	{
		if (params[1] == "down" || params[1] == "up" || params[1] == "right"
				|| params[1] == "left")
		{
			if (board.getLoadMode() == false)
			{
				std::cout << "[ERR] No maze loaded." << std::endl;
				return 1;
			}
			
			board.setFastMove(false);
			board.makeMoveInDirection(params[1]);
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
	
	return 1;
}
