#include <iostream>
#include <fstream>
#include <cstring>
#include "User.h"

User::User(){																	// Default "User" constructor
	cout << "User" << endl;
	
}

User::User(char * username){													// New "User" constructor w/ parameter
	this->username = new char[94];												// save username of this session as new char 
	strcpy(this->username,username);											// copy username from parameter to this->username
}

bool User::checkUsername(){														// Checks to see if username has already been used
	fstream readFile("accounts.bat");											// opens the "accounts.bat" file to read/write
	output = new char[300];														// creates new empty array to hold usernames;
	if(readFile.is_open()){
		while(!readFile.eof()){													// read until end of file
			string tempString = "";												// create temp string;
			int i = 0;															// counter to read char in certain position
			readFile >> output;
			finalText = myCoder.decode(output);									// decode the strings

			while(finalText[i] != ','){											// while char at certain position does not equal ','
				tempString.push_back(finalText[i]);								// add character to the end of newString
				i++;
			}
			string strUsername = username;
			if(tempString == strUsername){										// if strings match, username already exists
				cout << "\tPlease enter a different username\n" << endl;
				return false;
			} 
		}
	}
	
	readFile.close();															// close file
	return true;																// if username does not exist, return true
}

bool User::checkUserAccount(char * account){									// checks to see if account exists (twitter, facebook, etc)
	userText = username;
	string theAccount = account;
	fstream readFile(userText + ".bat");										// opens the "accounts.bat" file to read/write
	output = new char[300];														// creates new empty array to hold usernames;
	if(readFile.is_open()){
		while(!readFile.eof()){													// read until end of file
			string tempString = "";												// create temp string;
			int i = 0;															// counter to read char in certain position
			readFile >> output;
			finalText = myCoder.decode(output);

			while(finalText[i] != ':'){											// while char at certain position does not equal ','
				tempString.push_back(finalText[i]);								// add character to the end of newString
				i++;
			}
			
			if(theAccount == tempString){
				return false;
			}
		}
	}
	
	readFile.close();															// close file
	return true;
}

bool User::viewProfile(string viewAccount){										// display's the account details of a stored account
	userText = username;
	fstream readFile(userText + ".bat");										// opens the "accounts.bat" file to read/write
	output = new char[300];														// creates new empty array to hold usernames;
	if(readFile.is_open()){
		while(!readFile.eof()){													// read until end of file
			int i = 0;															// counter to read char in certain position
			string tempString = "";
			readFile >> output;
			finalText = myCoder.decode(output);

			while(finalText[i] != ':'){
				tempString.push_back(finalText[i]);
				i++;
			}

			if(viewAccount == tempString){
				string theFinal = finalText;
				string accountName,theUsername,thePassword;
				istringstream iss(theFinal);
				getline(iss,accountName,':');
				getline(iss,theUsername,',');
				getline(iss,thePassword);
				cout << "\n\n\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^" << endl;
				cout << "\t\tAccount: " << accountName << endl;
				cout << "\t\tUsername: " << theUsername << endl;
				cout << "\t\tPassword: " << thePassword << endl;
				cout << "\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^" << endl;
				return false;
			}
		}
	}
	
	readFile.close();																// close file
	return true;
}

bool User::checkAccount(string accountAttempt){										// checks to see if account exists
	fstream readFile("accounts.bat");												// opens the "accounts.bat" file to read/write
	output = new char[300];															// creates new empty array to hold usernames;
	if(readFile.is_open()){
		while(!readFile.eof()){														// read until end of file
			int i = 0;																// counter to read char in certain position
			readFile >> output;
			finalText = myCoder.decode(output);

			if(finalText == accountAttempt){
				cout << "\n\t\t^v^v^v^v^v^v" << endl;
				cout << "\t\tlogging in.." << endl;
				cout << "\t\t^v^v^v^v^v^v" << endl;
				return false;
			}
		}
	}
	
	readFile.close();																// close file
	return true;
}

char * User::getUsername(){															// returns username
	return username;
}

char * User::getPassword(){															// returns password
	return password;
}

void User::setUsername(char * username){											// sets inputted char as this-> char
	strcpy(this->username,username);												// copies given username as this username
}

void User::setPassword(char * password){
	strcpy(this->password,password);
}

void User::addAccount(char * password){												// writes account info in "accounts.bat" file
	fstream writeFile("accounts.bat", ios::out | ios::app);
																					// opens "accounts.txt" & begins writting at the bottom of doc
	userText = username;
	pass = password;
	originalText = userText + "," + pass;											// combines username and password into 1 string
	secretCode = myCoder.encode(originalText);
	writeFile << secretCode << endl;												// writes the encoded line in file 

}

void User::clearScreen(){

	sleep_for(seconds(1));

	for(int k = 0; k < 10; k++){
		cout << "\n\n\n\n\n\n\n\n" << endl;
	}
}

void User::userMainReturn(){														// returns to the User's main menu
	cout << "\n\t\t\tReturning to User menu" << flush;

	for(int i = 0; i < 3; i++){
		sleep_for(milliseconds(500));
		cout << "." << flush;
	}

	clearScreen();
}

void User::openAccount(){															// user's main menu
	int userOption;

	cout << "\t\t\t---------------------" << endl;
	cout << "\t\t\tWelcome " << username << endl;
	cout << "\t\t\t---------------------\n" << endl;

	cout << "\t(1) Add" << endl;
	cout << "\t(2) View" << endl;
	cout << "\t(3) Edit" << endl;
	cout << "\t(4) Remove" << endl;
	cout << "\t(5) Logout" << endl;

	while(userOption != 5){
		cout << "\tPlease enter an option (1-5): " << flush;

		cin >> userOption;

		if(userOption > 0 && userOption < 5){
			switch(userOption){
				case 1:																// Add account details
					clearScreen();
					userAdd();
					openAccount();
					userOption = 5;
					break;
				case 2:																// view account details
					clearScreen();
					userView();
					openAccount();
					userOption = 5;
					break;
				case 3:																// edit account details
					clearScreen();
					userEdit();
					openAccount();
					userOption = 5;
					break;
				case 4:																// remove account details
					clearScreen();
					userRemove();
					openAccount();
					userOption = 5;
					break;
				default:
					cout << "\t\tdefault" << endl;
					break;
			}
		}
		else if(userOption != 5){
			cout << "\tInvalid input" << endl;
		}
	}
}

void User::userAdd(){
	cout << "\t\t\t\t-----------" << endl;
	cout << "\t\t\t\tAdd Account" << endl;
	cout << "\t\t\t\t-----------\n" << endl;
	userText = username;
	string accountName,userLogin,userPassword,userTempPassword,textFile;
	account = new char[94];
	textFile = userText + ".bat";
	bool theCheck = false;
	fstream accountFile(textFile, ios::out | ios::app);

	while(theCheck != true){
		cin.ignore();
		cout << "\tEnter Account Name (Ex:twitter,bank,etc) : " << flush;
		cin.get(account,94);

		accountName = account;
		theCheck = checkUserAccount(account);

		if(theCheck != true){
			cout << "\n\tSorry, account with this name already exists." << endl;
		}
	}

	cout << "\tEnter Account Login/Username: " << flush;
	cin >> userLogin;

	do{
		cout << "\tEnter Account Password: " << flush;
		cin >> userPassword;

		cout << "\tRe-enter Account Password: " << flush;
		cin >> userTempPassword;

		if(userPassword != userTempPassword){
			cout << "\n\tPasswords do not match, try again." << endl;
		}

	}while(userPassword != userTempPassword);

	secretCode = myCoder.encode(accountName + ":" + userLogin + "," + userPassword);
	accountFile << secretCode << endl;

	cout << "\n\t\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v" << endl;
	cout << "\t\t\tAccount has been successfully added!" << endl;
	cout << "\t\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v" << endl;

	accountFile.close();

	userMainReturn();
}

void User::userView(){
	cout << "\n\t\t\t\t--------------" << endl;
	cout << "\t\t\t\tView Account/s" << endl;
	cout << "\t\t\t\t--------------" << endl;
	string viewAccount;
	bool theCheck = true;
	account = new char[94];

	while(theCheck != false){
		cin.ignore();
		cout << "\tEnter Account Name (Ex:twitter,bank,etc) : " << flush;
		cin.get(account,94);

		viewAccount = account;
		theCheck = checkUserAccount(account);

		if(theCheck != false){
			cout << "\n\tSorry, this account does not exist." << endl;
		}
	}

	viewProfile(viewAccount);

	cout << "\n\t\tPress enter to continue." << flush;

	cin.ignore(1);
	cin.ignore(1);

	userMainReturn();
}

void User::userEdit(){
	cout << "\n\t\t\t\t-------------------" << endl;
	cout << "\t\t\t\tEdit/Modify Account" << endl;
	cout << "\t\t\t\t-------------------" << endl;
	userText = username;
	string userLogin,userPassword,userTempPassword,deleteLine,line;
	string theFileName = userText + ".bat";
	fstream modFile(theFileName);
	fstream tempFile("temp.bat", ios::out | ios::app);
	bool theCheck = true;
	account = new char[94];

	int a = openMyFile();


	if(a > 0){
		int j = a - 1;
		int k = 0;

		if(modFile.is_open()){
			deleteLine = listOfAccounts[j];
			while(getline(modFile,line)){
				string tempString = "";
				int i = 0;
				finalText = myCoder.decode(line);

				while(finalText[i] != ':'){
					tempString.push_back(finalText[i]);
					i++;
				}

				if(tempString.substr(0,deleteLine.size()) != deleteLine){
					tempFile << line << endl;
					listOfAccounts[k] = tempString;
					k++;
				}
				else if(tempString.substr(0,deleteLine.size()) == deleteLine){
					cout << "\n\tEnter Account Name (Ex: twitter,bank,etc) : " << listOfAccounts[j] << endl;
				
					cout << "\tEnter Account Login/Username: " << flush;
					cin >> userLogin;

					do{
						cout << "\tEnter Account Password: " << flush;
						cin >> userPassword;

						cout << "\tRe-enter Account Password: " << flush;
						cin >> userTempPassword;

						if(userPassword != userTempPassword){
							cout << "\n\tPasswords do not match, try again." << endl;
						}

					}while(userPassword != userTempPassword);

					secretCode = myCoder.encode(listOfAccounts[j] + ":" + userLogin + "," + userPassword);
					
					listOfAccounts[k] = tempString;
					k++;
					tempFile << secretCode << endl;
				}
			}
		}
		
		
		cout << "\n\t\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^" << endl;
		cout << "\t\t\tAccount has been successfully modified!" << endl;
		cout << "\t\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^" << endl;


		modFile.close();
		tempFile.close();
		remove(theFileName.c_str());
		rename("temp.bat", theFileName.c_str());
	}
	userMainReturn();
}

void User::userRemove(){
	cout << "\n\t\t\t\t--------------" << endl;
	cout << "\t\t\t\tRemove Account" << endl;
	cout << "\t\t\t\t--------------" << endl;
	string deleteLine,line;
	userText = username;
	string theFileName = userText + ".bat";
	fstream myFile(theFileName);
	fstream tempFile("temp.bat", ios::out | ios::app);
	
	int a = openMyFile();

	if(a > 0){
		int j = a - 1;
		int k = 0;

		if(myFile.is_open()){
			deleteLine = listOfAccounts[j];
			while(getline(myFile,line)){
				string tempString = "";
				int i = 0;
				finalText = myCoder.decode(line);

				while(finalText[i] != ':'){
					tempString.push_back(finalText[i]);
					i++;
				}

				if(tempString.substr(0,deleteLine.size()) != deleteLine){
					tempFile << line << endl;
					listOfAccounts[k] = tempString;
					k++;

				}

			}
		}

		cout << "\t\t\tRemoving " << deleteLine << endl;



		cout << "\n\t\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v" << endl;
		cout << "\t\t\tAccount has been successfully removed!" << endl;
		cout << "\t\t\t^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v" << endl;

		myFile.close();
		tempFile.close();
		remove(theFileName.c_str());
		rename("temp.bat", theFileName.c_str());
	}

	userMainReturn();
}

int User::openMyFile(){
	userText = username;
	int option,j = 0;
	theOutput = new char[300];
	char verify = 'n';
	bool check = false;


	fstream readFile(userText + ".bat");

	cout << "\tAccounts:" << endl;

	if(readFile.is_open()){
		while(!readFile.eof()){
			int i = 0;
			string tempString = "";
			readFile >> theOutput;
			finalText = myCoder.decode(theOutput);
			while(finalText[i] != ':' && !readFile.eof()){
				tempString.push_back(finalText[i]);
				i++;
			}
			if(readFile.good()){
				cout << "\t\t(" << ++j << ") " << tempString << endl;
				listOfAccounts.push_back(tempString);
			}
		}
	}

	if(j == 0){
		cout << "\t\tNo passwords saved" << endl;
		option = 0;
	}
	else if(j > 0){
		while(check != true){
			do{
				cout << "\n\t\tSelect account (1-" << j <<") : " << flush;
				cin >> option;

				if(option <= 0 || option > j){
					cout << "\n\t\tSorry, invalid input.";
				}

			}while(option <= 0 || option > j);
				
			cout << "\n\t\tYou selected (" << option << ") " << listOfAccounts[option - 1];
			cout << ", correct (Y/N)? : " << flush;
			cin >> verify;

			if(verify == 'Y' || verify == 'y'){
				check = true;
			}
			else if(verify == 'N' || verify == 'n'){
				check = false;
			}
			else{
				cout << "\t\tInvalid input." << endl;
			}
		}
	}
	readFile.close();
	return option;

}

User::~User(){
	cout << "User Deconstructor" << endl;
	delete [] username;
	delete [] output;
}