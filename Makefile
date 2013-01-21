PROJECT_DIR = /home/chris/git/domonion

CC = g++
CFLAGS = -g -Wall
INCLUDE = -I$(PROJECT_DIR)/include
LDFLAGS = -lmenu -lncurses 
OBJ := obj
SRC := $(PROJECT_DIR)/src
RM := rm -f

_objects := app.o deck.o card.o basicvictory.o basictreasure.o cardview.o \
gamestate.o infoview.o player.o playercollection.o viewport.o
objects := $(addprefix $(OBJ)/,$(_objects))

vpath %.cc $(SRC):$(SRC)/cards:$(SRC)/ui/console

all : decktest scratch app

app : $(objects)
	$(CC) $(CFLAGS) $(objects) -o $@ $(LDFLAGS)

scratch : $(OBJ)/scratch.o
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(OBJ)/%.o : %.cc
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(objects) : | $(OBJ)

$(OBJ) :
	mkdir -p obj

clean :
	$(RM) $(objects)
	$(RM) scratch
	$(RM) app
	
.PHONY : clean