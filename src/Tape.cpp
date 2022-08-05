#include "Tape.hpp"

#include <cstring>
#include <iostream>

Tape::Tape() :
	dataPtr(0), instrPtr(0), tape(new tapeDataType_T[TAPE_SIZE]),
	code(), debugEnabled(false)
{
}

Tape::~Tape() { }

void Tape::reset()
{
	dataPtr  = 0;
	instrPtr = 0;
	debugEnabled = false;
	memset(tape.get(), 0, TAPE_SIZE);
	code.clear();
}

void Tape::print_char()
{
	std::cout << (displayDataType_T)tape[dataPtr];
	#ifdef DEBUG_ENABLED
	print_debug_info(".");
	#endif
}

void Tape::get_char()
{
	#ifdef DEBUG_ENABLED
	print_debug_info(",");
	#endif
	char c = getchar();
	if (c == EOF) tape[dataPtr] = 0;
	else tape[dataPtr] = c;
}

void Tape::start_loop()
{
	if (tape[dataPtr] == 0)
	{
		instrPtr = code[instrPtr].data;
		#ifdef DEBUG_ENABLED
		print_debug_info("[s");
		#endif
	}
	#ifdef DEBUG_ENABLED
	else print_debug_info("[c");
	#endif
}

void Tape::end_loop()
{
	if (tape[dataPtr])
	{
		instrPtr = code[instrPtr].data;
		#ifdef DEBUG_ENABLED
		print_debug_info("]c");
		#endif
	}
	#ifdef DEBUG_ENABLED
	else print_debug_info("]s");
	#endif
}

void Tape::change_data_ptr()
{
	#ifdef DEBUG_ENABLED
	if (dataPtr + code[instrPtr].data >= TAPE_SIZE)
	{
		std::cerr << "bf-interp: "
		          << "tried to increase dataPtr past the end of the tape, "
		          << "exiting\n";
		exit(1);
	}
	#endif
	
	dataPtr += code[instrPtr].data;
	
	#ifdef DEBUG_ENABLED
	if (debugEnabled)
		print_debug_info(">/< " + std::to_string(code[instrPtr].data));
	#endif
}

void Tape::change_data()
{
	tape[dataPtr] += code[instrPtr].data;
	
	#ifdef DEBUG_ENABLED
	if (debugEnabled)
		print_debug_info("-/+ " + std::to_string(code[instrPtr].data));
	#endif
}

void Tape::print_debug_info(const std::string &info)
{
	if (debugEnabled)
	std::cerr << "\t" << info
	          << "\t\tinstrPtr - " << instrPtr
	          << "\tdataPtr - "    << dataPtr
	          << "\t@dataPtr - "   << (int)tape[dataPtr] << '\n';
}
