#pragma once
#include <cstddef>
#include <string.h>
#include <algorithm>
#include <string>

class Reiziger {
public:
	Reiziger();
	virtual ~Reiziger();

	Reiziger(const Reiziger&  other);
	Reiziger(Reiziger&& other);

	Reiziger& operator = (const Reiziger& other);
	Reiziger& operator = (Reiziger&& other);


	virtual unsigned int& getId();
	virtual void SetId(unsigned int id);
	virtual char* GetName();
	virtual void SetName(std::string name);
	virtual char* getAddress();
	virtual void SetAddress(std::string address);
	virtual char* getCity();
	virtual void SetCity(std::string city);

private:
	unsigned int id_;
	char *name_;
	char *address_;
	char *city_;
};

