#include <iostream>
#include <sstream>
#include <string>

#include "Transaction.h"

using namespace std;

/// <summary>
/// Constructor for Transaction Object.
/// Includes parameter for account number, 
/// therefore should only be used for transferTo or transferFrom TransactionTypes.
/// </summary>
/// <param name="t">Type of Transaction</param>
/// <param name="a">Account Number</param>
/// <param name="v">Monetary value for Transaction</param>
Transaction::Transaction(TransactionType t, int a, float v) {
	string d;
	switch (t) {
	case TransactionType::initialDeposit:
		throw runtime_error("account number argument is irrelevent for TransactionTypes other than transferTo and transferFrom");
		break;
	case TransactionType::deposit:
		throw runtime_error("account number argument is irrelevent for TransactionTypes other than transferTo and transferFrom");
		break;
	case TransactionType::withdraw:
		throw runtime_error("account number argument is irrelevent for TransactionTypes other than transferTo and transferFrom");
		break;
	case TransactionType::transferTo: d = "transfer to account " + to_string(a); break;
	case TransactionType::transferFrom: d = "transfer from account " + to_string(a); break;
	}
	desc = d;
	value = v;
	type = t;
	// save account number for transfer in this attribute
	transferAccount = a;
	// get and save current time;
	timestamp = time(0);
}

/// <summary>
/// Constructor for Transaction Object.
/// Does not include parameter for account number, 
/// therefore should not be used for transfer TransactionTypes.
/// </summary>
/// <param name="t">Type of Transaction</param>
/// <param name="v">Monetary value for Transaction</param>
Transaction::Transaction(TransactionType t, float v) {
	string d;
	switch (t) {
		case TransactionType::initialDeposit: d = "initial deposit"; break;
		case TransactionType::deposit: d = "deposit"; break;
		case TransactionType::withdraw: d = "withdraw"; break;
		case TransactionType::transferTo: 
			throw runtime_error("For transferTo and transferFrom types, please provide an additional account number argument");
			break;
		case TransactionType::transferFrom: 
			throw runtime_error("For transferTo and transferFrom types, please provide an additional account number argument");
			break;
	}
	desc = d;
	value = v;
	type = t;
	// this transaction is not a transfer and so has a null (-1) value for transfer account
	transferAccount = -1;
	// get and save current time;
	timestamp = time(0);
}

/// <summary>
/// Formats and returns output information of Transaction object
/// </summary>
/// <returns>Formatted output string of Transaction object</returns>
string Transaction::toString() const {
	stringstream ss;
	// charater buffer used to output results of ctime_s
	char tmBuff[30];
	// Converts time_t timestamp into correctly formatted string and ouputs into buffer tmBuff
	ctime_s(tmBuff, sizeof(tmBuff), &timestamp);
	// If transaction is of type withdraw or transferTo then append a minus sign to string to indicate a negative amount
	char posOrNeg = (type == TransactionType::withdraw || type == TransactionType::transferTo) ? '-' : '\0';
	// Append info to stringstream object and outputs result
	ss << "-- " << desc << ": " << posOrNeg << "\x9C" << value << " on " << tmBuff;
	return ss.str();
}

/// <summary>
/// Private Overload for float casting, simply returns the internal attribute value
/// </summary>
Transaction::operator float() const { return value; }

/// <summary>
/// Overrides << operator to output correctly formatted data from Transaction object.
/// </summary>
/// <param name="os">Output stream object</param>
/// <param name="a">Reference to transaction object</param>
/// <returns>Output stream object</returns>
ostream& operator<<(ostream& os, const Transaction& a) { return os << a.toString(); }