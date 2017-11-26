# Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
# Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
#	Date:							21.10.2017
# Email:						<xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>

PROJECT_NAME     		= shreya
PROJECT_DOC					= doc/manual.pdf
PROJECT_SOURCES  		= src/*.c
PROJECT_HEADERS			= src/*.h

CC              		= gcc
CFLAGS 							= -std=gnu99 -Wextra -Werror -pedantic -g -Wall

###########################################

all:			$(PROJECT_NAME)

$(PROJECT_NAME): $(PROJECT_SOURCES) $(PROJECT_HEADERS)
	$(CC) $(CFLAGS) $(PROJECT_SOURCES) $(PROJECT_HEADERS) -o $@ -lm

############################################

TAR_NAME = xtucko00
TAR_FILES = Makefile $(PROJECT_DOC) $(PROJECT_SOURCES)

zip:
	tar -cvzf $(TAR_NAME).zip $(TAR_FILES)

rmzip:
	rm -f $(TAR_NAME).zip

############################################

tex:
	cd doc && make && make manual.ps && make manual.pdf
