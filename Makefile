# Daryl Vogel
# dev160130@utdallas.edu
# CS 3377.002

program6: program6.o header.h record.h
	g++ -o program6  -Wall program6.o -L/scratch/perkins/lib -lcdk -lcurses

program6.o: program6.cc
	g++ -c program6.cc -I/scratch/perkins/include -Wall

clean:
	rm -f *.o program6 *~

backup:
	tar -czf program6.cc Makefile README.txt
