CC := g++
LD_FLAGS := 
CC_FLAGS := -g -Wall -Werror -pedantic -O0 -std=c++0x 

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES = $(patsubst %.cpp,obj/%.o,$(CPP_FILES))

obj/%.o : %.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< $(LD_FLAGS)

main : $(OBJ_FILES)
	$(CC) $^ -o $@ $(LD_FLAGS)

.PHONY: clean
clean:
	rm -f obj/*.o
