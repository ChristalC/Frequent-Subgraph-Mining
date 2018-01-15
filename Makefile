#CFLAGS=--std=c++11
CFLAGS=-std=c++0x
DEPS=adj_matrix.h graph.h p1_helper.h runner.h embedding.h
all:	adj_matrix.o graph.o p1_helper.o runner.o embedding.o p1.o
	g++ -o P1 $^ $(CFLAGS)
%.o:	%.cpp $(DEPS)
	g++ -c -o $@ $< $(CFLAGS)
#debug:	info.cpp info.hpp
#	g++ -g -o P0 info.cpp
clean:
	rm -rf *.o *~ P1
