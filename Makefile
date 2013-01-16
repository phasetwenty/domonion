PROJECT_DIR = /home/chris/Workspace/eclipse/domonion

CC = g++
CFLAGS = -g -Wall
INCLUDE = -I$(PROJECT_DIR)/include
LDFLAGS = -lmenu -lncurses 
OBJ := obj
SRC := $(PROJECT_DIR)/src
RM := rm -f
objects := $(wildcard $(OBJ)/*.o)

all : decktest scratch app

app : app.o deck.o card.o basicvictory.o basictreasure.o
	$(CC) $(CFLAGS) $(OBJ)/app.o $(OBJ)/deck.o $(OBJ)/card.o $(OBJ)/basicvictory.o $(OBJ)/basictreasure.o -o app $(LDFLAGS)

scratch : scratch.o
	$(CC) $(CFLAGS) $(OBJ)/scratch.o -o scratch $(LDFLAGS)

app.o : $(SRC)/ui/console/app.cc
	$(CC) $(CFLAGS) -c $(SRC)/ui/console/app.cc $(INCLUDE) -o $(OBJ)/app.o

scratch.o : $(SRC)/scratch.cc
	$(CC) $(CFLAGS) -c $(SRC)/scratch.cc $(INCLUDE) -o $(OBJ)/scratch.o

deck.o : $(SRC)/deck.cc
	$(CC) $(CFLAGS) -c $(SRC)/deck.cc $(INCLUDE) -o $(OBJ)/deck.o

basicvictory.o : $(SRC)/cards/basicvictory.cc
	$(CC) $(CFLAGS) -c $(SRC)/cards/basicvictory.cc $(INCLUDE) -o $(OBJ)/basicvictory.o

basictreasure.o : $(SRC)/cards/basictreasure.cc
	$(CC) $(CFLAGS) -c $(SRC)/cards/basictreasure.cc $(INCLUDE) -o $(OBJ)/basictreasure.o

card.o : $(SRC)/card.cc
	$(CC) $(CFLAGS) -c $(SRC)/card.cc $(INCLUDE) -o $(OBJ)/card.o

clean :
	$(RM) $(objects)
	$(RM) scratch
	
.PHONY : clean