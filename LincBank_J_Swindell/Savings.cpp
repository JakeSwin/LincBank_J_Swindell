#define _CRT_SECURE_NO_WARNINGS
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
	checkValidDeposit(amount);

	interestRate = (isIsa) ? (float)1.15 : (float)0.85;
	isa = isIsa;
	balance = amount;
	history.push_back(new Transaction(TransactionType::initialDeposit, amount));
}

void Savings::deposit(float amount) {
	checkValidDeposit(amount);
	balance += amount;
	history.push_back(new Transaction(TransactionType::deposit, amount));
}

void Savings::withdraw(float amount) {
	checkValidWithdrawal(amount, balance);
	balance -= amount;
	history.push_back(new Transaction(TransactionType::withdraw, amount));
}

float Savings::computeInterest(float years) {
	return balance * pow((1 + (interestRate / 100) / 12), 12 * years);
}

string Savings::toString() const {
	stringstream ss;
	string accountType = (isa) ? "ISA" : "Savings";
	ss << accountType << " account | Balance: \x9C" << balance << "\n";
	for (auto& t : history) {
		ss << *t;
	}
	return ss.str();
}