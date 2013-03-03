BIN = bin
SRC = src

BINARY = $(BIN)/rat
OBJECTS = $(SRC)/main.o $(SRC)/server.o $(SRC)/events.o
OPTIONS = -Wall -Werror -Wextra -pedantic -ansi
LINKS = -lX11

$(BINARY) : $(OBJECTS)
	gcc $(OPTIONS) -o $(BINARY) $(OBJECTS) $(LINKS)

main.o : main.c
	gcc $(OPTIONS) -c $(SRC)/main.c

server.o : server.c
	gcc $(OPTIONS) -c $(SRC)/server.c -D_POSIX_SOURCE

events.o : events.c
	gcc $(OPTIONS) -c $(SRC)/events.c

.PHONY : clean
clean :
	-rm $(BINARY) $(OBJECTS)
