#include "Account.h"

using namespace std;

Account::Account(int accountId) {
	balance = 0;
	id = accountId;
}

int Account::getId() const{
	return id;
}

void swap(vector<Transaction*>& historyCopy, int a, int b) {
	Transaction* temp = historyCopy[a];
	historyCopy[a] = historyCopy[b];
	historyCopy[b] = temp;
}

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

void quicksort(vector<Transaction*>& historyCopy, int low, int high) {
	if (low < high) {
		int part = partition(historyCopy, low, high);

		quicksort(historyCopy, low, part - 1);
		quicksort(historyCopy, part + 1, high);
	}
}

vector<Transaction*> Account::sortTransactions() {
	vector<Transaction*> historyCopy = history;
	
	int n = historyCopy.size();
	
	quicksort(historyCopy, 0, n - 1);

	return historyCopy;
}

void Account::transferTo(Account* to, float amount) {
	if (amount > balance) throw invalid_argument("Cannot transfer more than account balance");
	balance -= amount;
	history.push_back(new Transaction(TransactionType::transferTo, to->getId(), amount));
	to->transferFrom(this, amount);
}

void Account::transferFrom(Account* from, float amount) {
	balance += amount;
	history.push_back(new Transaction(TransactionType::transferFrom, from->getId(), amount));
}

ostream& operator<<(ostream& os, const Account& c) { return os << c.toString(); }