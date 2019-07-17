#ifndef SESSION
#define SESSION
#include "User.h"

class Session {

	public:
		Session();
		void clearScreen();
		void mainReturn();
		void login();
		void create();
		~Session();

	private:
		int option;
		User * user;
		string userText;
		string pass;
		string rePass;
		char * username;
		char * password;
		char * rePassword;
};

#endif