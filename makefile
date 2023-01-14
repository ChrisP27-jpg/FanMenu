# Copy and adapt the contents of a makefile here.
# Use separate compilation, support "make clean", and name your 
# executable "fans" as per the specification

COURSE = cs240
SEMESTER = spring2022

# Update the CP_NUMBER if you adapt this makefile for future assignments
CP_NUMBER = 4

# Change the following to your own information
LASTNAME = Painter
GITUSERID = ChrisP27-jpg

# The name of the executable
EXE = fans

# Name files according to CS240 naming conventions
REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

# Store executables in a subdirectory
all: $(BIN)/$(EXE)

# Reflects how the files may have been named in CP0
$(BIN)/$(EXE): $(OBJ)/Fans.o
	$(CC) $(FLAGS) $(OBJ)/Fans.o -o $@

$(OBJ)/Fans.o: Fans.cpp Parser.h Fans.h
	$(CC) $(FLAGS) -c Fans.cpp -o $@

# Update to add targets for your other .o files, following the Play.o sample
	

# Run make tar to build a .tar.gz file appropriate for uploading to Brightspace
tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz
