#include "Filemanager.h"
#include <fstream>
#include <algorithm>
#include <regex>
#include <iostream>



Filemanager::Filemanager(std::string travelerpath, std::string trippath) {
	readTravelerFile(travelerpath);
	//readTripFile(trippath);
	amount_travelers_ = 0;
	amount_trips_ = 0;
	trips_ = 0;
	travelers_ = 0;
}

Filemanager::Filemanager(const Filemanager& other) : amount_trips_(other.amount_trips_), amount_travelers_(other.amount_travelers_), trips_(new Reis[other.amount_trips_]), travelers_(new Reiziger[other.amount_travelers_]) {
	std::copy(other.travelers_, other.travelers_ + amount_travelers_, travelers_);
	std::copy(other.trips_, other.trips_ + amount_trips_, trips_);
}

Filemanager::Filemanager(Filemanager&& other) : amount_trips_(0), amount_travelers_(0), trips_(nullptr), travelers_(nullptr) {
	*this = std::move(other);
}

Filemanager& Filemanager::operator=(const Filemanager &other) {
	if (this != &other) {
		delete[] travelers_;
		delete[] trips_;
		amount_trips_ = other.amount_trips_;
		amount_travelers_ = other.amount_travelers_;
		travelers_ = new Reiziger[amount_travelers_];
		trips_ = new Reis[amount_trips_];
		std::copy(other.travelers_, other.travelers_ + amount_travelers_, travelers_);
		std::copy(other.trips_, other.trips_ + amount_trips_, trips_);
	}
	return *this;
}

Filemanager& Filemanager::operator=(Filemanager &&other) {
	if (this != &other) {
		delete[] travelers_;
		delete[] trips_;
		travelers_ = other.travelers_;
		trips_ = other.trips_;
		amount_trips_ = other.amount_trips_;
		amount_travelers_ = other.amount_travelers_;
		other.amount_trips_ = 0;
		other.amount_travelers_ = 0;
		other.travelers_ = nullptr;
		other.trips_ = nullptr;
	}
	return *this;
}

int Filemanager::findIndex(int id, int sw) {
	unsigned int i;
	for (i = 0; i != amount_travelers_; i++) {
		if (travelers_[i].getId() == id) {
			break;
		}
	}
	if (i == amount_travelers_) {
		return -1;
	}
	else {
		if (sw) {
			printTraveler(i);
			return i;
		}
		else
			return i;
	}
}

void Filemanager::findName(std::string name) {
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	unsigned i = 0;
	bool found = false;
	for (; i != amount_travelers_; i++) {
		std::string tmp = travelers_[i].GetName();
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		if (tmp.find(name) != std::string::npos) {
			printTraveler(i);
			found = true;
		}
	}
	if (!found) {
		std::cout << " Name not found!" << std::endl;
	}
}

void Filemanager::findAddress(std::string address) {
	std::transform(address.begin(), address.end(), address.begin(), ::tolower);
	unsigned i = 0;
	bool found = false;
	for (; i != amount_travelers_; i++) {
		std::string tmp = travelers_[i].getAddress();
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		if (tmp.find(address) != std::string::npos) {
			printTraveler(i);
			found = true;
		}
	}
	if (!found) {
		std::cout << " Name not found!" << std::endl;
	}
}

void Filemanager::findCity(std::string city) {
	std::transform(city.begin(), city.end(), city.begin(), ::tolower);
	unsigned i = 0;
	bool found = false;
	for (; i != amount_travelers_; i++) {
		std::string tmp = travelers_[i].getCity();
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		if (tmp.find(city) != std::string::npos) {
			printTraveler(i);
			found = true;
		}
	}
	if (!found) {
		std::cout << " Name not found!" << std::endl;
	}
}

void Filemanager::printTraveler(unsigned index) {
	if (index > amount_travelers_ - 1 || index < 0) {
		index = 0;
	}
	std::cout << "ID: " << travelers_[index].getId() << "\nName: " << travelers_[index].GetName() << "\nAddress: " << travelers_[index].getAddress() << "\nCity: " << travelers_[index].getCity() << std::endl;
}

void Filemanager::findTraveler() {
	std::string input;
	std::cout << "Search for name: (N); Search for Address (A); Search for City (C); Seach for ID (I); Exit (X)" << std::endl;
	std::getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	if (input == "N") {
		std::cout << "Enter name or part of the nameyou would like to search for: " << std::endl;
		std::getline(std::cin, input);
		findName(input);
	}
	else if (input == "A") {
		std::cout << "Enter the address (or part of the address)" << std::endl;
		std::getline(std::cin, input);
		findAddress(input);
	}
	else if (input == "C") {
		std::cout << "Enter the City (or part of the city name)" << std::endl;
		std::getline(std::cin, input);
		findCity(input);
	}
	else if (input == "I") {
		std::cout << "Enter the ID you would like to search for: " << std::endl;
		std::getline(std::cin, input);
		try {
			unsigned parse = std::stoi(input);
			if (parse > travelers_[amount_travelers_ - 1].getId() || parse < 1) {
				throw - 1;
			}
			else
				findIndex(parse, 1);
		}
		catch (...) {
			std::cout << "Enter a valid number" << std::endl;
		}
	}
	else if (input == "X") {
		return;
	}
	else {
		std::cout << "Enter one of the given options" << std::endl;
		return findTraveler();
	}
}

void Filemanager::editTrip() {
	Reiziger *newArray1 = 0;
	unsigned int index;
	unsigned int newSize;
	std::string input;
	bool valid = false;
	printTrips();
	std::cout << "Enter the number of the group you would like to edit" << std::endl;
	std::getline(std::cin, input);
	try {
		unsigned parse = std::stoi(input);
		if (parse >= amount_trips_ || parse < 0) {
			valid = false;
		}
		else {
			valid = true;
		}
	}
	catch (...) {
		std::cout << "Please type a number" << std::endl;
		return editTrip();
	}
	if (valid) {
		index = std::stoi(input);
		std::cout << "Now editing group" << trips_[index].getId() << std::endl;
		newSize = trips_[index].getAmount();
		std::cout << "Delete a Traveler: (D); Add a traveler: (A); Change Destination (C), Change Date: (N), Change TouringCar: (T); Exit: (X)" << std::endl;
		std::getline(std::cin, input);
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input == "D") {
			try {
				newSize--;
				std::cout << "Enter the ID of the Traveler you would like to delete" << std::endl;
				std::getline(std::cin, input);
				unsigned parse = std::stoi(input);
				if (parse > travelers_[amount_travelers_ - 1].getId() || parse < 0) {
					std::cout << "Enter a valid number" << std::endl;
					return editTrip();
				}
				else {
					unsigned int deleted = trips_[index].deleteTraveler(parse);
					if (deleted != -1) {
						std::cout << "Deleted Traveler: " << std::endl;
						findIndex(deleted, 1);
						std::cout << std::endl;
					}
				}
			}
			catch (...) {
				std::cout << "Please enter a number" << std::endl;
				return editTrip();
			}
		}
		else if (input == "A") {
			std::string num = "st";
			std::cout << "Enter the amount of travelers you would like to add" << std::endl;
			std::getline(std::cin, input);
			try {
				newSize += std::stoi(input);
				unsigned int oldSize = trips_[index].getAmount();
				unsigned int nr;
				for (unsigned int k = oldSize; k < (unsigned)newSize; k++) {
					nr = (k - (oldSize - 1));
					if (nr == 1 || ((nr % 10) == 1 && nr != 11)) {
						num = "st";
					}
					else if (nr == 2 || ((nr % 10) == 2) && nr != 12) {
						num = "nd";
					}
					else if (nr == 3 || ((nr % 10) == 3) && nr != 13) {
						num = "rd";
					}
					else {
						num = "th";
					}
					if (std::stoi(input) > 1) {
						std::cout << "Enter the ID of the " << nr << num << " Traveler you would like to add" << std::endl;
					}
					else {
						std::cout << "Enter the ID of the Traveler you would like to add" << std::endl;
					}
					getline(std::cin, input);
					unsigned parse = std::stoi(input);
					if (parse > travelers_[amount_travelers_ - 1].getId() || parse < 0) {
						std::cout << "enter a valid ID!" << std::endl;
						return editTrip();
					}
					else {
						int a = findIndex(parse, 0);
						trips_[index].addTraveler(travelers_[a]);
					}
				}
			}
			catch (...) {
				std::cout << "Please enter a number" << std::endl;
				return editTrip();
			}

		}
		else if (input == "C") { // destination
			std::cout << "Enter new destination" << std::endl;
			std::getline(std::cin, input);
			bool contains_non_alpha = std::regex_match(input, std::regex("^[A-Za-z][A-Za-z0-9]*(?:_?-?/?[A-Za-z0-9]+)*$"));
			if (!contains_non_alpha) {
				std::cout << "Please note that the Destination has to start with a letter and end with a letter or number, and only allows underscores as special characters." << std::endl;
				std::cout << "Press enter to continue" << std::endl;
				std::cin.get();
				return editTrip();
			}
			else
				trips_[index].setDestination(input);
		}
		else if (input == "N") { // date
			std::cout << "Enter new date" << std::endl;
			std::getline(std::cin, input);
			bool contains_non_alpha = std::regex_match(input, std::regex("^[A-Za-z][A-Za-z0-9]*(?:_?-?/?[A-Za-z0-9]+)*$"));
			if (!contains_non_alpha) {
				std::cout << "Please note that the Date has to start with a letter and end with a letter or number, and only allows underscores as special characters." << std::endl;
				std::cout << "Press enter to continue" << std::endl;
				std::cin.get();
				return editTrip();
			}
			else
				trips_[index].setDate(input);
		}
		else if (input == "T") { // touringcar
			std::cout << "Enter new Touringcar name" << std::endl;
			std::getline(std::cin, input);
			bool contains_non_alpha = std::regex_match(input, std::regex("^[A-Za-z][A-Za-z0-9]*(?:_?-?/?[A-Za-z0-9]+)*$"));
			if (!contains_non_alpha) {
				std::cout << "Please note that the Tourincar name has to start with a letter and end with a letter or number, and only allows underscores as special characters." << std::endl;
				std::cout << "Press enter to continue" << std::endl;
				std::cin.get();
				return editTrip();
			}
			else
				trips_[index].setTouringCar(input);
		}
		else if (input == "X") { // exit
			return;
		}
		else {
			std::cout << "Enter something that is given on the list. Press enter to continue" << std::endl;
			std::cin.get();
			return editTrip();
		}
	}
	else {
		std::cout << "The group you entered doesn't exist. Please try again." << std::endl;
		return editTrip();
	}
}

void Filemanager::addTraveler() {
	std::string input;
	std::string num;
	Reiziger *newArray = 0;
	unsigned oldSize = amount_travelers_;
	std::cout << "Enter the amount of travelers you want to add" << std::endl;
	getline(std::cin, input);
	try {
		unsigned parse = std::stoi(input);
		unsigned newSize = oldSize;
		newSize += parse; //no need to set amount because amount is incremented in groups->addMember
		unsigned nr;
		for (unsigned k = oldSize; k < newSize; k++) {
			nr = (k - (oldSize - 1));
			if (nr == 1 || ((nr % 10) == 1 && nr != 11)) {
				num = "st";
			}
			else if (nr == 2 || ((nr % 10) == 2) && nr != 12) {
				num = "nd";
			}
			else if (nr == 3 || ((nr % 10) == 3) && nr != 13) {
				num = "rd";
			}
			else {
				num = "th";
			}
			amount_travelers_++;
			try {
				newArray = new Reiziger[amount_travelers_];
				if (parse > 1) {
					std::cout << "Enter the name of the " << nr << num << " traveler you would like to add" << std::endl;
					getline(std::cin, input);
					newArray[amount_travelers_ - 1].SetName(input);
					std::cout << "Enter the address of the " << nr << num << " new traveler: " << std::endl;
					getline(std::cin, input);
					newArray[amount_travelers_ - 1].SetAddress(input);
					std::cout << "Enter the city of the " << nr << num << " new traveler: " << std::endl;
					getline(std::cin, input);
					newArray[amount_travelers_ - 1].SetCity(input);

				}
				else {
					std::cout << "Enter the name of your new traveler: " << std::endl;
					getline(std::cin, input);
					newArray[amount_travelers_ - 1].SetName(input);
					std::cout << "Enter the address of your new traveler: " << std::endl;
					getline(std::cin, input);
					newArray[amount_travelers_ - 1].SetAddress(input);
					std::cout << "Enter the city of your new traveler: " << std::endl;
					getline(std::cin, input);
					newArray[amount_travelers_ - 1].SetCity(input);
				}
			}
			catch (...) {
				std::cout << "Please enter the correct input" << std::endl;
				std::cin.get();
				return editTrip();
			}
			newArray[amount_travelers_ - 1].SetId(amount_travelers_);
			for (unsigned int i = 0; i < amount_travelers_ - 1; i++) {
				newArray[i] = travelers_[i];
			}
			//delete[] travelers_;
			travelers_ = newArray;
		}
	}
	catch (...) {
		std::cout << "Please enter a number!" << std::endl;
		return;
	}
}

void Filemanager::removeTraveler() {
	std::string input;
	std::cout << "Enter the ID of the member you would like to delete" << std::endl;
	getline(std::cin, input);
	try {
		unsigned parse = std::stoi(input);
		if (parse > travelers_[amount_travelers_ - 1].getId() || parse < 0) {
			std::cout << "Please enter a valid ID!" << std::endl;
		}
		else {
			unsigned i = findIndex(parse, 0);
			if (i != -1) {
				int deleted = 0;
				for (unsigned n = 0; n < amount_trips_; n++) {
					deleted = trips_[n].deleteTraveler(parse);
					if (deleted > 0) {
						std::cout << "deleted traveler from trip(s): " << trips_[n].getId() << "\t" << trips_[n].getDestination() << "\t" << trips_[n].getDate() << std::endl;
					}
				}
				Reiziger *newTravelers = new Reiziger[amount_travelers_];
				amount_travelers_--;
				for (unsigned j = 0; j < amount_travelers_ + 1; j++) {
					newTravelers[j] = travelers_[j];
				}

				for (; i < amount_travelers_; i++) {
					newTravelers[i] = newTravelers[i + 1];
				}
				delete[] this->travelers_;
				travelers_ = newTravelers;
			}
			else {
				std::cout << "Somehow ID is invalid, contact me!" << std::endl;
			}
		}
	}
	catch (...) {
		std::cout << "Please enter a number!" << std::endl;
	}
}

void Filemanager::modifyTraveler() {
	std::string input;
	std::cout << "Enter the ID of the traveler you would like to modify" << std::endl;
	std::getline(std::cin, input);
	try {
		unsigned parse = std::stoi(input);
		if (parse > travelers_[amount_travelers_ - 1].getId() || parse < 1) {
			std::cout << "Please enter a valid ID" << std::endl;
		}
		else {
			std::cout << "Now editing traveler: " << std::endl;
			int found = findIndex(parse, 1);
			if (found != -1) {
				std::cout << "Modify Name (N); Modify Address (A); Modify City (C)" << std::endl;
				std::getline(std::cin, input);
				std::transform(input.begin(), input.end(), input.begin(), ::toupper);
				if (input == "N") {
					std::cout << "Enter the new name for " << travelers_[found].GetName() << std::endl;
					std::getline(std::cin, input);
					travelers_[found].SetName(input);
					for (unsigned g = 0; g < amount_trips_; g++) {
						trips_[g].modifyTravelerName(input, travelers_[found].getId());
					}
				}
				else if (input == "A") {
					std::cout << "Enter the new address for " << travelers_[found].GetName() << std::endl;
					std::getline(std::cin, input);
					travelers_[found].SetAddress(input);
					for (unsigned g = 0; g < amount_trips_; g++) {
						trips_[g].modifyTravelerAddress(input, travelers_[found].getId());
					}
				}
				else if (input == "C") {
					std::cout << "Enter the new City for " << travelers_[found].GetName() << std::endl;
					std::getline(std::cin, input);
					travelers_[found].SetCity(input);
					for (unsigned g = 0; g < amount_trips_; g++) {
						trips_[g].modifyTravelerCity(input, travelers_[found].getId());
					}
				}
				else {
					std::cout << "Please enter valid input" << std::endl;
				}
			}
		}
	}
	catch (...) {
		std::cout << "Please enter an ID (Number)";
		return modifyTraveler();
	}
}

void Filemanager::addTrip() {
	std::string input;
	amount_trips_++;
	Reis *newTrips = new Reis[amount_trips_];
	for (unsigned m = 0; m < amount_trips_ - 1; m++) {
		newTrips[m] = trips_[m];
	}
	newTrips[amount_trips_ - 1].setId(amount_trips_ - 1);
	std::cout << "Enter a destination for the new trip: " << std::endl;
	std::getline(std::cin, input);
	newTrips[amount_trips_ - 1].setDestination(input);
	std::cout << "Enter a date for the new trip: " << std::endl;
	std::getline(std::cin, input);
	newTrips[amount_trips_ - 1].setDate(input);
	std::cout << "Enter a touring care for the new trip: " << std::endl;
	std::getline(std::cin, input);
che	newTrips[amount_trips_ - 1].setTouringCar(input);
	std::cout << newTrips[amount_trips_ - 1].getId() << " New trip added: " << newTrips[amount_trips_ - 1].getDestination() << "\t" << newTrips[amount_trips_ - 1].getDate() << std::endl;
	delete[] trips_;
	trips_ = newTrips;
	for (unsigned int i = 0; i < amount_trips_; i++) {
		std::cout << "ID: " << trips_[i].getId() << "\nDestination: " << trips_[i].getDestination() << "\nDate: " << trips_[i].getDate() << std::endl;
	}
}

void Filemanager::removeTrip() {
	std::string input;
	std::cout << "Enter the number of the trip you would like to delete: " << std::endl;
	getline(std::cin, input);
	try {
		Reis *newTrips = new Reis[amount_trips_];
		for (unsigned j = 0; j < amount_trips_; j++) {
			newTrips[j] = trips_[j];
		}
		amount_trips_--;
		unsigned i = std::stoi(input);
		std::cout << "Deleting trip \"" << trips_[i].getDestination() << "\t" << trips_[i].getDate() << "\"" << std::endl;
		for (i; i < amount_trips_; i++) {
			newTrips[i] = newTrips[i + 1];
		}
		delete[] trips_;
		trips_ = newTrips;
		std::cout << "Trip successfully deleted!" << std::endl;
	}
	catch (...) {
		std::cout << "Enter a valid number!" << std::endl;
	}
}

void Filemanager::findTrip() {
	std::string input;
	std::cout << "Find trip by Traveler (T) or find trip by ID (I)" << std::endl;
	std::getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::toupper);
	if (input == "T") {
		std::cout << "Enter the ID of the traveler you want to search the group for" << std::endl;
		std::getline(std::cin, input);
		std::string name;
		unsigned parse = std::stoi(input);
		int traveler = findIndex(parse, 0);
		if (traveler > -1) {
			name = travelers_[traveler].GetName();
			std::string tmp;
			bool found = false;
			for (unsigned i = 0; i < amount_trips_; i++) {
				for (unsigned j = 0; j < trips_[i].getAmount(); j++) {
					tmp = trips_[i].getTravelers()[j].GetName();
					if (tmp.find(name) != std::string::npos) {
						std::cout << trips_[i].getId() << "\t" << trips_[i].getDestination() << "\t" << trips_[i].getDate() << std::endl;
						found = true;
					}
				}
			}
			if (!found) {
				std::cout << "Name not found in any trips" << std::endl;
			}
		}
	}
	else if (input == "I") {
		std::cout << "enter the ID of the trip you would like to find" << std::endl;
		std::getline(std::cin, input);
		unsigned parse = std::stoi(input);
		bool foundid = false;
		for (unsigned i = 0; i < amount_trips_; i++) {
			if (trips_[i].getId() == parse) {
				std::cout << "Trip with ID: " << trips_[i].getId() << " Found." << std::endl;
				std::cout << "Information: \nDestination: " << trips_[i].getDestination() << "\nDate: " << trips_[i].getDate() << std::endl;
				foundid = true;
			}
		}
		if (!foundid) {
			std::cout << "No trip with ID: " << input << " Found" << std::endl;
		}

	}
	else {
		std::cout << "Enter valid input" << std::endl;
	}
}

void Filemanager::readTravelerFile(std::string path)
{
}

void Filemanager::readTripFile(std::string path){
	std::fstream file;
	file.open(path, std::fstream::out);
	unsigned tmpid = 0;
	std::string tmp;
	unsigned amount = 0;
	unsigned line = 0;
	size_t travelers_in_trip = 0;
	bool tripN = false;
	std::string dummyline;
	Reiziger *r = 0;
	if(file.is_open()) {
		getline(file, dummyline);
		std::cout << "Dummyline: " << dummyline << std::endl;
		if(this->amount_trips_ == 3452816845) {
			this->amount_trips_ = std::stoi(dummyline);
			this->trips_ = new Reis[amount_trips_];
		}
		while(1) {
			/*std::getline(file, tmp);
			tmpid = std::stoi(tmp);
			amount++;
			trips_[amount - 1].setId(tmpid);
			*/
			std::getline(file, tmp);
			bool contains_non_alpha = !std::regex_match(tmp, std::regex("^[A-Za-z][A-Za-z0-9]*(?:_?-?/?[A-Za-z0-9]+)*$"));
			if(!contains_non_alpha) {
				if ((amount >= 0 && r != nullptr)) {
					trips_[amount - 1].setTravelers(r);
					line = 0;
				}
				amount++;
				trips_[amount - 1].setDestination(tmp);
				std::getline(file, tmp);
				tmpid = std::stoi(tmp);
				trips_[amount - 1].setId(tmpid);
				std::getline(file, tmp);
				trips_[amount - 1].setDate(tmp);
				std::getline(file, tmp);
				trips_[amount - 1].setTouringCar(tmp);
			}
			else if(tripN) {
				travelers_in_trip = std::stoi(tmp);
				trips_[amount - 1].setAmount(travelers_in_trip);
				r = new Reiziger[travelers_in_trip];
				tripN = false;
			}
			else {
				if (line < travelers_in_trip) {
					if (travelers_[std::stoi(tmp)].GetName() != nullptr) {
						r[line] = travelers_[std::stoi(tmp)];
						line++;
					}
				}
				if((amount >= 0 && r != nullptr) && file.eof()) {
					trips_[amount - 1].setTravelers(r);
					line = 0;
					break;
				}
				else if (file.eof()) {
					break;
				}
			}
		}
		file.close();
		r = nullptr;
	}
	else {
		std::cout << "File \"" << path << "\" not found" << std::endl;
	}
	delete[] r;
}

void Filemanager::writeTripFile(std::string path) {
	std::fstream file;
	file.open(path, std::fstream::out);
	if (file.is_open()) {
		file << amount_trips_ << std::endl;
		for (unsigned i = 0; i < amount_trips_; i++) {
			file << trips_[i].getId() << std::endl;
			file << trips_[i].getDestination() << std::endl;
			file << trips_[i].getDate() << std::endl;
			file << trips_[i].getTouringCar() << std::endl;
			file << trips_[i].getAmount() << std::endl;
			for (unsigned j = 0; trips_[i].getAmount(); j++) {
				if (i == amount_trips_ - 1 && j == (trips_[i].getAmount() - 1)) {
					file << travelers_[(trips_[i].getTravelers()[j].getId() - 1)].getId() - 1;
				}
				else {
					file << travelers_[(trips_[i].getTravelers()[j].getId() - 1)].getId() - 1 << std::endl;
				}
			}
		}
		file.close();
	}
	else {
		std::cout << "File not found" << std::endl;
	}
}

void Filemanager::writeTravelerFile(std::string path) {
	std::fstream file;
	file.open(path, std::fstream::out);
	if (file.is_open()) {
		file.clear();
		file << amount_travelers_ << std::endl;
		for (unsigned i = 0; i < amount_travelers_; i++) {
			file << travelers_[i].GetName() << std::endl;
			if (i < amount_travelers_ - 1) {
				file << "\naddress " << travelers_[i].getAddress();
				file << "ncity " << travelers_[i].getCity();
			}
			else {
				file << "\naddress " << travelers_[i].getAddress();
				file << "\ncity " << travelers_[i].getCity();
			}
		}
		file.close();
	}
	else {
		std::cout << "File not found" << std::endl;
	}
}

void Filemanager::printTrips() {
	std::cout << "Trips: " << std::endl;
	for (unsigned int i = 0; i < amount_trips_; i++) {
		std::cout << "ID: " << trips_[i].getId() << "\nDestination: " << trips_[i].getDestination() << "\nDate: " << trips_[i].getDate() << std::endl;
		std::cout << "Travelers:" << std::endl;
		for (unsigned int j = 0; j < trips_[i].getAmount(); j++) {
			std::cout << trips_[i].getTravelers()[j].GetName() << std::endl;
		}
	}
}

void Filemanager::printTravelers() {
	std::cout << "traveler: " << std::endl;
	for (unsigned int j = 0; j < amount_travelers_; j++) {
		std::cout << travelers_[j].getId() << "\t" << travelers_[j].GetName() << "\t" << travelers_[j].getAddress() << "\t" << travelers_[j].getCity() << std::endl;
	}
}

void Filemanager::print() {
	std::cout << "Trips: " << std::endl;
	for (unsigned int i = 0; i < amount_trips_; i++) {
		std::cout << "ID: " << trips_[i].getId() << "\nDestination: " << trips_[i].getDestination() << "\nDate: " << trips_[i].getDate() << std::endl;
		std::cout << "\nTravelers:" << std::endl;
		for (unsigned int j = 0; j < trips_[i].getAmount(); j++) {
			std::cout << "\n" << trips_[i].getTravelers()[j].GetName() << std::endl;
		}
	}
	std::cout << "-------------------------" << std::endl;
	std::cout << "traveler: " << std::endl;
	for (unsigned int j = 0; j < amount_travelers_; j++) {
		std::cout << travelers_[j].getId() << "\t" << travelers_[j].GetName() << "\t" << travelers_[j].getAddress() << "\t" << travelers_[j].getCity() << std::endl;
	}
}

Filemanager::~Filemanager() {
	writeTravelerFile("travelerfile.txt");
	writeTripFile("tripfile.txt");
	delete[] this->trips_;
	delete[] this->travelers_;
	travelers_ = nullptr;
	trips_ = nullptr;
}
