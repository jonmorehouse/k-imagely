CC=gcc
LIBS=-lmill
OUTPUT_DIR=.
OUTPUT=kimagely

install: main.c
	$(CC) $(LIBS) -o $(OUTPUT_DIR)/$(OUTPUT) main.c

clean:
	@if [ -a $(OUTPUT_DIR)/$(OUTPUT) ] ; \
	then \
		rm $(OUTPUT_DIR)/$(OUTPUT); \
	fi;

.PHONY: install clean
