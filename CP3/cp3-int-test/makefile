COURSE = cs240
SEMESTER = spring2023
CP_NUMBER = 3
LASTNAME = Oconnor
GITUSERID = koconno8
EXE = zll

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

# FLAGS = -Wall -Wextra -g
FLAGS = -Wall -Wextra -O3
CC = g++
BIN = bin
OBJ = obj
ZFILES = zany.h ZLL.h ZLL.cpp
TESTS = $(BIN)/zll_int_test

all: $(BIN)/$(EXE) $(TESTS)

# ------------------------------------------------------------------------
# Builds the .o for the isZany() functions for string and int
$(OBJ)/zany.o: zany.cpp
	$(CC) $(FLAGS) -c zany.cpp -o $@

# ------------------------------------------------------------------------
# Builds the .o for a simple Thing class
$(OBJ)/Thing.o: Thing.cpp
	$(CC) $(FLAGS) -c Thing.cpp -o $@

# ------------------------------------------------------------------------
# zll
$(BIN)/$(EXE): $(OBJ)/zll.o $(OBJ)/zany.o $(OBJ)/Thing.o
	$(CC) $(FLAGS) $(OBJ)/zll.o $(OBJ)/zany.o $(OBJ)/Thing.o \
		-o $@ 

$(OBJ)/zll.o: zll.cpp $(ZFILES) 
	$(CC) $(FLAGS) -c zll.cpp -o $@

# ------------------------------------------------------------------------
# zll_int_test
$(BIN)/zll_int_test: $(OBJ)/zll_int_test.o $(OBJ)/zany.o
	$(CC) $(FLAGS) $(OBJ)/zll_int_test.o $(OBJ)/zany.o -o $@

$(OBJ)/zll_int_test.o: zll_int_test.cpp $(ZFILES) $(OBJ)/zany.o
	$(CC) $(FLAGS) -c zll_int_test.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) $(TESTS) *.tar.gz
