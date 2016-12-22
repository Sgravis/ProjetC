CC=gcc
DEBUG=yes
VISUEL=`pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags cairo`
EXECUTABLE=prog

ifeq ($(DEBUG),yes)
	FLAGS= -Wall -g
else
	FLAGS= -Wall
endif

all: $(EXECUTABLE)


$(EXECUTABLE): main.o allocation.o remplissage.o suppression.o visuel.o interaction.o agglomeration.o
	$(CC) -o $@ $^ $(FLAGS) $(VISUEL) -lm

main.o: main.c allocation.h visuel.h remplissage.h structure_log.h suppression.h interaction.h agglomeration.h
	$(CC) -c $< $(VISUEL)

allocation.o: allocation.c allocation.h structure_log.h
	$(CC) -c $< $(FLAGS)

remplissage.o: remplissage.c allocation.h structure_log.h remplissage.h
	$(CC) -c $< $(FLAGS)

suppression.o: suppression.c suppression.h remplissage.h allocation.h structure_log.h
	$(CC) -c $< $(FLAGS) $(VISUEL)

agglomeration.o: agglomeration.c agglomeration.h structure_log.h remplissage.h suppression.h allocation.h
	$(CC) -c $< $(FLAGS)

visuel.o: visuel.c visuel.h
	$(CC) -c $< $(VISUEL)

interaction.o: interaction.c interaction.h
	$(CC) -c $< $(VISUEL)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf prog
	rm -f BackupPoints.txt
