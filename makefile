# Makefile for pseudo Gcode 

CC- gcc -std=c11
CFLAGS= -g -c -Wall
LDFLAGS= -g
OBJECTS= main.o

.SILENT:
gcode:	$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o gcode
	echo gcode compiled successfully!

main.o: main.c main.h
	$(CC) $(CFLAGS) main.c
	echo main.o compiled successfully!

clean:
	rm main.o
	#rm gcode
	echo Clearing of files complete!
