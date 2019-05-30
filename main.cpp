#include "hashtable.h"
#include "passserver.h"
#include <cctype>	
#include <utility>
#include <iostream>
using namespace std;
void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
bool validChoice(char);
char userInput();

int main()
{
	int capacity;
	cout << "Enter preferred hash table capacity: ";
	cin >> capacity;
	if( capacity > 999)
	{
		cout << "Size is too large.\nSet to default capacity (101).";
		capacity = 101;
	}
	PassServer server(capacity);
//Menu();
	char choice;
	do{
		choice = userInput();
		switch (choice)
		{
			case 'L': {
				string filename;
				cout << "Enter password file name to load from: ";
				cin>>filename;
				if(!server.load(filename.c_str()))
					cout << "Cannot open "<< filename << "\n";
				} break;
			case 'A':{
				string username;
				string password;
				cout << "Enter username: ";
				cin>>username;
				cout << "Enter password: ";
				cin>>password;
				pair<string, string> entry(username, password);
				if(server.addUser(entry))
					cout << "User " << username << " added.\n";
				else
					cout << "User already exists. Could not add User.\n";
			}break;
			case 'R':{
				string username;
				cout << "Enter username: ";
				cin >> username;
				if(server.removeUser(username))
					cout << "User " << username << " deleted.\n";
				else
					cout << "User not found. Could not delete user.\n";
			}break;
			case 'C':{
				string username, oldpass, newpass;
				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				cin >> oldpass;
				pair<string, string> user(username, oldpass);
				if(server.changePassword(user, newpass))
					cout << "Password changed for user " << username << '\n';
				else
					cout << "Could not change user password.\n";
			}break;
			case 'F':{
				string username;
				cout << "Enter username: ";
				cin >> username;
				if(server.find(username))
					cout << "User " << "'" << username << "'" << " found.\n";
				else
					cout << "User " << "'" << username << "'" << " not found.\n";
			}break;
			case 'D': server.dump();
				break;
			case 'S': cout << "Size of hashtable: " << server.size() << '\n';
				break;
			case 'W':{
				string filename;
				cout << "Enter password file name to write to: ";
				cin >> filename;
				server.write_to_file(filename.c_str());
			}
			case 'X': break;
			
		}
		}while (choice != 'X');
	return 0;
}

bool validChoice(char input)
{
	if (input == 'L' || input == 'A' || input == 'R' || input == 'C' || input == 'F' || input == 'D' || input == 'S' || input == 'W' || input == 'X')
		return true;
	return false;
}

char userInput()
{
	Menu();
	char choice;
	cin >> choice;
	choice = toupper(choice);
	//cin.get();
	while (validChoice(choice) == false)
	{
		cout << "Invalid entry. Try again.\n";
		userInput();
	}
	return choice;
}
