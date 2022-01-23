#pragma once
#include <vector>
#include <iostream>
#include "Transaction.h"

using namespace std;

class Account {
private:
	// ID is private so it cannot be changed once initialized
	int id;
	vector<Transaction*> sortTransactions();
protected:
	float balance;
	vector<Transaction*> history;
	virtual void checkValidDeposit(const float& amount);
	virtual void checkValidWithdrawal(const float& amount);
public:
	Account(int);
	~Account();
	int getId() const;
	Transaction* findTransactionByAmount(float amount);
	virtual string toString() const = 0;
	virtual void deposit(float);
	virtual void withdraw(float);
	friend void transfer(Account&, Account&, float);
	// Overloaded << operator to make outputing Account objects simpler
	// Removes the need to call toString everytime
	friend ostream& operator<<(ostream&, const Account&);
};