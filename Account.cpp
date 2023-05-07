#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"

Account::Account() {
	m_transactionList = NULL;
	m_numberOfTransaction = NULL;
	m_persons = NULL;
	m_totalPersons = NULL;
	m_accountNumber = NULL;
	m_balance = NULL;
}

Account::Account(Person** persons, int count/*number of persons*/, double balance) {
	m_totalPersons = count;
	m_balance = balance;
	m_persons = new Person*[m_totalPersons];
	m_transactionList = NULL;
	m_numberOfTransaction = NULL;
	for (int i = 0; i < count; i++) {
		m_persons[i] = new Person(*(persons[i]));
	}
	m_accountNumber = m_persons[0]->GetId();
}

Account::Account(const Person& person, double balance) {
	m_totalPersons = 1;
	m_balance = balance;
	m_persons = new Person*;
	m_persons[0] = new Person(person);
	m_transactionList = NULL;
	m_numberOfTransaction = NULL;
	m_accountNumber = m_persons[0]->GetId();
}

Account::Account(const Account& other) {
	m_totalPersons = other.m_totalPersons;
	m_balance = other.m_balance;
	m_numberOfTransaction = other.m_numberOfTransaction;
	m_persons = new Person*[m_totalPersons];
	for (int i = 0; i < m_totalPersons; i++) {
		m_persons[i] = new Person(*(other.m_persons[i]));
	}
	m_transactionList = new Transaction*[m_numberOfTransaction];
	for (int i = 0; i < m_numberOfTransaction; i++) {
		m_transactionList[i] = new Transaction(*(other.m_transactionList[i]));
	}
	m_accountNumber = other.m_accountNumber;
}

Account::~Account() {
	for (int i = 0; i < m_numberOfTransaction; i++) {
		delete m_transactionList[i];
	}
	delete[] m_transactionList;
	for (int i = 0; i < m_totalPersons; i++) {
		delete m_persons[i];
	}
}

void Account::SetPersons(Person** persons, int count) {
	m_totalPersons = count;
	m_persons = new Person * [m_totalPersons];
	for (int i = 0; i < m_totalPersons; i++) {
		m_persons[i] = new Person(*(persons[i]));
	}
}

void Account::SetAccountNumber(int number) {
	m_accountNumber = number;
}

void Account::SetBalance(double balance) {
	m_balance = balance;
}

void Account::SetTransactions(Transaction** newTransaction, int count) {
	m_numberOfTransaction = count;
	m_transactionList = new Transaction * [m_numberOfTransaction];
	for (int i = 0; i < m_numberOfTransaction; i++) {
		m_transactionList[i] = new Transaction(*(newTransaction[i]));
	}
}

Transaction** Account::GetTransactions() {
	return m_transactionList;
}

int	Account::GetNumOfTransactions() {
	return m_numberOfTransaction;
}

Person** Account::GetPersons() const {
	return m_persons;
}

int	Account::GetTotalPersons()const {
	return m_totalPersons;
}

int Account::GetAccountNumber() const {
	return m_accountNumber;
}

double Account::GetBalance() const {
	return m_balance;
}

void Account::Withdraw(double amount, const char* date) {
	m_balance -= amount;
	m_numberOfTransaction += 1;
	Transaction** tempTran = new Transaction * [m_numberOfTransaction];

	for (int i = 0; i < m_numberOfTransaction - 1; i++) {
		tempTran[i] = new Transaction(*(m_transactionList[i]));
	}
	tempTran[m_numberOfTransaction - 1] = new Transaction(this, this, amount, date);

	m_transactionList = new Transaction * [m_numberOfTransaction];
	for (int i = 0; i < m_numberOfTransaction; i++) {
		m_transactionList[i] = new Transaction(*(tempTran[i]));
	}
	
	for (int i = 0; i < m_numberOfTransaction; i++) {
		delete tempTran[i];
	}
	delete[] tempTran;
}


void Account::Deposit(double amount, const char* date) {
	m_balance += amount;
	m_numberOfTransaction += 1;
	Transaction** tempTran = new Transaction * [m_numberOfTransaction];

	for (int i = 0; i < m_numberOfTransaction - 1; i++) {
		tempTran[i] = new Transaction(*(m_transactionList[i]));
	}
	tempTran[m_numberOfTransaction - 1] = new Transaction(this, this, amount, date);

	m_transactionList = new Transaction * [m_numberOfTransaction];
	for (int i = 0; i < m_numberOfTransaction; i++) {
		m_transactionList[i] = new Transaction(*(tempTran[i]));
	}

	for (int i = 0; i < m_numberOfTransaction; i++) {
		delete tempTran[i];
	}
	delete[] tempTran;
}

void Account::AddPerson(const Person& newPerson, double	amount) {
	for (int i = 0; i < m_numberOfTransaction; i++) {
		if (strcmp(m_persons[i]->GetName(), newPerson.GetName()) == 0) {
			return;
		}
	}
	m_totalPersons += 1;
	m_balance += amount;
	Person** tempPer = new Person * [m_totalPersons];

	for (int i = 0; i < m_totalPersons-1; i++) {
		tempPer[i] = new Person(*(m_persons[i]));
	}
	tempPer[m_totalPersons - 1] = new Person(newPerson);

	m_persons = new Person * [m_totalPersons];
	for (int i = 0; i < m_totalPersons; i++) {
		m_persons[i] = new Person(*(tempPer[i]));
	}

	for (int i = 0; i < m_totalPersons; i++) {
		delete tempPer[i];
	}
	delete[] tempPer;
}

void Account::DeletePerson(const Person& oldPerson) {
	for (int i = 0; i < m_totalPersons; i++) {
		if (strcmp(m_persons[i]->GetName(), oldPerson.GetName()) == 0) {
			if (m_totalPersons == 1) {
				m_totalPersons = 0;
				delete m_persons[0];
				delete[] m_persons;
			}
			else {
				m_totalPersons -= 1;
				delete m_persons[i];
			}
		}
	}
}

void Account::AddTransaction(const Transaction& newTransaction) {
	if ((newTransaction.GetSource()->m_accountNumber == this->m_accountNumber) && (newTransaction.GetDes()->m_accountNumber == this->m_accountNumber)) {
		return;
	}

	newTransaction.GetSource()->m_numberOfTransaction += 1;
	int size = newTransaction.GetSource()->m_numberOfTransaction;
	Transaction** temp = new Transaction * [size];
	for (int i = 0; i < size - 1; i++) {
		temp[i] = new Transaction(*(newTransaction.GetSource()->m_transactionList[i]));
	}
	temp[size - 1] = new Transaction(newTransaction);
	newTransaction.GetSource()->m_transactionList = new Transaction*[size];
	for (int i = 0; i < size; i++) {
		newTransaction.GetSource()->m_transactionList[i] = new Transaction(*temp[i]);
	}
	

	newTransaction.GetDes()->m_numberOfTransaction += 1;
	int size2 = newTransaction.GetDes()->m_numberOfTransaction;
	Transaction** temp2 = new Transaction * [size2];
	for (int i = 0; i < size2 - 1; i++) {
		temp2[i] = new Transaction(*(newTransaction.GetDes()->m_transactionList[i]));
	}
	temp2[size2 - 1] = new Transaction(newTransaction);
	newTransaction.GetDes()->m_transactionList = new Transaction * [size2];
	for (int i = 0; i < size2; i++) {
		newTransaction.GetDes()->m_transactionList[i] = new Transaction(*temp2[i]);
	}

	newTransaction.GetSource()->m_balance -= newTransaction.GetAmount();
	newTransaction.GetDes()->m_balance += newTransaction.GetAmount();
}

void Account::clearTransactions() {
	for (int i = 0; i < m_numberOfTransaction; i++) {
		delete m_transactionList[i];
	}
	delete[] m_transactionList;
	m_numberOfTransaction = 0;
}

void Account::clearPersons() {
	for (int i = 0; i < m_totalPersons; i++) {
		m_persons[i]->~Person();
		delete m_persons[i];
	}
	delete[] m_persons;
	m_totalPersons = 0;
}