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

/// <summary>
/// Menu function for program
/// </summary>
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

/// <summary>
/// Error Checking function for number of parameters
/// </summary>
/// <param name="parameters">Reference to parameter list</param>
/// <param name="num">Number of parameters needed</param>
/// <returns></returns>
const void checkNumberOfParameters(const vector<string>& parameters, unsigned int num) {
	if (parameters.size() < num+1) {
		throw runtime_error("Too few parameters!!! You need to provide " + to_string(num) + " parameters for this command");
	}
	else if (parameters.size() > num+1) {
		throw runtime_error("Too many parameters!!! You need to provide " + to_string(num) + " parameters for this command");
	}
}

int main()
{
	vector <string> parameters;
    string userCommand;
	vector <Account*> openAccounts;
	Account* mostRecentAccount{};

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
			try {
				checkNumberOfParameters(parameters, 2);

				float initialDeposit = stof(parameters[2]);
				int newAccountId = openAccounts.size();
				string newAccountType;

				// Create appropriate Account type based on user input
				switch (stoi(parameters[1])) {
				case 1:
					openAccounts.push_back(new Current(newAccountId, initialDeposit));
					newAccountType = "Current";
					break;
				case 2:
					openAccounts.push_back(new Savings(newAccountId, false, initialDeposit));
					newAccountType = "Savings";
					break;
				case 3:
					openAccounts.push_back(new Savings(newAccountId, true, initialDeposit));
					newAccountType = "ISA";
					break;
				}
				cout << "Successfully opened a new " << newAccountType << " account with balance of \x9C" << initialDeposit << endl;
				mostRecentAccount = openAccounts[newAccountId];
			}
			catch (invalid_argument const& e) {
				// Catches errors in type conversion for stof func
				cout << "Input parameter must be numerical" << endl;
			}
			catch (runtime_error const& e) {
				// Catches all custom defined throws
				cout << e.what() << endl;
			}
		}
		else if (command.compare("view") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 1);

				unsigned int userInput = stoi(parameters[1]);

				// Check if account number inuputted is valid
				if (userInput < 1 || userInput > openAccounts.size()) {
					cout << "account number does not exist" << endl;
				}
				else {
					// Overloaded << operator on Account object calls internal toString Method
					cout << *openAccounts[userInput - 1];
					// Change most recent account for future use in other commands
					mostRecentAccount = openAccounts[userInput - 1];
				}
			}
			catch (invalid_argument const& e) {
				cout << "Input parameter must be numerical" << endl;
			}
			catch (runtime_error const& e) {
				// If invalid parameters are provided for this command 
				// then we can output information for all accounts
				cout << e.what() << endl;
				cout << "Displaying all accounts instead \n" << endl;
				for (auto& a : openAccounts) {
					cout << *a;
				}
			}
		}
		else if (command.compare("withdraw") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 1);

				float amount = stof(parameters[1]);

				// Only executes if most recent account is not null
				if (mostRecentAccount) {
					mostRecentAccount->withdraw(amount);
					cout << "Successfully withdrew \x9C" << amount << " from account " << mostRecentAccount->getId() + 1 << endl;
				}
				else {
					cout << "There is no account to withdraw from" << endl;
				}
			}
			catch (invalid_argument const& e) {
				cout << "Input parameter must be numerical" << endl;
			}
			catch (runtime_error const& e) {
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
				else {
					cout << "There is no account to deposit into" << endl;
				}
			}
			catch (invalid_argument const& e) {
				cout << "Input parameter must be numerical" << endl;
			}
			catch (runtime_error const& e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("transfer") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 3);

				unsigned int userFromAccount = stoi(parameters[1]);
				unsigned int userToAccount = stoi(parameters[2]);
				float amount = stof(parameters[3]);

				// Checks that both account numbers are valid and do exist
				if (userFromAccount < 1 || userFromAccount > openAccounts.size() ||
					userToAccount < 1 || userToAccount > openAccounts.size()) {
					cout << "account number does not exist" << endl;
				}
				else {
					// Copy Account pointers from openAccounts vector
					// -1 since account inputs are indexed starting from 1 
					Account* From = openAccounts[userFromAccount - 1];
					Account* To = openAccounts[userToAccount - 1];
					transfer(*From, *To, amount);
					
					cout << "Successfully transfered \x9C" << amount << " to account " << To->getId() + 1 << " from account " << From->getId() + 1 << endl;
				}
			}
			catch (invalid_argument const& e) {
				cout << "Input parameter must be numerical" << endl;
			}
			catch (runtime_error const& e) {
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

					// Attempt to dynamic cast Account pointer to InterestEarning Pointer
					// Will only succeed if pointer is for Savings Account
					// Since Current does not inherit from InterestEarning
					if (InterestEarning* IE = dynamic_cast<InterestEarning*>(openAccounts[accountNumber])) {
						// If cast succeeds then output computed interest
						cout << "Projected balance : \x9C" << IE->computeInterest(years) << endl;
					}
					else {
						// Otherwise Account pointer was not for a Savings Account
						cout << "Currently selected account is not a Savings Account, Please select a Savings Account and try again." << endl;
					}
				}
			}
			catch (invalid_argument const& e) {
				cout << "Input parameter must be numerical" << endl;
			}
			catch (runtime_error const& e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("search") == 0)
		{
			try {
				checkNumberOfParameters(parameters, 1);

				float amount = stof(parameters[1]);

				if (mostRecentAccount) {
					// Returns pointer to trancaction that is closest to input amount
					Transaction* foundTransaction = mostRecentAccount->findTransactionByAmount(amount);

					cout << "The Transaction that is closest to " + parameters[1] + " is:" << endl;
					cout << *foundTransaction << endl;
				}
			}
			catch (invalid_argument const& e) {
				cout << "Input parameter must be numerical" << endl;
			}
			catch (runtime_error const& e) {
				cout << e.what() << endl;
			}
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
