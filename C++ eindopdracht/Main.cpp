// C++ eindopdracht.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Reis.h"
#include "Reiziger.h"
#include "Interface.h"
#include "FileManager.h"
#include <iostream>

void checkForLeaks();

void checkForLeaks() {
#ifdef _DEBUG;

	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	flag |= _CRTDBG_LEAK_CHECK_DF;

	_CrtSetDbgFlag(flag);

#endif
}

int main(int argc, char *argv[]) {
	Filemanager *fm = new Filemanager(argv[1], argv[2]);
	Interface *in = new Interface();
	int input = in->readInput();
	//checkForLeaks();
	void(Filemanager::*functionPointers[])() = { 0, &Filemanager::findTrip, &Filemanager::removeTrip, 
		&Filemanager::addTrip, &Filemanager::findTraveler, &Filemanager::editTrip, &Filemanager::print, 
		&Filemanager::printTravelers, &Filemanager::printTrips, &Filemanager::removeTraveler, 
		&Filemanager::modifyTraveler, &Filemanager::addTraveler };
	while(input != 1) {
		if (input == -1) {
			std::cout << "Not a valid input, Exiting program" << std::endl;
			return 0;
		}
		(*fm.*functionPointers[input - 1])();
		input = in->readInput();
	}
	delete fm;
	delete in;
	std::cin.get();
	return 0;

}

