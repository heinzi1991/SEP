#include "Fastmove.h"
#include "Game.h"

//------------------------------------------------------------------------------
Fastmove::~Fastmove()
{
	
}

//------------------------------------------------------------------------------
Fastmove::Fastmove(std::string name) : Command(name)
{
	
}

//------------------------------------------------------------------------------
int Fastmove::execute(Game &board, std::vector <std::string> &params)
{
	if (params.size() == 3)
	{
		if (board.checkFastMoveInput(params[1]) == false)
		{
			std::cout << "[ERR] Wrong parameter." << std::endl;
			return 1;
			
		}
		
		if (board.getLoadMode() == false)
		{
			std::cout << "[ERR] No maze loaded." << std::endl;
			return 1;
		}
		
		board.setFastMove(true);
		board.makeMoreMoves(params[1]);
		
	}
	else
	{
		std::cout << "[ERR] Wrong parameter count." << std::endl;
		return 1;
	}
	
	return 1;
}
