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

//Should these be private methods or leave as functions?
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

Transaction* Account::findTransactionByAmount(float amount) {
	vector<Transaction*> sortedHistory = sortTransactions();

	int left = 0;
	int right = sortedHistory.size() - 1;

	while (left < right) {
		int middle = (left + right) / 2;
		Transaction middleValue = *sortedHistory[middle];

		if (middleValue == amount) {
			return sortedHistory[middle];
		}

		if (middle == 0) {
			return sortedHistory[0];
		}

		int leftIndex = middle - 1;
		Transaction leftValue = *sortedHistory[leftIndex];

		if (leftValue <= amount && middleValue >= amount) {
			int leftDist = abs(leftValue - amount);
			int rightDist = abs(middleValue - amount);

			if (leftDist <= rightDist) {
				return sortedHistory[leftIndex];
			}
			else {
				 return sortedHistory[middle];
			}
		}

		if (middleValue <= amount) {
			left = middle + 1;
		}
		else {
			right = middle;
		}
	}

	Transaction first = *sortedHistory[0];
	Transaction last = *sortedHistory[sortedHistory.size() - 1];

	if (first >= amount) {
		return sortedHistory[0];
	}
	else if (last <= amount) {
		return sortedHistory[sortedHistory.size() - 1];
	}
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