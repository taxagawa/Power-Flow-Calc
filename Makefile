GCC = g++
PROGRAM = power

OBJ =	main.o \
		BFS.o \
		BFSCalc.o \
		FileIO.o \
		Network.o \
		Node.o \
		Utility.o

.PHONY : all
all : $(PROGRAM)

$(PROGRAM) : $(OBJ)
		$(GCC) -o $@ $(OBJ)

.PHONY : .o .cpp
.cpp.o :
		$(GCC) -c $<

.PHONY : clean
clean :
		-rm *.o $(PROGRAM)
