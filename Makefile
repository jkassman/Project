CMP = g++
MAIN = main
CLASS1 = Dragon
CLASS2 = Alien
CLASS3 = Player
CLASS4 = Encounter
EXEC = $(MAIN)
FLAGS = -Wall

all:	$(MAIN)

$(EXEC): $(MAIN).o $(CLASS1).o $(CLASS2).o $(CLASS3).o $(CLASS4).o
	$(CMP) $(MAIN).o $(CLASS1).o $(CLASS2).o $(CLASS3).o $(CLASS4).o $(FLAGS) -o $(EXEC)

$(MAIN).o: $(MAIN).cpp $(CLASS1).h
	$(CMP) -c $(MAIN).cpp $(FLAGS)

$(CLASS1).o: $(CLASS1).cpp $(CLASS1).h 
	$(CMP) -c $(CLASS1).cpp $(FLAGS)

$(CLASS2).o: $(CLASS2).cpp $(CLASS2).h 
	$(CMP) -c $(CLASS2).cpp $(FLAGS)

$(CLASS3).o: $(CLASS3).cpp $(CLASS3).h 
	$(CMP) -c $(CLASS3).cpp $(FLAGS)

$(CLASS4).o: $(CLASS4).cpp $(CLASS4).h 
	$(CMP) -c $(CLASS4).cpp $(FLAGS)

clean:
	rm *.o $(EXEC)
