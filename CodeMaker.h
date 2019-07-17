#ifndef CODEMAKER
#define CODEMAKER

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

class CodeMaker{
	
	public:
		CodeMaker();
		string encode(string);
		string decode(string);

	private:
		int size;
		char codeChar[94];			// Array to hold the substitutions
									// for the 94 printable ASCII chars
		int findIt(char[], int, char);

};

#endif