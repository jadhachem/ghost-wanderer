# flags
CC = g++
CFLAGS = -Wall -std=c++11

# Platform-dependent flags
OS = $(shell uname)
ifeq ($(OS),Linux)
LD = -lsfml-graphics -lsfml-window -lsfml-system
endif
ifeq ($(OS),Darwin)
LD = -framework SFML -framework sfml-window -framework sfml-system -framework sfml-graphics
endif

DEBUG ?= 0
ifeq ($(DEBUG),0)
CFLAGS += -O2
else
CFLAGS += -g
endif

# Creating missing directories
DIR_GUARD = @mkdir -p $(@D)

# Program version
VERSION = 0.0.3

# executable
EXEC = ghost-wanderer

# directories
SRCD = src
INCD = inc
OBJD = obj
UNTD = unit_tests

# files
SRC = $(wildcard $(SRCD)/*.cpp)
INC = $(wildcard $(INCD)/*.hpp)
OBJ = $(SRC:$(SRCD)/%.cpp=$(OBJD)/%.o)

EXECSRC = wanderer.cpp
EXECOBJ = wanderer.o

UNTSRC = $(wildcard $(UNTD)/$(SRCD)/*_test.cpp)
UNTOBJ = $(UNTSRC:$(UNTD)/$(SRCD)/%_test.cpp=$(UNTD)/$(OBJD)/%_test.o)
UNTEXEC = $(UNTSRC:$(UNTD)/$(SRCD)/%_test.cpp=$(UNTD)/%_test)
UNTRUN = $(UNTD)/run_tests.sh

# Preventing make from deleting certain intermediate files
.PRECIOUS: $(UNTOBJ)

# header file dependencies
# (later?)

# targets

default: $(EXEC)

$(EXEC): $(EXECOBJ) $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(EXECOBJ) $(OBJ) $(LD)

$(UNTD)/%_test: $(UNTD)/$(OBJD)/%_test.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(OBJ) $(LD)

$(EXECOBJ): $(EXECSRC) $(INC)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCD)/

$(OBJD)/%.o: $(SRCD)/%.cpp $(INC)
	$(DIR_GUARD)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCD)/

$(UNTD)/$(OBJD)/%_test.o: $(UNTD)/$(SRCD)/%_test.cpp $(INC)
	$(DIR_GUARD)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCD)/

all: $(EXEC) $(UNTEXEC)

test: $(UNTEXEC)
	@chmod +x $(UNTRUN)
	./$(UNTRUN) $(UNTEXEC)

tar:
	cd ../ && \
	tar -cvf ghost-wanderer-$(VERSION).tar \
	ghost-wanderer/Makefile \
	ghost-wanderer/$(EXECSRC) \
	ghost-wanderer/$(SRCD) \
	ghost-wanderer/$(INCD) \
	ghost-wanderer/$(UNTD)/$(SRCD) \
	ghost-wanderer/data

clean:
	rm -f $(EXEC) $(EXECOBJ) $(OBJ) $(UNTEXEC) $(UNTOBJ)

