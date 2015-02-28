#include "Alien.h"
#include <string>
#include <sstream>
#include <iostream>

//Displays a message and gets input. Only cares about the first character entered.
int Alien::getTraitInput()
{
    char checkChar;
    char second;

    cout << "Do you want to use Lasers, Shields, Diplomacy, Trickery, " <<endl;
    cout << "Speed, Navigation, Bravery, or Caution? "; 
    while (1)
    {
    	checkChar = toupper(firstCharEntered(&second));
	second = toupper(second);
	switch (checkChar)
	{
	    case 'L':
		return 1;
	    case 'S':
		if (second == 'H')
		{
		    return 2;
		}
		else if (second == 'P')
		{
		    return 5;
		}
		else break;
	    case 'T':
		return 3;
	    case 'D':
		return 4;
	    case 'N':
		return 6;
	    case 'B':
		return 7;
	    case 'C':
		return 8;
	}
	cout << "Invalid input. Please try again" << endl;
    }
}

//gets input from the user and returns the first character they typed
//whitespace characters don't count.
char firstCharEntered(char* second)
{
  string input;
  int i = 0;
  int whiteSpace = 0;

  getline(cin,input);
  while (input[i] != '\0')
    {
      i++;
      if (isspace(input[i]) && i == whiteSpace)
        {
          whiteSpace++;
        }
    }
  *second = input[whiteSpace+1];
  return input[whiteSpace];
}

