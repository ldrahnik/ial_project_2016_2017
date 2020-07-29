# Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
# Project: 		 				IAL: náhradní projekt: 4. Nejkratší cesta v grafu
# Date:							21.10.2017
# Email:						<xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>

PROJECT_NAME     		= shreya
PROJECT_DOC				= doc/manual.pdf
PROJECT_DOC_DIR			= doc
PROJECT_DOC_NAME		= manual.pdf
PROJECT_SOURCES  		= src/*.c src/algorithm/*.c
PROJECT_HEADERS			= src/*.h src/algorithm/*.h

CC              		= gcc
CFLAGS 					= -std=gnu99 -Wextra -Werror -pedantic -g # -Wall

###########################################

all:			$(PROJECT_NAME)

$(PROJECT_NAME): $(PROJECT_SOURCES) $(PROJECT_HEADERS)
	$(CC) $(CFLAGS) $(PROJECT_SOURCES) $(PROJECT_HEADERS) -o $@ -lm

############################################

ARCHIVE_NAME = xdrahn00
ARCHIVE_FILES = Makefile $(PROJECT_SOURCES) $(PROJECT_HEADERS) -C $(PROJECT_DOC_DIR) $(PROJECT_DOC_NAME)
ARCHIVE_EXTENSION = .tar.gz
ARCHIVE = $(ARCHIVE_NAME)$(ARCHIVE_EXTENSION)

archive:
	# doc
	make tex
	
	tar -cvzf $(ARCHIVE) $(ARCHIVE_FILES)

unarchive:
	rm -rf $(ARCHIVE_NAME) && mkdir -p $(ARCHIVE_NAME) && tar -C $(ARCHIVE_NAME) -xvzf $(ARCHIVE)

rmarchive:
	rm -f $(ARCHIVE)

tree:
	tree -a $(ARCHIVE_NAME)

############################################

tex:
	cd doc && make && make manual.ps && make manual.pdf
