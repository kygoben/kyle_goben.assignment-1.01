all: terrain

terrain: terrain.c
	gcc terrain.c -o terrain -Wall
	

clean:
	$(RM) terrain