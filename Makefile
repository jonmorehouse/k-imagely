CC=gcc
LIBS=-lmill
OUTPUT_DIR=.
OUTPUT=kimagely

SRC_FILES=main.c server.c router.c handlers.c
HEADER_FILES=server.h router.h handlers.h

install: $(HEADER_FILES) $(SRC_FILES)
	$(CC) $(LIBS) -o $(OUTPUT_DIR)/$(OUTPUT) $(SRC_FILES)

clean:
	@if [ -a $(OUTPUT_DIR)/$(OUTPUT) ] ; \
	then \
		rm $(OUTPUT_DIR)/$(OUTPUT); \
	fi;

.PHONY: install clean
