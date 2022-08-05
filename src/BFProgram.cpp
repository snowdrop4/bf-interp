#include "BFProgram.hpp"

#include <vector>
#include <assert.h>
#include <stack>
#include <iostream>

// public ----------------------------------------------------------------------
BFProgram::BFProgram()  { }
BFProgram::~BFProgram() { }

void BFProgram::load(std::ifstream &file)
{
	if (file.is_open() == false)
	{
		std::cerr << "BFProgram: error -- brainfuck source file was not open";
		return;
	}
	
	static bool needsReseting = false;
	if (needsReseting == true)
		Tape::reset();
	needsReseting = true;
	
	std::stack<unsigned int> startTags;
	unsigned int instrNum = 0;
	char input;
	while (file >> input)
	{
		switch (input)
		{
			case '>': compress_operator('>', file, true,  &Tape::change_data_ptr); break;
			case '<': compress_operator('<', file, false, &Tape::change_data_ptr); break;
			case '+': compress_operator('+', file, true,  &Tape::change_data);     break;
			case '-': compress_operator('-', file, false, &Tape::change_data);     break;
			case '.': code.emplace_back(&Tape::print_char, 0 ); break;
			case ',': code.emplace_back(&Tape::get_char,   0 ); break;
			case '[':
				code.emplace_back(&Tape::start_loop, 0);
				startTags.push(instrNum);
				break;
			case ']':
				code.emplace_back(&Tape::end_loop, 0);
				code.back().data = startTags.top();
				startTags.pop();
				code[code.back().data].data = instrNum;
				break;
			
			default: --instrNum; break;
		}
		++instrNum;
	}
	
	file.close();
}

void BFProgram::run(bool debugEnabledArg, bool stepThrough)
{
	debugEnabled = debugEnabledArg;
	dataPtr  = 0;
	instrPtr = 0;
	
	unsigned int size = code.size();
	
	while (instrPtr < size)
	{
		(this->*code[instrPtr].method)();
		
		// If Tape::get_char() is called, and more than one character is entered
		// this garbles the input. I see no way around this, apart from going
		// down the road of capturing the arrow keys as the continuation buttons
		// instead
		if (stepThrough) getchar();
		
		++instrPtr;
	}
}

// private ---------------------------------------------------------------------
void BFProgram::compress_operator(char operator_, std::ifstream &file,
	bool increment, void (Tape::*method)())
{
	unsigned int numberOf = 1;
	char input;
	while (file >> input)
	{
		while (isspace(input) == true)
			file >> input;
		
		if (input != operator_)
		{
			file.unget();
			break;
		}
		
		++numberOf;
	}
	
	if (increment)
		code.emplace_back(method, numberOf);
	else code.emplace_back(method, 0 - numberOf);
}
