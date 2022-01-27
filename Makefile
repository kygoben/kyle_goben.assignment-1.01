all: terrain

terrain: terrain.c
	gcc terrain.c -o terrain
	

notes: hw1_notes.c
	gcc hw1_notes.c -o note1.o

clean:
	$(RM) *.o notes terrain