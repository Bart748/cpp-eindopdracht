#include "Reis.h"
#include <iostream>

void Reis::createArray(size_t size) {
	travelers_ = new Reiziger[size];
}

void Reis::resizeArray(size_t size) {
	Reiziger *newArray = new Reiziger[size];
	std::copy(travelers_, travelers_ + size, newArray);
	delete[] travelers_;
	travelers_ = newArray;
}


Reis::Reis() {
	id_ = 0;
	touringCar_ = 0;
	destination_ = 0;
	date_ = 0;
	travelers_ = 0;
	amount_ = 0;
}

Reis::Reis(const Reis& other) : amount_(other.amount_), travelers_(new Reiziger[other.amount_]) {
	id_ = other.id_;
	std::copy(other.travelers_, other.travelers_ + amount_, travelers_);
}

Reis::Reis(Reis&& other) : id_(0), touringCar_(nullptr), destination_(nullptr), date_(nullptr), travelers_(nullptr), amount_(0) {
	*this = std::move(other);
}


Reis::~Reis() {
	id_ = NULL;
	delete[] travelers_;
	travelers_ = nullptr;

}

Reis& Reis::operator=(const Reis& other) {
	if (this != &other) {
		id_ = NULL;
		delete[] travelers_;
		amount_ = other.amount_;
		id_ = other.id_;
		createArray(amount_);
		std::copy(other.travelers_, other.travelers_ + amount_, travelers_);
	}
	return *this;
}

Reis& Reis::operator=(Reis&& other) {
	if (this != &other) {
		id_ = NULL;
		delete[] travelers_;
		id_ = other.id_;
		touringCar_ = other.touringCar_;
		destination_ = other.destination_;
		date_ = other.date_;
		travelers_ = other.travelers_;
		amount_ = other.amount_;

		other.id_ = 0;
		other.touringCar_ = nullptr;
		other.destination_ = nullptr;
		other.date_ = nullptr;
		other.travelers_ = nullptr;
		other.amount_ = 0;
	}
	return *this;
}

int Reis::deleteTraveler(int id) {
	unsigned i = findTraveler(id);
	Reiziger *newArray1 = 0;
	if (i != -1) {
		amount_--;
		newArray1 = new Reiziger[amount_ + 1];
		for (unsigned j = 0; j < amount_ + 1; j++) {
			newArray1[j] = travelers_[j];
		}
		for (; i < amount_; i++) {
			newArray1[i] = newArray1[i + 1];
		}
		delete[] travelers_;
		setTravelers(newArray1);
		resizeArray(amount_);
		return i;
	}
	return i;
}


int Reis::findTraveler(int id) {
	unsigned int i;
	for (i = 0; i != amount_; i++) {
		if (travelers_[i].getId() == id) {
			break;
		}
	}
	if (i == amount_) {
		return -1;
	}
	else {
		return i;
	}
}

void Reis::addTraveler(Reiziger traveler) {
	if(findTraveler(traveler.getId()) >= 0) {
		return;
	}
	else {
		amount_++;
		Reiziger *newTravelers = new Reiziger[amount_];
		for (unsigned n = 0; n < amount_ - 1; n++) {
			newTravelers[n] = travelers_[n];
		}
		delete[] travelers_;
		newTravelers[amount_ - 1] = traveler;
		travelers_ = newTravelers;
	}
	
}

void Reis::modifyTravelerName(std::string name, int id) {
	int index = findTraveler(id);
	if(index > -1) {
		travelers_[index].SetName(name);
	}
}

void Reis::modifyTravelerAddress(std::string address, int id) {
	int index = findTraveler(id);
	if(index > -1) {
		travelers_[index].SetAddress(address);
	}
}

void Reis::modifyTravelerCity(std::string city, int id) {
	int index = findTraveler(id);
	if(index > -1) {
		travelers_[index].SetCity(city);
	}
}


unsigned int & Reis::getId() {
	return this->id_;
}

void Reis::setId(unsigned int id) {
	this->id_ = id;
}

char * Reis::getTouringCar() {
	return this->touringCar_;
}

void Reis::setTouringCar(std::string touringCar) {
	delete[] this->touringCar_;
	this->touringCar_ = new char[touringCar.size() + 1];
	std::copy(touringCar.begin(), touringCar.end(), this->touringCar_);
	this->touringCar_[touringCar.size()] = '\0';
}

char * Reis::getDestination() {
	return this->destination_;
}

void Reis::setDestination(std::string destination) {
	delete[] this->destination_;
	this->destination_ = new char[destination.size() + 1];
	std::copy(destination.begin(), destination.end(), this->destination_);
	this->destination_[destination.size()] = '\0';
}

char * Reis::getDate() {
	return this->date_;
}

void Reis::setDate(std::string date) {
	delete[] this->date_;
	this->date_ = new char[date.size() + 1];
	std::copy(date.begin(), date.end(), this->date_);
	this->date_[date.size()] = '\0';
}

Reiziger* Reis::getTravelers() {
	return this->travelers_;
}


void Reis::setTravelers(Reiziger * traveler) {
	travelers_ = traveler;
}

unsigned int Reis::getAmount() {
	return amount_;
}

void Reis::setAmount(unsigned int amount) {
	amount_ = amount;
}
