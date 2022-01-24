#include <iostream>
#include <sstream>
#include <string>

#include "Savings.h"

using namespace std;

/// <summary>
/// Constructor for Class Savings,
/// Initializes ID, isa and provides an intial deposit
/// </summary>
/// <param name="id">Account ID</param>
/// <param name="isIsa">true if ISA</param>
/// <param name="amount">Initial Deposit</param>
Savings::Savings(int id, bool isIsa, float amount) : Account(id) {
	if (isIsa && amount < 1000) {
		throw runtime_error("ISA initial balance must be >= 1000");
	}
	else if (amount != 0) { checkValidDeposit(amount); }

	interestRate = (isIsa) ? (float)1.15 : (float)0.85;
	isa = isIsa;
	balance = amount;
	history.push_back(new Transaction(TransactionType::initialDeposit, amount));
}

/// <summary>
/// Projects the Savings Account's balance in X years based on it's interest rate
/// </summary>
/// <param name="years">How many year to project interest for</param>
/// <returns>Accont's Projected balance</returns>
float Savings::computeInterest(float years) {
	return balance * pow((1 + (interestRate / 100) / 12), 12 * years);
}

/// <summary>
/// Formats and returns output information of Savings Account
/// </summary>
/// <returns>Formatted output string of Savings Account</returns>
string Savings::toString() const {
	stringstream ss;
	string accountType = (isa) ? "ISA" : "Savings";
	ss << accountType << " account | Balance: \x9C" << balance << "\n";
	// For every Transaction object in history, append its contents to stringstream
	// Uses Transactions overridden << operator
	for (auto& t : history) {
		ss << *t;
	}
	return ss.str();
}