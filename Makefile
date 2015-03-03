CMP = g++
MAIN = dragontest
FUNC = dragon
EXEC = $(MAIN)
FLAGS = -lm -lX11

all:	$(MAIN)

$(EXEC): $(MAIN).o $(FUNC).o
	$(CMP) $(MAIN).o $(FUNC).o $(FLAGS) -o $(EXEC)

$(MAIN).o: $(MAIN).cpp $(FUNC).h
	$(CMP) -c $(MAIN).cpp

$(FUNC).o: $(FUNC).cpp $(FUNC).h 
	$(CMP) -c $(FUNC).cpp

clean:
	rm *.o $(EXEC)
