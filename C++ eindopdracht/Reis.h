#pragma once
#include "Reiziger.h"

class Reis //trip
{
public:
	// constructors
	Reis();
	Reis(const Reis& other);
	Reis(Reis&& other);
	~Reis();

	Reis& operator = (const Reis& other);
	Reis& operator = (Reis&& other);

	//getters and setters
	
	
	virtual int deleteTraveler(int id);
	virtual int findTraveler(int id);
	virtual void addTraveler(Reiziger);
	virtual void modifyTravelerName(std::string, int);
	virtual void modifyTravelerAddress(std::string, int);
	virtual void modifyTravelerCity(std::string, int);

	virtual void createArray(size_t size);
	virtual void resizeArray(size_t size);

	virtual unsigned int& getId();
	virtual void setId(unsigned int id);
	virtual char* getTouringCar();
	virtual void setTouringCar(std::string);
	virtual char* getDestination();
	virtual void setDestination(std::string);
	virtual char* getDate();
	virtual void setDate(std::string);

	virtual Reiziger *getTravelers();
	virtual void setTravelers(Reiziger *traveler); // add travelers to travel

	virtual unsigned int getAmount();
	virtual void setAmount(unsigned int amount);

private:
	unsigned int id_; 
	char *touringCar_; 
	char *destination_;
	char *date_;

	Reiziger *travelers_; // dynamic array of travelers
	unsigned int amount_;
};

