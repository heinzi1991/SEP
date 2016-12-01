#include <iostream>
#include <string>

#include "Game.h"

//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//

int main(int argc, char **argv)
{
	Game pokemon;
	
	if (argc == 3)
	{
		if ((std::string) argv[1] == "-s")
		{
			pokemon.setSaveMode(true);
			pokemon.setSaveFileName(argv[2]);
			
		}
		else if ((std::string) argv[1] == "-m")
		{
			pokemon.setLoadMode(true);
			pokemon.loadFile(argv[2]);
		}
		else
		{
			std::cout << "Wrong usage: ./basic [-s <filename1>] [-m <filename2>]"
			<< std::endl;
			return 2;
		}
	}
	
	if (argc == 5)
	{
		pokemon.setLoadMode(true);
		pokemon.setSaveMode(true);
		
		if ((std::string) argv[1] == "-s")
		{
			pokemon.setSaveFileName(argv[2]);
			pokemon.loadFile(argv[4]);
			pokemon.saveFile(argv[2]);
		}
		else if ((std::string) argv[1] == "-m")
		{
			pokemon.setSaveFileName(argv[4]);
			pokemon.loadFile(argv[2]);
			pokemon.saveFile(argv[4]);
		}
	}
	
	if (argc == 4 || argc == 2 || argc > 5)
	{
		std::cout << "Wrong usage: ./basic [-s <filename1>] [-m <filename2>]"
		<< std::endl;
		return 2;
	}
	
	try
	{
		pokemon.run();
	}
	catch (std::bad_alloc &ba)
	{
		std::cout << "Error: Out of memory!" << std::endl;
	}
	
	return 0;
}
