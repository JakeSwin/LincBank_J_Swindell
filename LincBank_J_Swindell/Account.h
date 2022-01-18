#pragma once
#include <vector>
#include <iostream>
#include "Transaction.h"

using namespace std;

class Account {
private:
	int id;
protected:
	float balance;
	vector<Transaction*> history;
public:
	Account(int);
	int getId() const;
	vector<Transaction*> sortTransactions();
	virtual string toString() const = 0;
	virtual void deposit(float) = 0;
	virtual void withdraw(float) = 0;
	virtual void transferTo(Account*, float);
	virtual void transferFrom(Account*, float);
	friend ostream& operator<<(ostream&, const Account&);
};