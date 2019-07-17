#include <iostream>
#include <fstream>
#include "Session.h"

Session::Session(){

	cout << "\t\t\t-----------------------------" << endl;
	cout << "\t\t\tWelcome to The Password Bank!" << endl;
	cout << "\t\t\t   Created by Luis Garduno" << endl;
	cout << "\t\t\t-----------------------------\n" << endl;

	cout << "\t(1) Login" << endl;
	cout << "\t(2) Create Account" << endl;
	cout << "\t(3) Exit" << endl;

	do {																				// loop until a valid option(1,2,3) is entered
		cout << "\tPlease select an option: " << flush;
		cin >> option;

		if(option == 1){
			clearScreen();																// clears screen
			login();																	// calls login function										
			Session();																	// calls Session function
			option = 3;																	// option = 3 to exit do-while loop									
		}
		else if(option == 2){
			clearScreen();
			create();																	// calls create function									
			Session();										
			option = 3;										
		}
		else if(option != 3){								
			cout << "\n\tInvalid input" << endl;			
		}

	} while (option != 3);																// if user input's 3, exit program.								

}

void Session::clearScreen(){															// this function clears the screen by using a for loop and newline's

	sleep_for(seconds(1));																// pause for 1 second

	for(int k = 0; k < 10; k++){
		cout << "\n\n\n\n\n\n\n\n" << endl;
	}
}

void Session::mainReturn(){																// mainReturn simply prints a statement and 
	cout << "\n\t\t\tReturning to main menu" << flush;

	for(int i = 0; i < 3; i++){
		sleep_for(milliseconds(500));													// prints "." each half sec x3
		cout << "." << flush;
	}

	clearScreen();
}


void Session::login(){
	cout << "\t\t\t\t-----" << endl;
	cout << "\t\t\t\tLogin" << endl;
	cout << "\t\t\t\t-----" << endl;

	int attempts = 0;																	// user is allowed 3 attempts before returning to main menu
	username = new char[94];															// username,password is created on HEAP as char
	password = new char[94];

	bool check = true;																	// "bool check" helps determine whether account exists

	while(attempts != 3 && check == true){
		cin.ignore();																	// ignore input until newline is read

		cout << "\tUsername: " << flush;
		cin.get(username,94);															// write to username[94]

		user = new User(username);														// the result of User(username) is saved as "user" on the HEAP
		userText = username;															// username is stored as string on HEAP for later

		cin.ignore();

		cout << "\tPassword: " << flush;
		cin.get(password,94);
		pass = password;																// password is stored as string on HEAP for later

		string accountAttempt = userText + "," + pass;									// new string is created by combining username, "," , and password
		check = user->checkAccount(accountAttempt);										// User class is called for user. Calls checkAccount function

		if(check == true){																// if check = true, keep going
			cout << "\n\tUsername/Password is either incorrect or does not exist" << endl;
			attempts++;																	// attempts = attempts + 1
			cout << "\t\t\t" << 3 - attempts << " attempts remaining" << endl;
		}
	}

	if(check == false){
		clearScreen();					
		user->openAccount();															// if false, open this user's account
	}

	mainReturn();																		// at the end, print mainmenu return 
}

void Session::create(){
	cout << "\n\t\t\t\t--------------" << endl;
	cout << "\t\t\t\tCreate Account" << endl;
	cout << "\t\t\t\t--------------" << endl;
	username = new char[94];															// once again username & password is stored on the HEAP
	password = new char[94];
	rePassword = new char[94];
	bool userCheck = false;																// if username already exists, set userCheck to false 
	bool passCheck = false;																// if passwords don't match, set passCheck to false

	while(userCheck != true){
		cin.ignore();

		cout << "\tEnter Username: " << flush;
		cin.get(username,94);

		user = new User(username);														// create new User w/ username						
		userCheck = user->checkUsername();												// checks to see if username has been used 						
																
		userText = username;															// stores username as string
	}

	while(passCheck != true){
		cin.ignore();

		cout << "\tEnter Password: " << flush;
		cin.get(password,94);
		pass = password;																// stores password as string

		cin.ignore();

		cout << "\tRe-enter password: " << flush;
		cin.get(rePassword,94);
		rePass = rePassword;															// stores rePassword as string


		if(pass == rePass){																// if password strings match
			user->addAccount(password);													// adds username,password to accounts.bat
			string newText = userText + ".bat";											// txt file is named after username
			fstream newAccount(newText, ios::out);										// personal txt file is created for user
			cout << "\n\t\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^" << endl;
			cout << "\t\t\tAccount succesfully created" << endl;
			cout << "\t\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^\n" << endl;

			passCheck = true;															// passwords match & account is created which also exits out of while loop
			newAccount.close();															// close personal file
		}
		else{
			cout << "\n\tSorry, passwords do not match" << endl;
		}
	}

	mainReturn();

}

Session::~Session(){
	//cout << "Session Deconstructor" << endl;
}