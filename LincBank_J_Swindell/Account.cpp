#include "Account.h"

using namespace std;

/// <summary>
/// Initialises balance to 0 and ID to input
/// </summary>
/// <param name="accountId">ID for account</param>
Account::Account(int accountId) {
	balance = 0;
	id = accountId;
}

/// <summary>
/// Deletes all Transaction pointers stored inside history
/// </summary>
Account::~Account() {
	for (auto t : history) {
		delete t;
	}
}

/// <summary>
/// Returns Account ID
/// </summary>
/// <returns>Account ID</returns>
int Account::getId() const{
	return id;
}

/// <summary>
/// Checks if withdrawal amount is valid
/// </summary>
/// <param name="amount">Amount to Withdraw/Transfer</param>
void Account::checkValidWithdrawal(const float& amount){
	if (amount > balance) {
		throw runtime_error("Cannot withdraw/transfer more than account balance");
	}
	else if (amount <= 0) {
		throw runtime_error("Cannot withdraw/transfer an ammount of <= \x9C 0");
	}
}

/// <summary>
/// Checks if Deposit Amount is valid
/// </summary>
/// <param name="amount">Amount to Deposit</param>
void Account::checkValidDeposit(const float& amount){
	if (amount <= 0) {
		throw runtime_error("Cannot deposit an amount of <= \x9C 0");
	}
}

/// <summary>
/// Swaps internal poiters of position a and b
/// </summary>
/// <param name="historyCopy">Vector of Transaction pointers to swap</param>
/// <param name="a">Swap position a</param>
/// <param name="b">Swap position b</param>
void swap(vector<Transaction*>& historyCopy, int a, int b) {
	Transaction* temp = historyCopy[a];
	historyCopy[a] = historyCopy[b];
	historyCopy[b] = temp;
}

/// <summary>
/// Partition method for quicksort algorithm
/// </summary>
int partition(vector<Transaction*>& historyCopy, int low, int high) {
	Transaction pivot = *historyCopy[high];

	int i = (low - 1);

	for (int j = low; j < high; j++) {
		if (*historyCopy[j] < pivot) {
			i++;
			swap(historyCopy, i, j);
		}
	}
	swap(historyCopy, i + 1, high);

	return (i + 1);
}

/// <summary>
/// Recursive Quicksort method for Quicksort algorithm
/// </summary>
void quicksort(vector<Transaction*>& historyCopy, int low, int high) {
	if (low < high) {
		int part = partition(historyCopy, low, high);

		quicksort(historyCopy, low, part - 1);
		quicksort(historyCopy, part + 1, high);
	}
}

/// <summary>
/// Creates a copy of history attribute, sorts it, then returns the copy
/// </summary>
/// <returns>Sorted copy of history</returns>
vector<Transaction*> Account::sortTransactions() {
	vector<Transaction*> historyCopy = history;
	
	int n = historyCopy.size();
	
	quicksort(historyCopy, 0, n - 1);

	return historyCopy;
}

/// <summary>
/// Implementation of Binary Search algorithm, can also return closest amount to input
/// </summary>
/// <param name="amount">Transaction amount to search for</param>
/// <returns>Transaction pointer to closet amount</returns>
Transaction* Account::findTransactionByAmount(float amount) {
	vector<Transaction*> sortedHistory = sortTransactions();

	// Initialise left and right values to start and end of vector
	int left = 0;
	int right = sortedHistory.size() - 1;

	while (left < right) {
		// Find midle of vector
		int middle = (left + right) / 2;
		// Get Value of middle item
		Transaction middleValue = *sortedHistory[middle];

		// If the middle Value is equal to amount then we have found the correct transaction
		if (middleValue == amount) {
			return sortedHistory[middle];
		}

		// If middle == 0 them vector is too small to search, return first item
		if (middle == 0) {
			return sortedHistory[0];
		}

		// Find Value directly to the left of middle
		int leftIndex = middle - 1;
		Transaction leftValue = *sortedHistory[leftIndex];

		// If search amount lies between leftand middle
		if (leftValue <= amount && middleValue >= amount) {
			// Find how far away midle and left is from search amount
			float leftDist = abs(leftValue - amount);
			float rightDist = abs(middleValue - amount);

			// If lest is closer then return left
			if (leftDist <= rightDist) {
				return sortedHistory[leftIndex];
			}
			else {
				// Otherwise return midle
				return sortedHistory[middle];
			}
		}
		// Otherwise if amount does not lie between left and middle
		// If amount is in the second half of vector
		if (middleValue <= amount) {
			// Set left to middle
			left = middle + 1;
		}
		else {
			// Otherwise set right to middle
			right = middle;
		}
	}
	// If amount is outside bounds of vector
	
	// get firt and last values of vector
	Transaction first = *sortedHistory[0];
	Transaction last = *sortedHistory[sortedHistory.size() - 1];

	// If amount is less than first then return first
	if (first >= amount) {
		return sortedHistory[0];
	}
	else if (last <= amount) {
		// If amount is greater than last return last
		return sortedHistory[sortedHistory.size() - 1];
	}
	return sortedHistory[0];
}

/// <summary>
/// Deposits valid amount into account
/// </summary>
/// <param name="amount">Amount to deposit</param>
void Account::deposit(float amount)
{
	checkValidDeposit(amount);
	balance += amount;
	history.push_back(new Transaction(TransactionType::deposit, amount));
}

/// <summary>
/// Withdraws valid amount from account
/// </summary>
/// <param name="amount">Amount to withdraw</param>
void Account::withdraw(float amount) 
{
	// Current.cpp will overide this method 
	// This ensures that the correct error checking will be performed for current accounts
	checkValidWithdrawal(amount);
	balance -= amount;
	history.push_back(new Transaction(TransactionType::withdraw, amount));
}

/// <summary>
/// Transfers a set amount between two Accounts
/// </summary>
///<param name = "from">Amount the transfer is from</param>
///<param name = "to">Amount the transfer is to</param>
///<param name = "amount">Amount to transfer</param>
void transfer(Account& from, Account& to, float amount) {
	from.checkValidWithdrawal(amount);
	from.balance -= amount;
	to.balance += amount;
	from.history.push_back(new Transaction(TransactionType::transferTo, to.getId() + 1, amount));
	to.history.push_back(new Transaction(TransactionType::transferFrom, from.getId() + 1, amount));
}

/// <summary>
/// Overrides << operator to output correctly formatted data from Account object.
/// Calls the virtual method toString that is required to be implemented on all child classes
/// </summary>
/// <param name="os">Output stream object</param>
/// <param name="a">Refefence to Account object</param>
/// <returns>Output stream object</returns>
ostream& operator<<(ostream& os, const Account& c) { return os << c.toString(); }