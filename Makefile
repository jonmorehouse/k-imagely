CC=gcc
LIBS=-lmill
OUTPUT_DIR=.
OUTPUT=kimagely

install: main.c 
	$(CC) $(LIBS) -o $(OUTPUT_DIR)/$(OUTPUT) main.c

clean: 
	rm kimagely

.PHONY: install clean
