/* ------------------------------------------------------
CMP2801M: Advanced Programming
Driver program for "LincBank" Assessment Item 1
Semester A 2021

Written by James Brown (jamesbrown@lincoln.ac.uk)

During marking, we will use the exact same notation
as provided in the brief, so make sure you follow that guideline.

You should avoid removing parts of this driver program, but
add to it the necessary code to produce your implementation.

Good luck!
------------------------------------------------------ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>

#include "Transaction.h"
#include "Account.h"
#include "Current.h"
#include "Savings.h"

using namespace std;

void displayOptions() {
	cout << "open [type] [initial_deposit]: open a current (1), savings (2) or ISA (3) account" << endl;
	cout << "view [index]: view balance and recent transactions" << endl;
	cout << "withdraw [sum]: withdraw funds from most recently viewed account" << endl;
	cout << "deposit [sum]: deposit funds into most recently viewed account" << endl;
	cout << "transfer [from] [to] [sum]: transfer funds between accounts" << endl;
	cout << "project [years]: project balance forward in time" << endl;
	cout << "search [sum]: search for a specific transaction by sum from most recently viewed account" << endl;
	cout << "exit: close this application" << endl;
	cout << "options: view these options again" << endl;
}

const void checkNumberOfParameters(const vector<string>& parameters, unsigned int num) {
	if (parameters.size() < num+1) {
		throw out_of_range("Too few parameters!!! You need to provide " + to_string(num) + " parameters for this command");
	}
	else if (parameters.size() > num+1) {
		throw out_of_range("Too many parameters!!! You need to provide " + to_string(num) + " parameters for this command");
	}
}

int main()
{
	vector <string> parameters;
    string userCommand;
	vector <Account*> openAccounts;
	vector <Savings*> openSavingsAccounts;
	Account* mostRecentAccount{};
	// you may also want to store a collection of opened accounts here

	cout << "~~~ Welcome to LincBank! ~~~" << endl;
	displayOptions();

    while (userCommand != "exit")
    {
		parameters.clear(); // clear ready for next command
		cout << endl << ">>> ";

		getline(cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");

		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		// Define all commands as per the brief
		string command = parameters[0];

		if (command.compare("options") == 0)
		{
			displayOptions();
		}
		else if (command.compare("open") == 0)
		{
			// allow a user to open an account
			// e.g., Account* a = new Savings(...);
			try {
				checkNumberOfParameters(parameters, 2);

				float initialDeposit = stof(parameters[2]);
				int newAccountId = openAccounts.size();

				switch (stoi(parameters[1])) {
				case 1:
					openAccounts.push_back(new Current(newAccountId, initialDeposit));
					mostRecentAccount = openAccounts[newAccountId];
					break;
				case 2:
					openAccounts.push_back(new Savings(newAccountId, false, initialDeposit));
					mostRecentAccount = openAccounts[newAccountId];
					break;
				case 3:
					Savings* newAccount = new Savings(newAccountId, true, initialDeposit);
					openAccounts.push_back(newAccount);
					openSavingsAccounts.push_back(newAccount);
					mostRecentAccount = openAccounts[newAccountId];
					break;
				}
			}
			catch (invalid_argument const& e) {
				cout << e.what() << endl;
			}
			catch (out_of_range const& e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("view") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 1);

				unsigned int userInput = stoi(parameters[1]);

				if (userInput < 1 || userInput > openAccounts.size()) {
					cout << "account number does not exist" << endl;
				}
				else {
					cout << *openAccounts[userInput - 1];
					mostRecentAccount = openAccounts[userInput - 1];
				}
			}
			catch (invalid_argument const& e) {
				cout << e.what() << endl;
			}
			catch (out_of_range const& e) {
				cout << e.what() << endl;
				cout << "Displaying all accounts instead" << endl;
				for (auto& a : openAccounts) {
					cout << *a;
				}
			}
			// display an account according to an index (starting from 1)
			// alternatively, display all accounts if no index is provided
		}
		else if (command.compare("withdraw") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 1);

				float amount = stof(parameters[1]);

				if (mostRecentAccount) {
					mostRecentAccount->withdraw(amount);
					cout << "Successfully withdrew \x9C" << amount << " from account " << mostRecentAccount->getId() + 1 << endl;
				}
			}
			catch (invalid_argument const& e) {
				cout << e.what() << endl;
			}
			catch (out_of_range const& e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("deposit") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 1);

				float amount = stof(parameters[1]);

				if (mostRecentAccount) {
					mostRecentAccount->deposit(amount);
					cout << "Successfully deposited \x9C" << amount << " to account " << mostRecentAccount->getId() + 1 << endl;
				}
			}
			catch (invalid_argument const& e) {
				cout << e.what() << endl;
			}
			catch (out_of_range const& e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("transfer") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 3);

				int userFromAccount = stoi(parameters[1]);
				int userToAccount = stoi(parameters[2]);
				float amount = stof(parameters[3]);

				if (userFromAccount < 1 || (unsigned int)userFromAccount > openAccounts.size() ||
					userToAccount < 1 || (unsigned int)userToAccount > openAccounts.size()) {
					cout << "account number does not exist" << endl;
				}
				else {
					Account* From = openAccounts[userFromAccount - 1];
					Account* To = openAccounts[userToAccount - 1];

					From->transferTo(To, amount);
					cout << "Successfully transfered \x9C" << amount << " to account " << To->getId() + 1 << " from account " << From->getId() + 1 << endl;
				}
			}
			catch (invalid_argument const& e) {
				cout << e.what() << endl;
			}
			catch (out_of_range const& e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("project") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 1);

				float years = stof(parameters[1]);

				if (mostRecentAccount) {
					int accountNumber = mostRecentAccount->getId();

					auto it = find_if(openSavingsAccounts.begin(), openSavingsAccounts.end(), [&accountNumber](Savings* obj) { return obj->getId() == accountNumber; });

					if (it != openSavingsAccounts.end()) {
						auto index = distance(openSavingsAccounts.begin(), it);
						Savings* account = openSavingsAccounts[index];
						cout << "Projected balance : \x9C" << account->computeInterest(years) << endl;
					}
				}
			}
			catch (invalid_argument const& e) {
				cout << e.what() << endl;
			}
			catch (out_of_range const& e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("search") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 1);

				float amount = stof(parameters[1]);

				if (mostRecentAccount) {
					Transaction* foundTransaction = mostRecentAccount->findTransactionByAmount(amount);

					cout << "The Transaction that is closest to " + parameters[1] + " is:" << endl;
					cout << *foundTransaction << endl;
				}
			}
			catch (invalid_argument const& e) {
				cout << e.what() << endl;
			}
			catch (out_of_range const& e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("test") == 0)
		{
			/*Transaction* a = new Transaction(TransactionType::deposit, 150);
			Transaction* b = new Transaction(TransactionType::deposit, 50);

			cout << "Test 1: " << (*a < *b) << endl;
			cout << "Test 2: " << (*b > *a) << endl;
			cout << "Test 3: " << (*a >= 100) << endl;
			cout << "Test 4: " << (*b <= 100) << endl;
			cout << "Test 5: " << (*a == *b) << endl;*/
		}
    }

	cout << "Press any key to quit...";
	(void)getchar();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
