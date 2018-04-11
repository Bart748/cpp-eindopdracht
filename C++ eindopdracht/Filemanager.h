#pragma once
#include "Reis.h"
#include "Reiziger.h"

class Filemanager
// READ, WRITE FILE.
// Read file, add info to vector
// edit info.......
// before exiting write changes in de file.
// Files: Trip.exe (Trip ID, Destination, date and travelers)
// Travelers: ID, name, address, livingPlace
{
public:
	Filemanager(std::string, std::string); //
	Filemanager(const Filemanager &other); //
	Filemanager(Filemanager &&other); //
	Filemanager& operator=(const Filemanager&); //
	Filemanager& operator=(Filemanager&&); // 

	virtual int findIndex(int, int); // 
	virtual void findName(std::string); //
	virtual void findAddress(std::string); //
	virtual void findCity(std::string); // 

	virtual void printTraveler(unsigned int); //
	virtual void findTraveler(); // 
	virtual void addTraveler(); //
	virtual void removeTraveler(); //
	virtual void modifyTraveler(); //

	virtual void addTrip();//
	virtual bool validName(std::string);
	virtual void editTrip(); //
	virtual void removeTrip(); //
	virtual void findTrip(); //

	virtual void readTravelerFile(std::string);
	virtual void readTripFile(std::string); //
	virtual void writeTravelerFile(std::string); //
	virtual void writeTripFile(std::string); //

	virtual void printTrips(); //
	virtual void printTravelers(); //
	virtual void print(); //

	~Filemanager(); //

private:
	size_t amount_travelers_;
	size_t amount_trips_;

	Reis *trips_;
	Reiziger *travelers_;
};

