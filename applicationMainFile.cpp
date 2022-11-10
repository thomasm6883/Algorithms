/*
-Assignment 5, CS 244, Sprting of 2021.
-use this project as a bas to solve the assignment. 
-means, ou update this code instead of starting from scratch.
-Most of the work will be in the bank_H.h file. 
-CopyRights: Dr. Alnaeli, UW-Stout, 2021
*/

#include "doublyLinkedList_H.h" /*DoublyLinkedList class definition*/
#include "bank_H.h"  /*Bank classes definition and including other utility libraries*/
string menu();
int main()
{
	Bank bank1;
	try {
		if (!bank1.fillBankListFromFile("database_names_balances.txt")) {
			throw 10;
			//throw runtime_error("FILE NOT FOUND\n");
		}
	}
	catch (int e) {
		cout << "File Not Found" << endl;
	}
	/*catch (exception e) {
		cout << e.what();
	}*/
	/*bank1.printAllAccounts();*/

int userEntry = 0;
	/*Note for my CS244 students:system("cls") is used for clearing the console screen. cls is a Dos command*/

	while (userEntry != 4) {
		cout << "**********************************\n";
		cout << menu();
		/*Can you improve this with exceptions?*/

		//is this really improved? its a lot longer...but i used exceptions
		try {
			string entry;
			cin >> entry;
			if (isdigit(entry[0])) {
				userEntry = stoi(entry);
				if (userEntry < 0 || userEntry > 4) {
					throw 201;
				}
			}
			else { throw 101; }
			
			
		}
		catch (int e){
			cout << "EXCEPTION " << e << ": ";
			if (e == 101) {
				cout << "entry must be an integer value" << endl;
			}
			if (e == 201) {
				cout << "entry must be between 0 and 4" << endl;
			}
		}
		

		switch (userEntry) {
		case 0: system("cls"); break;
		case 1: system("cls"); {
			bank1.printAllAccounts();
		}
			  break;
		case 2: system("cls"); {
			double amount;
			cout << "enter amount -> "; 
			/*Can you improve this with exceptions?*/
			try {
				if (!(cin >> amount)) {
					throw 41;
				}
				if (amount < 0) {
					throw 31;
				}
			}
			catch (int e) {
				if (e == 41) {
					cout << "Value must be a double or integer" << endl;
				}
				else if (e == 31) {
					cout << "Value must be positive" << endl;
				}
				exit(0);
			}
			catch (...) {
				cout << "Something went wrong" << endl;
				exit(0);
			}
			
			cout << "Customers with account balance less than " << amount << ":\n";
			bank1.printAccountsBelowAmount(amount);

		}
			  break;
		case 3:system("cls"); {
			BankAccount maxAccount0 = bank1.getMaxAccount();
			cout << maxAccount0 << endl;
		}
			  break;
		case 4:system("cls");
			break;
		default:
			break;
		}
	}/*end while*/

	return 0;
}

string menu() {

	string message;
	message = "0. Clear Screen..\n1. Print All accounts.\n2. Print names of the customer who have balances below a given amount.";
	message = message + "\n3.The customer with the highest balance.\n4: Exit.\nYour Selection --> ";
	return message;
}