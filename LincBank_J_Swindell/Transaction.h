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
	operator float() const;
public:
	Transaction(TransactionType, int, float);
	Transaction(TransactionType, float);
	template<typename T>
	bool operator<(const T& other) { return value < (float)other; };
	template<typename T>
	bool operator>(const T& other) { return value > (float)other; };
	template<typename T>
	bool operator<=(const T& other) { return value <= (float)other; };
	template<typename T>
	bool operator>=(const T& other) { return value >= (float)other; };
	template<typename T>
	bool operator==(const T& other) { return value == (float)other; };
	template<typename T>
	float operator+(const T& other) { return value + (float)other; };
	template<typename T>
	float operator-(const T& other) { return value - (float)other; };
	friend ostream& operator<<(ostream& os, const Transaction& a);
	string toString() const;
};