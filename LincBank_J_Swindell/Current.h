#pragma once
#include "Account.h"
#include <iostream>

using namespace std;

class Current : public Account {
private:
	float overdraft;
	void checkValidWithdrawal(const float& amount, const float& balance, const float& overdraft);
public:
	Current(int, float);
	string toString() const;
	void deposit(float);
	void withdraw(float);
	void transferTo(Account*, float);
};