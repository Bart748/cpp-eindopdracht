#include "Reiziger.h"

Reiziger::Reiziger() {
	id_ = 0;
	name_ = 0;
	address_ = 0;
	city_ = 0;
	
}

Reiziger::Reiziger(const Reiziger& other) : id_(other.id_){
	name_ = _strdup(other.name_);
	address_ = _strdup(other.address_);
	city_ = _strdup(other.city_);
}

Reiziger::Reiziger(Reiziger&& other) : name_(nullptr), id_(0), address_(nullptr), city_(nullptr) {
	*this = std::move(other);
}


Reiziger::~Reiziger() {
	delete[] name_;
	name_ = NULL;
}


Reiziger& Reiziger::operator=(const Reiziger& other) {
	if (this != &other) {
		delete[] name_;
		name_ = _strdup(other.name_);
		id_ = other.id_;
		address_ = _strdup(other.address_);
		city_ = _strdup(other.city_);
	}
	return *this;
}

Reiziger& Reiziger::operator=(Reiziger&& other) {
	if (this != &other) {
		delete[] name_;
		name_ = _strdup(other.name_);
		id_ = other.id_;
		address_ = _strdup(other.address_);
		city_ = _strdup(other.city_);
		other.name_ = nullptr;
		other.id_ = 0;
		other.address_ = nullptr;
		other.city_ = nullptr;
	}
	return *this;
}

unsigned int & Reiziger::getId() {
	return this->id_;
}

void Reiziger::SetId(unsigned int id) {
	this->id_ = id;
}

char * Reiziger::GetName() {
	return this->name_;
}

void Reiziger::SetName(std::string name) {
	delete[] this->name_;
	this->name_ = new char[name.size() + 1];
	std::copy(name.begin(), name.end(), this->name_);
	this->name_[name.size()] = '\0';

}

char * Reiziger::getAddress() {
	return this->address_;
}

void Reiziger::SetAddress(std::string address) {
	delete[] this->address_;
	this->address_ = new char[address.size() + 1];
	std::copy(address.begin(), address.end(), this->address_);
	this->address_[address.size()] = '\0';
}

char * Reiziger::getCity() {
	return this->city_;
}

void Reiziger::SetCity(std::string city) {
	delete[] this->city_;
	this->city_ = new char[city.size() + 1];
	std::copy(city.begin(), city.end(), this->city_);
	this->city_[city.size()] = '\0';
}

