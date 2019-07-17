#include <iostream>
#include <fstream>
#include <string>
#include "CodeMaker.h"

/*
	CodeMaker::CodeMaker - the Constructor
This method reads the substitution characters in
from a file and stores them in the codeChar array.
It also sets member variable size.
*/
CodeMaker::CodeMaker(){
	size = 94;
	ifstream inputFile;
	inputFile.open("code.dat");						// Open the file

	for(int ascii = 32; ascii < 127; ascii++){		// Read in data
		inputFile >> codeChar[ascii - 32];
	}

	inputFile.close();								// close file
}

/*
	CodeMaker::encode
This method encodes and returns a clear text string.
*/
string CodeMaker::encode(string s){
	int ascii;
	char newChar;
	string newString = "";							// Will hold the encoded string

	for(unsigned pos = 0; pos < s.length(); pos++){
		ascii = s[pos];								// get the original character's ASCII code

		newChar = codeChar[ascii - 32];				// get the new replacement character

		newString += newChar;						// Concatenate it onto the end of the new string
	}
	return newString;
}

/*
	CodeMaker::decode
This method converts an encoded string back to
clear text and returns it.
*/
string CodeMaker::decode(string s){
	int index;
	char nextChar;
	char originalChar;
	string decodedText = "";

	for(unsigned pos = 0; pos < s.length(); pos++){
		nextChar = s[pos];							// get the next character from the string
	
		index = findIt(codeChar, size, nextChar);	// Call findIt to find it in the array and returns its index

		originalChar = index + 32;					// get the original character by computing it's ASCII code

		// Concatenate this character onto the end of the
		// decoded text string being constructed
		decodedText += originalChar;
	}

	return decodedText;
}

/*
	CodeMaker::findIt
This method performs a linear search on
a character array looking value
*/
int CodeMaker::findIt(char A[], int size, char value){
	int index = 0;
	int position = -1;
	bool found = false;

	while(index < size && !found){
		if(A[index] == value){						// if the value is found
			found = true;							// set the flag
			position = index;						// record the value's subscript
		}
		index++;									// Go to the next element
	}
	return position;								// Return the position, or -1
}