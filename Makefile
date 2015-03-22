CMP = g++
MAIN = main
OBJECTS = Player.o Encounter.o Alien.o Dragon.o Golem.o  Scribe.o StarRunner.o Smuggler.o
EXEC = $(MAIN)
FLAGS = -Wall

all:	$(EXEC)

$(EXEC): $(MAIN).o $(OBJECTS)
	$(CMP) $(MAIN).o $(OBJECTS) $(FLAGS) -o $(EXEC)

$(MAIN).o: $(MAIN).cpp $(OBJECTS)
	$(CMP) -c $(MAIN).cpp $(FLAGS)

%.o: %.cpp %.h 
	$(CMP) -c $< $(FLAGS)

.PHONY: clean
clean:
	rm *.o $(EXEC) *~
