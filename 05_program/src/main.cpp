#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	// Make sure there are some program arguments available.
	if (argc <= 1)
	{
		printf("No program arguments found.\n");
		return 0;
	}

	// Get the first argument
	
	std::string argumentAsString = argv[1];

	char* ptr = new char[argumentAsString.length() + 1];
	
	if (argc >= 2)
	{
		for(int i = 1; i <= (argc-1); i++) //argc-1 becuse the first argument is the .exe file
		{
			std::cout << argv[i] << "\n"; //m-am complicat data trecuta, da :))
		}	
	}

	delete[] ptr;

	return 0;
}