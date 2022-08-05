#ifndef TAPE_HPP
#define TAPE_HPP

/*
 * Undefine to disable debug display and bounds checking.
 * Roughly doubles the execution speed of the program.
 */
#define DEBUG_ENABLED

#include <string>
#include <deque>
#include <memory>

typedef unsigned char tapeDataType_T;
typedef char          displayDataType_T;
typedef int           debugDisplayDataType_T;

const unsigned int TAPE_SIZE = 30000;

struct code_T;

class Tape
{
public:
	Tape();
	virtual ~Tape();
	
	void reset();
	
	virtual void load(std::ifstream &file) = 0;
	virtual void run(bool debugEnabled, bool stepThrough) = 0;
	
	void change_data_ptr();
	void change_data();
	void print_char();
	void get_char();
	void start_loop();
	void end_loop();
	
protected:
	void print_debug_info(const std::string &info);
	
	unsigned int dataPtr;
	unsigned int instrPtr;
	
	std::unique_ptr<tapeDataType_T[]> tape;
	std::deque<code_T> code;
	
	bool debugEnabled;
};

struct code_T
{
	code_T(void (Tape::*method)(), int data) :
		method(method), data(data)
	{ }
	
	~code_T() {}
	
	void (Tape::*method)();
	
	/*
	 * If the instruction is either '[' or ']' this references the matching
	 * '[' or ']'.
	 * If the instruction modifies the dataPtr or data, this stores the amount
	 * to modify by.
	 */
	int data;
};

#endif
