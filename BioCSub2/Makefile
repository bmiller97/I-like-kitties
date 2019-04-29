#makefile

#.exe files
sobel.exe: sobel.o KernelFilter.o 
	gcc -o sobel.exe sobel.o KernelFilter.o -lm



#.o files
sobel.o: sobel.c KernelFilter.o
	gcc -c sobel.c

KernelFilter.o: KernelFilter.c KernelFilter.h 
	gcc -c KernelFilter.c


#non-declare
clean:
	-rm *.o
	-rm *.exe
	-rm *.txt

all: sobel.exe