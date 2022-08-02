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
	
	if (argc > 2)
	{
		for(int i = 1; i <= (argc-1); i++) //argc-1 becuse the first argument is the .exe file
		{
			std::string argumentAsString = argv[i];
			std::strcpy(ptr, argumentAsString.c_str()); //a c-string copy of argumentAsString

			char* ptr2 = std::strtok(ptr, " "); 
			while (ptr2 != 0)
			{
				std::cout << ptr2 << '\n';
				ptr2 = std::strtok(NULL, " ");
			}
		}	
	}

	delete[] ptr;

	return 0;
}