//
//  main.cpp
//  Bar Code Database
//
//  Created by Hunter Boleman on 7/28/15.
//  Copyright (c) 2015 Hunter Boleman. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int everyother = 0;
int linenum = 0;
int const SIZE = 5000;
int const SIZEA = 10000;
bool quit = false;
string strLine = "";
string UPC[SIZE];
string name[SIZE];
string all[SIZEA];
string scan = "";
string scanName;
string listName;
string clear = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

void readfile();
bool inDatabase();
void newEntry();
void listEntry();
void mainMenu();
void scanLoop();
void resetDatabase();
void resetList();


int main(){
	do{
		mainMenu();
	} while (quit == false);
	return 0;
}

void scanLoop(){
	cout << clear;
	cout << "Starting Up..." << endl;
	for (int i = 0; i < SIZE; i++){
		UPC[i] = "";
		name[i] = "";
	}
	readfile();
	//SCAN LOOP
	do{
		cout << clear;
		if (inDatabase() == true)
			listEntry();
	} while (scan != "q" && scan != "Q");
}

void readfile(){
	cout << clear;
	ifstream bc_database("bc_database.txt");
	if (bc_database.is_open()){
		string strLine = "";

		while (getline(bc_database, strLine)){
			all[linenum] = strLine;
			linenum++;
		}
		linenum = 0;
		bc_database.close();


		//Sorting all into each one
		for (int i = 0; i < SIZEA; i++){
			if (i == 0){
				UPC[0] = all[i];
			}
			else if (i == 1){
				name[0] = all[i];
			}
			else if (all[i] == "\n"){
				all[i] = "";
			}
			else if (i % 2 || i == 0){
				name[(i / 2)] = all[i];
			}
			else if (!(i % 2) && i != 0){
				UPC[(i / 2)] = all[i];
			}
		}
	}
	else{
		cout << "ERROR: Database Cannot Be Opened!" << endl;
	}
}

bool inDatabase(){
	cout << clear;
	if (scan != ""){
		cout << "Added: \"";
		for (int i = 0; i < SIZE; i++){
			if (UPC[i] == scan)
				cout << name[i];
		}
		cout << "\" to list." << endl;
	}
	cout << "(q to quit) Enter UPC: ";
	cin >> scan;
	cin.ignore(100000, '\n');
	if (scan != "q" && scan != "Q"){
		for (int i = 0; i < SIZE; i++){
			if (UPC[i] == scan){
				cout << "Found!" << endl;
				return true;
			}
		}
		int newEntryChoice = 1;
		cout << '\a';
		do{
			cout << "Not Found!" << endl;
			cout << endl;
			cout << "Would you like to create a new entry?" << endl;
			cout << "1. Yes" << endl;
			cout << "2. No" << endl;
			if (newEntryChoice < 1 || newEntryChoice > 2)
				cout << "ERROR: Invalid Choice!" << endl;
			cout << ": ";
			cin >> newEntryChoice;
			cin.ignore(100000, '\n');
		} while (newEntryChoice < 1 || newEntryChoice > 2);
		if (newEntryChoice == 1){
			newEntry();
			readfile();
			return true;
		}
		else if (newEntryChoice == 2){
			return false;
		}
	}
	return false;
}

void newEntry(){
	cout << endl;
	cout << "What is the product name?" << endl;
	cout << ": ";
	getline(cin, scanName);
	ofstream bc_database("bc_database.txt", ios::app);
	if (bc_database.is_open()){
		bc_database << scan << endl << scanName << endl;
		bc_database.close();
	}
}

void listEntry(){
	for (int i = 0; i < SIZE; i++){
		if (UPC[i] == scan)
			listName = name[i];
	}
	ofstream bc_list("bc_list.txt", ios::app);
	if (bc_list.is_open()){
		bc_list << "[] " << listName << endl << endl;
		bc_list.close();
	}
}

void mainMenu(){
	int mainMenuChoice = 1;
	do{
		cout << clear;
		cout << "---Barcode Scanning Database V1.0---" << endl;
		cout << endl << endl;
		cout << "1. Scanning Mode" << endl;
		cout << "2. About" << endl;
		cout << "3. Reset List" << endl;
		cout << "4. Reset Database" << endl;
		cout << "5. Quit" << endl;
		if (mainMenuChoice < 1 || mainMenuChoice > 5)
			cout << "ERROR: Invalid Choice" << endl;
		cout << ": ";
		cin >> mainMenuChoice;
		cin.ignore(100000, '\n');
	} while (mainMenuChoice < 1 || mainMenuChoice > 5);
	switch (mainMenuChoice){
	case 1:{
		scanLoop();
		break;
	}
	case 2:{
		cout << clear;
		cout << "                       Barcode Scanning Database" << endl;
		cout << "                              Version 1.0" << endl;
		cout << "                       Created By: Hunter Boleman" << endl;
		cout << endl;
		cout << "This application was created in order to produce a shopping list as you throw" << endl;
		cout << "things away." << endl;
		cout << "This application will create two text files in order to function. Because of" << endl;
		cout << "this, it is recommended that you place the application in it's own folder." << endl;
		cout << endl;
		cout << "Press enter to return to the main menu..." << endl;
		cin.get();
		break;
	}
	case 3:{
		resetList();
		break;
	}
	case 4:{
		resetDatabase();
		break;
	}
	case 5:{
		quit = true;
		break;
	}
	}
}

void resetList(){
	cout << clear;
	int resetListChoice = 1;
	do{
		cout << clear;
		cout << "Are you sure you want to clear the list?" << endl;
		cout << endl << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		if (resetListChoice < 1 || resetListChoice > 2)
			cout << "ERROR: Invalid Choice" << endl;
		cout << ": ";
		cin >> resetListChoice;
		cin.ignore(100000, '\n');
	} while (resetListChoice < 1 || resetListChoice > 2);

	switch (resetListChoice){
	case 1:{
		ofstream bc_list("bc_list.txt", ios::trunc);
		if (bc_list.is_open()){
			bc_list << "";
			bc_list.close();
		}
	}
	}
	cout << clear;
	cout << "List has been reset." << endl;
	cout << "Press enter to continue..." << endl;
	cin.get();
}

void resetDatabase(){
	cout << clear;
	int resetDatabaseChoice = 1;
	do{
		cout << clear;
		cout << "Are you sure you want erase the database?" << endl;
		cout << endl << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		if (resetDatabaseChoice < 1 || resetDatabaseChoice > 2)
			cout << "ERROR: Invalid Choice" << endl;
		cout << ": ";
		cin >> resetDatabaseChoice;
		cin.ignore(100000, '\n');
	} while (resetDatabaseChoice < 1 || resetDatabaseChoice > 2);

	switch (resetDatabaseChoice){
	case 1:{
		cout << clear;
		int resetDatabaseChoice = 1;
		do{
			cout << clear;
			cout << "This will ERASE your database, are you sure?" << endl;
			cout << endl << endl;
			cout << "1. Yes" << endl;
			cout << "2. No" << endl;
			if (resetDatabaseChoice < 1 || resetDatabaseChoice > 2)
				cout << "ERROR: Invalid Choice" << endl;
			cout << ": ";
			cin >> resetDatabaseChoice;
			cin.ignore(100000, '\n');
		} while (resetDatabaseChoice < 1 || resetDatabaseChoice > 2);

		switch (resetDatabaseChoice){
		case 1:{
			ofstream bc_database("bc_database.txt", ios::trunc);
			if (bc_database.is_open()){
				bc_database << "";
				bc_database.close();
			}
		}
			   break;
		}
	}
	}
	cout << clear;
	cout << "Database has been reset." << endl;
	cout << "Press enter to continue..." << endl;
	cin.get();
}