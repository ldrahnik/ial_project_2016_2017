# Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
# Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
#	Date:							21.10.2017
# Email:						<xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>

PROJECT_NAME     		= shreya
PROJECT_DOC					= doc/manual.pdf
PROJECT_SOURCES  		= src/shreya.c
PROJECT_OBJECTS  		= $(PROJECT_SOURCES:.c=.o)

CC              		= gcc
CFLAGS 							= -std=gnu99 -Wall -Wextra -Werror -pedantic

###########################################

all:			$(PROJECT_NAME)

$(PROJECT_NAME): $(PROJECT_SOURCES)
	$(CC) $(CFLAGS) $(PROJECT_SOURCES) -o $@

############################################

TAR_NAME = xtucko00
TAR_FILES = Makefile $(PROJECT_DOC) $(PROJECT_SOURCES)

tar:
	tar -cvzf $(TAR_NAME).tar $(TAR_FILES)

rmtar:
	rm -f $(TAR_NAME).tar

############################################

tex:
	cd doc && make && make manual.ps && make manual.pdf
