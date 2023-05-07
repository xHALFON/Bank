#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"

Transaction::Transaction(Account* s, Account* d, double amount, const char* date) {
	m_amount = amount;
	m_date = new char[strlen(date) + 1];
	strcpy(m_date, date);
	m_source = s;
	m_destination = d;
}
Transaction::Transaction(const Transaction& other) {
	m_date = new char[strlen(other.GetDate()) + 1];
	strcpy(m_date, other.m_date);
	m_amount = other.m_amount;
	m_destination = other.m_destination;
	m_source = other.m_source;
}

void Transaction::SetSource(Account* src) {
	m_source = src;
}

void Transaction::SetDes(Account* dst) {
	m_destination = dst;
}

void Transaction::SetAmount(double amount) {
	m_amount = amount;
}

void Transaction::SetDate(const char* date) {
	strcpy(m_date, date);
}

Account* Transaction::GetSource() const {
	return m_source;
}

Account* Transaction::GetDes() const {
	return m_destination;
}

double Transaction::GetAmount() const {
	return m_amount;
}

char* Transaction::GetDate() const {
	return m_date;
}