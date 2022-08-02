#include <stdio.h>
#include <iostream>
#include <cstring>

using namespace std;

void main() {
	const char* str = "sssseeerrrrggggiiiiuuu";
	int asciiLen = (int)'z' - (int)'A'; // TODO figure out how much data you want to allocate
	int* counts = new int[asciiLen]; // allocate data

	for (int i = 0; i < asciiLen; ++i) {
		counts[i] = 0;
	}

	for (int j = 0; j < strlen(str); j++) {
		//TODO this should loop over all chars in 'str'
		int letterCode = (int)str[j]; // Somebody should replace this with the actual char 
		int pos = letterCode - int('A');
		counts[pos]++;
	}
	//TODO increment value in 'counts' array based based on 'pos'. Use pointer arithmetics pls 

	for (int i = 0; i < asciiLen; ++i) {
		// print 'actual letter = occurrence'
		cout << (char)(i + 65) << "  " << counts[i] << endl;
	}

	delete[] counts;
}