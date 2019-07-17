#ifndef USER
#define USER
#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>			// system, NULL
#include <algorithm>		// remove, rename
#include "CodeMaker.h"


using std::fstream;
using std::ios;
using std::flush;
using std::cin;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using std::istringstream;
using std::vector;
using std::remove;
using std::rename;


class User{
	public:
		User();
		string originalText,secretCode,finalText,userText,pass;
		CodeMaker myCoder;
		User(char * username);
		bool checkUsername();
		bool checkUserAccount(char * account);
		bool viewProfile(string viewAccount);
		bool checkAccount(string accountAttempt);
		char * getUsername();
		char * getPassword();
		void setUsername(char * username);
		void setPassword(char * password);
		void addAccount(char * password);
		void openAccount();
		void clearScreen();
		void userMainReturn();
		void userAdd();
		void userView();
		void userEdit();
		void userRemove();
		int openMyFile();
		vector<string> listOfAccounts;
		~User();

	private:
		char * username;
		char * password;
		char * rePassword;
		char * output;
		char * account;
		char * theOutput;

};

#endif