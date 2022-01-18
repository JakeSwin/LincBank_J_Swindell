#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>

#include "Current.h"

using namespace std;

void checkValidDeposit(float amount) {
	if (amount <= 0) {
		throw invalid_argument("Cannot deposit an ammount of <= £0");
	}
}

void checkValidWithdrawal(float amount, float balance, float overdraft) {
	if (amount > overdraft) {
		throw invalid_argument("Cannot withdraw/transfer over \x9C" + to_string(overdraft) + " as per account overdraft limit.");
	}
	else if (amount > balance) {
		throw invalid_argument("Cannot withdraw/transfer more than account balance");
	}
	else if (amount <= 0) {
		throw invalid_argument("Cannot withdraw/transfer an ammount of <= £0");
	}
}

Current::Current(int id, float amount) : Account(id) {
	checkValidDeposit(amount);
	balance = amount;
	overdraft = 500.0;
	history.push_back(new Transaction(TransactionType::initialDeposit, amount));
}

void Current::deposit(float amount) {
	checkValidDeposit(amount);
	balance += amount;
	history.push_back(new Transaction(TransactionType::deposit, amount));
}

void Current::withdraw(float amount) {
	checkValidWithdrawal(amount, balance, overdraft);
	balance -= amount;
	history.push_back(new Transaction(TransactionType::withdraw, amount));
}

void Current::transferTo(Account* to, float amount) {
	checkValidWithdrawal(amount, balance, overdraft);
	Account::transferTo(to, amount);
}

string Current::toString() const {
	stringstream ss;
	ss << "Current account | Balance: \x9C" << balance << "\n";
	for (auto& t : history) {
		ss << *t;
	}
	return ss.str();
}