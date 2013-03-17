PROJECT_DIR = /home/chris/Workspace/eclipse/domonion

CC = g++
CFLAGS = -g -Wall -fno-inline
INCLUDE = -I$(PROJECT_DIR)/include
LDFLAGS = -lmenu -lncurses 
OBJ := obj
SRC := $(PROJECT_DIR)/src
RM := rm -f

_objects := app.o base.o debugview.o deck.o card.o cardbank.o dominion.o \
gamestate.o genericcard.o infoview.o player.o playercollection.o playerview.o \
supplypile.o view.o viewport.o
_scratch_objects := base.o debugview.o deck.o card.o cardbank.o dominion.o \
gamestate.o genericcard.o infoview.o player.o playercollection.o playerview.o \
scratch.o selector.o supplypile.o view.o viewport.o
objects := $(addprefix $(OBJ)/,$(_objects))
scratch_objects := $(addprefix $(OBJ)/,$(_scratch_objects))

vpath %.cc $(SRC):$(SRC)/cards:$(SRC)/cards/sets:$(SRC)/ui/console

all : app

app : $(objects)
	$(CC) $(CFLAGS) $(objects) -o $@ $(LDFLAGS)

scratch : $(scratch_objects)
	$(CC) $(CFLAGS) $(scratch_objects) -o $@ $(LDFLAGS) 

%.o : $(OBJ)/%.o

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