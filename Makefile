CC=gcc
LIBS=-lmill
OUTPUT=kimagely

install: main.c 
	$(CC) $(LIBS) -o $(OUTPUT) main.c

clean: 
	rm kimagely

.PHONY: install clean
