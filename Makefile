CMP = g++
MAIN = main
OBJECTS = Player.o Encounter.o Alien.o Dragon.o Golem.o  Scribe.o StarRunner.o Smuggler.o Message.o LTexture.o
EXEC = $(MAIN)
FLAGS = -Wall
SDL_FLAGS = -w -lSDL2 -lSDL2_image -lSDL2_ttf

all:	$(EXEC)

$(EXEC): $(MAIN).o $(OBJECTS)
	$(CMP) $(MAIN).o $(OBJECTS) $(SDL_FLAGS) -o $(EXEC)

$(MAIN).o: $(MAIN).cpp $(OBJECTS)
	$(CMP) -c $(MAIN).cpp $(FLAGS)

%.o: %.cpp %.h 
	$(CMP) -c $< $(FLAGS)

LTexture.o: LTexture.cpp LTexture.h
	$(CMP) -c $< $(SDL_FLAGS)

.PHONY: clean
clean:
	-rm *.o $(EXEC) *~
