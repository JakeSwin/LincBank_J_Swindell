#pragma once
#include <iostream>

using namespace std;

enum class TransactionType { initialDeposit, deposit, withdraw, transferFrom, transferTo };

class Transaction {
private:
	string desc;
	time_t timestamp;
	TransactionType type;
	float value;
	int transferAccount;
public:
	Transaction(TransactionType, int, float);
	Transaction(TransactionType, float);
	bool operator<(const Transaction& t);
	bool operator>(const Transaction& t);
	bool operator<=(const Transaction& t);
	bool operator>=(const Transaction& t);
	friend ostream& operator<<(ostream& os, const Transaction& a);
	string toString() const;
};