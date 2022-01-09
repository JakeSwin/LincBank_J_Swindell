#pragma once
#include "Account.h"
#include "InterestEarning.h"
#include <iostream>

using namespace std;

class Savings : public Account, public InterestEarning {
private:
	float interestRate;
	bool isa;
public:
	Savings(int, bool, float);
	string toString() const;
	void deposit(float);
	void withdraw(float);
	float computeInterest(float years);
	friend void transfer(Account*, Account*, float);
};