#define _CRT_SECURE_NO_WARNINGS
#include "Person.h"

Person::Person() {
	m_name = NULL;
	m_id = NULL;
}

Person::Person(const char* name, int id) {
	m_name = new char[strlen(name) + 1];
	strcpy(this->m_name, name);
	m_id = id;
}

Person::Person(const Person& other) {
	m_name = new char[strlen(other.GetName()) + 1];
	strcpy(m_name, other.m_name);
	m_id = other.m_id;
}

Person::~Person() {
	delete m_name;
}

void Person::SetName(const char* newName) {
	strcpy(m_name, newName);
}

void Person::SetId(int newId) {
	m_id = newId;
}

char* Person::GetName()const {
	return m_name;
}

int Person::GetId() const {
	return m_id;
}