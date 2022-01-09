#include "Account.h"

using namespace std;

Account::Account(int accountId) {
	balance = 0;
	id = accountId;
}

int Account::getId() const{
	return id;
}

void swap(Transaction* a, Transaction* b) {
	Transaction temp = *a;
	*a = *b;
	*b = temp;
}

int partition(vector<Transaction> history,int low, int high) {
	Transaction pivot = history[high];

	int i = (low - 1);

	for (int j = low; j < high; j++) {
		if (history[j] <= pivot) {
			i++;
			swap(&history[i], &history[j]);
		}
	}

	swap(&history[i + 1], &history[high]);

	return (i + 1);
}

void quicksort(vector<Transaction> history, int low, int high) {
	if (low < high) {
		int part = partition(history, low, high);

		quicksort(history, low, part - 1);
		quicksort(history, part + 1, high);
	}
}

vector<Transaction> Account::sortTransactions() {
	vector<Transaction> historyCopy = history;
	
	int n = historyCopy.size();
	
	quicksort(historyCopy, 0, n - 1);

	return historyCopy;
}

void Account::transferTo(Account* to, float amount) {
	if (amount > balance) throw invalid_argument("Cannot transfer more than account balance");
	balance -= amount;
	history.push_back(Transaction(TransactionType::transferTo, to->getId(), amount));
	to->transferFrom(this, amount);
}

void Account::transferFrom(Account* from, float amount) {
	balance += amount;
	history.push_back(Transaction(TransactionType::transferFrom, from->getId(), amount));
}

ostream& operator<<(ostream& os, const Account& c) { return os << c.toString(); }