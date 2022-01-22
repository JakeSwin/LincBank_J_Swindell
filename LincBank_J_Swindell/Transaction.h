#pragma once
#include <iostream>

using namespace std;

// Public Enum defines different types of Transactions that Transaction objects can be initialized with.
// Taking this enum as an argument for the constructor ensures that the input must be one of these types
enum class TransactionType { initialDeposit, deposit, withdraw, transferFrom, transferTo };

class Transaction {
private:
	string desc;
	// Stores timestamp for when transaction object was created
	time_t timestamp;
	TransactionType type;
	float value;
	// Stores Account Number, used only when Transaction is a transfer
	int transferAccount;
	// Overloaded casting to float is private to prevent any unexpected implicit float casting outside this object
	operator float() const;
public:
	// This constructor is used for Transfer Transaction types
	// there is an additional argument for account number
	Transaction(TransactionType, int, float);
	Transaction(TransactionType, float);
	// A series of overloaded operators, used when sorting / searching transaction objects inside Account.cpp
	// Templated so operators can be used on any other type that can be cast to float
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
	// Overloaded << operator to make outputing Transaction objects simpler
	// Removes the need to call toString everytime
	friend ostream& operator<<(ostream& os, const Transaction& a);
	string toString() const;
};