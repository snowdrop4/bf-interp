#ifndef BFPROGRAM_HPP
#define BFPROGRAM_HPP

#include "Tape.hpp"
#include <fstream>

class BFProgram : private Tape
{
public:
	BFProgram();
	~BFProgram();
	
	void load(std::ifstream &file);
	void run(bool debugEnabled, bool stepThrough);
	
private:
	void compress_operator(char operator_, std::ifstream &file,
		bool increment, void (Tape::*method)());
};

#endif
