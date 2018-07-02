GCC = g++
#C11 = c++11
PROGRAM = power

OBJ =	main.o \
		BFS.o \
		BFSCalc.o \
		FileIO.o \
		Node.o \
		Utility.o

.PHONY : all
all : $(PROGRAM)

$(PROGRAM) : $(OBJ)
		$(GCC) -Wall -g -o $@ $(OBJ)

.PHONY : .o .cpp
.cpp.o :
		$(GCC) -c $<

.PHONY : clean
clean :
		-rm *.o $(PROGRAM)
