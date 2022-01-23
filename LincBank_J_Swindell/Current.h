#pragma once
#include "Account.h"
#include <iostream>

using namespace std;

// Inherits from Account
class Current : public Account {
private:
	float overdraft;
	// Overides Account's virtual function checkValidWithdrawal
	// Adds additional check that withdrawal is less than overdraft
	void checkValidWithdrawal(const float& amount);
public:
	Current(int, float);
	string toString() const;
};