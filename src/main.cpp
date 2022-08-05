#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>

#include "BFProgram.hpp"

void print_help()
{
	std::cout << "bf-interp: specify a file\n";
	std::cout << "    [optional] -g (debugging mode)\n";
	std::cout << "    [optional] -s (step-through mode)\n\n";
	
	std::cout << "Reading debugging output:\n";
	std::cout << "    '.' or ',' -- corresponding brainfuck operator\n";
	std::cout << "    '[c' -- loop was started\n";
	std::cout << "    '[s' -- loop was skipped\n";
	std::cout << "    ']c' -- loop tested positive and will run again\n";
	std::cout << "    ']s' -- loop tested negative and will not run again\n";
	std::cout << "    '>/<' or '-/+' -- corresponding brainfuck operator, ";
	std::cout << "number of repetitions displayed directly after\n";
}

int main (int argc, char *argv[])
{
	if (argc < 2 || argv[1] == std::string("-h") ||
	                argv[1] == std::string("--help"))
	{
		print_help();
		exit(1);
	}

	std::ifstream file(argv[1]);
	
	if (file.is_open() == false)
	{
		std::cerr << "bf-interp: could not open file\n";
		exit(1);
	}
	
	bool debug = false;
	bool stepThrough = false;
	
	int currArg = 2;
	
	while (currArg < argc)
	{
		if (argv[currArg] == std::string("-g"))      debug = true;
		else if (argv[currArg] == std::string("-s")) stepThrough = true;
		++currArg;
	}

	BFProgram program;
	
	program.load(file);
	program.run(debug, stepThrough);
	
	return 0;
}
