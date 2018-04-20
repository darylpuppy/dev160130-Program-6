#
# UTD CS3377 CDK Example
# Dr. Perkins
# stephen.perkins@utdallas.edu
#

CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = program6

OBJS = program6.o header.o record.o


program6: program6.o header.h record.h
	g++ -o program6  -Wall program6.o -L/scratch/perkins/lib -lcdk -lcurses

program6.o: program6.cc
	g++ -c program6.cc -I/scratch/perkins/include -Wall

clean:
	rm -f *.o program6 *~

backup:
	tar -czf program6.cc Makefile README.txt
