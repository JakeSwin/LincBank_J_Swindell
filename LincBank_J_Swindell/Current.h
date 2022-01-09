#pragma once
#include "Account.h"
#include <iostream>

using namespace std;

class Current : public Account {
private:
	float overdraft;
public:
	Current(int, float);
	string toString() const;
	void deposit(float);
	void withdraw(float);
	void transferTo(Account*, float);
};