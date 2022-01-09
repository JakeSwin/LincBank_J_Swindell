#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>

#include "Savings.h"

using namespace std;

void checkValidWithdrawal(float amount, float balance) {
	if (amount > balance) {
		throw invalid_argument("Cannot withdraw/transfer more than account balance");
	}
}

void checkValidDeposits(float amount) {
	if (amount < 0) {
		throw invalid_argument("Cannot deposit an ammount of <= £0");
	}
}

Savings::Savings(int id, bool isIsa, float amount) : Account(id) {
	if (isIsa && amount < 1000) {
		throw invalid_argument("ISA initial balance must be >= 1000");
	}
	checkValidDeposits(amount);

	interestRate = (isIsa) ? (float)1.15 : (float)0.85;
	isa = isIsa;
	balance = amount;
	history.push_back(Transaction(TransactionType::initialDeposit, amount));
}

void Savings::deposit(float amount) {
	checkValidDeposits(amount);
	balance += amount;
	history.push_back(Transaction(TransactionType::deposit, amount));
}

void Savings::withdraw(float amount) {
	checkValidWithdrawal(amount, balance);
	balance -= amount;
	history.push_back(Transaction(TransactionType::withdraw, amount));
}

float Savings::computeInterest(float years) {
	return balance * pow((1 + (interestRate / 100) / 12), 12 * years);
}

string Savings::toString() const {
	stringstream ss;
	ss << "Savings account | Balance: \x9C" << balance << "\n";
	for (auto& t : history) {
		ss << t;
	}
	return ss.str();
}