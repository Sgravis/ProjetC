CC=gcc
FLAGS=-Wall
EXECUTABLE=prog

all: $(EXECUTABLE)

$(EXECUTABLE): main.o allocation.o remplissage.o suppression.o cpprof.o
	$(CC) -lm -o $@ $^ $(FLAGS) `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags cairo`

main.o: main.c allocation.h cpprof.h remplissage.h structure_log.h suppression.h
	$(CC) -c $< `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags cairo`

allocation.o: allocation.c allocation.h structure_log.h
	$(CC) -c $< $(FLAGS)

remplissage.o: remplissage.c allocation.h structure_log.h remplissage.h
	$(CC) -c $< $(FLAGS)

suppression.o: suppression.c suppression.h remplissage.h allocation.h structure_log.h
	$(CC) -c $< $(FLAGS)

cpprof.o: cpprof.c cpprof.h
	$(CC) -c $< `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags cairo`

clean:
	rm -rf *.o

mrproper: clean
	rm -rf prog
