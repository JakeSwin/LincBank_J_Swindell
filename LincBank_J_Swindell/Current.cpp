#include <iostream>
#include <sstream>
#include <string>

#include "Current.h"

using namespace std;

/// <summary>
/// Overides base account checkValidWithdrawal, also checks if amount is less than balance + overdraft
/// </summary>
/// <param name="amount">Amount to Withdraw/Transfer</param>
void Current::checkValidWithdrawal(const float& amount) {
	// Adds an additional withdrawal check to current accounts
	if (amount > (balance + overdraft)) {
		throw runtime_error("Cannot withdraw/transfer over \x9C" + to_string(overdraft) + " as per account overdraft limit.");
	}
	else if (amount <= 0) {
		throw runtime_error("Cannot withdraw/transfer an ammount of <= \x9C 0");
	}
}

/// <summary>
/// Constructor for Current Accounts
/// </summary>
/// <param name="id">Account ID</param>
/// <param name="amount">Initial Deposit Amount</param>
Current::Current(int id, float amount) : Account(id) {
	if (amount != 0) { checkValidDeposit(amount); }
	balance = amount;
	overdraft = (float)500;
	history.push_back(new Transaction(TransactionType::initialDeposit, amount));
}

/// <summary>
/// Formats and returns output information of Current Account
/// </summary>
/// <returns>Formatted output string of Current Account</returns>
string Current::toString() const {
	stringstream ss;
	ss << "Current account | Balance: \x9C" << balance << "\n";
	// For every Transaction object in history, append its contents to stringstream
	// Uses Transactions overridden << operator
	for (auto& t : history) {
		ss << *t;
	}
	return ss.str();
}