#include <stdio.h>

#include <iostream>
#include <string>

using namespace std;

void printOddOrEven(int number)
{
	if (number % 2 == 0)
	{
		printf("EVEN\n");
	}
	else
	{
		printf("ODD\n");
	}
}

bool checkNumber(string str) 
{
	for (int i = 0; i < str.length(); i++){
		if (isdigit(str[i]) == false) 
			return false;
		else
			return true;	
	}		
}

int main(int argc, char *argv[])
{
	int number = -13;

	// What is this program expected to do?
	// - Shows whether an argument is an ODD or EVEN number.
	// How to launch it?
	// - Execute the binary and pass a parameter to it?
	// - E.g. Open CMD in bin/Debug or bin/Release
	//		  02_odd_even.exe 1		=> Output: ODD
	//		  02_odd_even.exe 2		=> Output: EVEN
	//		  02_odd_even.exe 		=> Output: No program arguments found.
	//		  02_odd_even.exe ABC   => Undefined output (do whatever).
	//		

	// Make sure there are some program arguments available.
	if (argc <= 1)
	{
		printf("No program arguments found.\n");
	}
	// TODO(Gusti): i don't know why this doesn't work, but someone please FIX it.
	
	// --------------- start

	// Get the first argument
	std::string argumentAsString = argv[1];
	const char* argumentAsCharArray = argumentAsString.c_str(); 

	number = std::stoi(argv[1], nullptr, 0);

	if (checkNumber(argumentAsString))
		printOddOrEven(number);
	else
		printf("NAN\n");

	// I tried several ways to solve the bonus requirement, but I failed. I'm missing something...
	// One method was to define a function that checks whether letters or numbers were typed. 
	// I did not delete the function because it does not affect the basic functionality of the program.

	// --------------- stop

	//printOddOrEven(number);
	
	return 0;
}