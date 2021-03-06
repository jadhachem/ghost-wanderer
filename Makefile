#
# Copyright (C) 2014, 2015 Jad Hachem <jad.hachem@gmail.com>
# 
# This file is part of Ghost Wanderer.
# 
# Ghost Wanderer is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Ghost Wanderer is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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

