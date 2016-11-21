CC=gcc
FLAGS=-Wall
EXECUTABLE=prog

all: $(EXECUTABLE)

$(EXECUTABLE): main.o allocation.o remplissage.o suppression.o
	$(CC) -lm -o $@ $^ $(FLAGS)

main.o: main.c allocation.h remplissage.h structure_log.h suppression.h
	$(CC) -c $< $(FLAGS)

allocation.o: allocation.c allocation.h structure_log.h
	$(CC) -c $< $(FLAGS)

remplissage.o: remplissage.c allocation.h structure_log.h remplissage.h
	$(CC) -c $< $(FLAGS)

suppression.o: suppression.c suppression.h remplissage.h allocation.h structure_log.h 
	$(CC) -c $< $(FLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf prog



