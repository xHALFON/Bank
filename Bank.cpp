#define _CRT_SECURE_NO_WARNINGS
#include "Bank.h"

Bank::Bank() {
	m_name = NULL;
	m_account = NULL;
	m_bankCode = NULL;
	m_numbeOfAccounts = NULL;
	m_totalBalance = NULL;
}

Bank::Bank(const char* name, int code) {
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);
	m_account = NULL;
	m_numbeOfAccounts = NULL;
	m_totalBalance = NULL;
	m_bankCode = code;
}

Bank::~Bank() {
	delete[] m_name;
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		delete m_account[i];
	}
	delete[] m_account;
}

void Bank::SetBankName(const char* name) {
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);
}
void Bank::SetAccount(Account** account, int numbeOfAccounts) {
	m_numbeOfAccounts = numbeOfAccounts;
	m_account = new Account * [numbeOfAccounts];

	for (int i = 0; i < m_numbeOfAccounts; i++) {
		m_account[i] = new Account(*(account[i]));
	}
}
void Bank::SetTotal(double total) {
	m_totalBalance = total;
}

void Bank::SetCode(int code) {
	m_bankCode = code;
}

const char* Bank::GetBankName() const {
	return m_name;
}

Account** Bank::GetAccounts() const {
	return m_account;
}

int Bank::GetNumberOfAccounts() const {
	return m_numbeOfAccounts;
}

double Bank::GetTotal() const {
	return m_totalBalance;
}

int	Bank::GetCode() const {
	return m_bankCode;
}

void Bank::AddAccount(const Account& account) {
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
			return;
		}
	}
	if (m_numbeOfAccounts == 0) {
		m_numbeOfAccounts += 1;
		m_account = new Account*;
		m_account[0] = new Account(account);
		m_totalBalance += account.GetBalance();
		return;
	}
	m_numbeOfAccounts += 1;
	Account** tempAccList = new Account * [m_numbeOfAccounts];
	for (int i = 0; i < m_numbeOfAccounts - 1; i++) {
		tempAccList[i] = new Account(*(m_account[i]));
	}
	tempAccList[m_numbeOfAccounts - 1] = new Account(account);
	
	m_account = new Account * [m_numbeOfAccounts];
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		m_account[i] = new Account(*(tempAccList[i]));
	}
	m_totalBalance += account.GetBalance();
}

void Bank::AddAccount(const Person& per, double amount) {
	m_numbeOfAccounts += 1;
	Account** tempAccList = new Account * [m_numbeOfAccounts];
	for (int i = 0; i < m_numbeOfAccounts - 1; i++) {
		tempAccList[i] = new Account(*(m_account[i]));
	}
	tempAccList[m_numbeOfAccounts - 1] = new Account(per,amount);
	m_account = new Account * [m_numbeOfAccounts];
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		m_account[i] = new Account(*(tempAccList[i]));
	}
	m_totalBalance += m_account[m_numbeOfAccounts - 1]->GetBalance();
}

void Bank::AddPerson(const Person& newPerson, const Account& account, double amount) {
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
			for (int j = 0; j < m_account[i]->GetTotalPersons(); j++) {
				if (strcmp(m_account[i]->GetPersons()[j]->GetName(), newPerson.GetName()) == 0) {
					return;
				}
			}
			m_account[i]->AddPerson(newPerson, amount);
			return;
		}
	}

	AddAccount(newPerson, amount);
}

void Bank::DeleteAccount(const Account& account) {
	m_totalBalance -= account.GetBalance();
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
			for (int j = 0; j < m_account[i]->GetTotalPersons(); j++) {
				delete m_account[i]->GetPersons()[j];
			}
			if (m_numbeOfAccounts == 1) {
				delete[] m_account;
			}
		}
	}
	m_numbeOfAccounts -= 1;
}
void Bank::DeletePerson(const Person& p) {
	for (int i = 0; i < m_numbeOfAccounts; i++) {
		for (int j = 0; j < m_account[i]->GetTotalPersons(); j++) {
			if (m_account[i]->GetPersons()[j]->GetId() == p.GetId()) {
				m_account[i]->DeletePerson(p);
				m_totalBalance -= m_account[i]->GetBalance();
				if (m_account[i]->GetTotalPersons() == 0) {
					DeleteAccount(*m_account[i]);
				}
			}
		}
	}
}