COMPILER = gcc
CCFLAGS = -Wall -g
ARKEYS = rv

all: sl libsl.a
	
sl: main.o libsl.a
	$(COMPILER) $(CCFLAGS) -o sl main.o libsl.a
main.o: main.c
	$(COMPILER) $(CCFLAGS) -c main.c
libsl.a: sorted-list.o
	ar $(ARKEYS) libsl.a sorted-list.o
sorted-list.o: sorted-list.c
	$(COMPILER) $(CCFLAGS) -c sorted-list.c
clean:
	rm -f sl *.o *.a
