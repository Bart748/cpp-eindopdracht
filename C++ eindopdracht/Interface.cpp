#include "Interface.h"
#include <iostream>
#include <string>
#include <algorithm>

void Interface::printInterface() {
	std::cout << ("________________________________\n") << std::endl;
	std::cout << ("What would you like to do:      \n") << std::endl;
	std::cout << ("(A) to add a traveler           \n") << std::endl;
	std::cout << ("(M) to modify traveler          \n") << std::endl;
	std::cout << ("(R) to remove a traveler        \n") << std::endl;
	std::cout << ("(F) to find traveler            \n") << std::endl;
	std::cout << ("(P) to print all travelers      \n") << std::endl;
	std::cout << ("(T) to add new Trip             \n") << std::endl;
	std::cout << ("(E) to edit Trip                \n") << std::endl;
	std::cout << ("(Z) to remove Trip              \n") << std::endl;
	std::cout << ("(H) to find Trip                \n") << std::endl;
	std::cout << ("(1) print all Trips             \n") << std::endl;
	std::cout << ("(U) print everything            \n") << std::endl;
	std::cout << ("(X) to save & exit              \n") << std::endl;
	std::cout << ("________________________________\n") << std::endl;
	std::cout << std::endl;
}

int Interface::readInput() {
	printInterface();
	std::string str;
	std::getline(std::cin, str);
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	switch (str[0]) {
	case 'X': return 1; break;
	case 'H':return 2; break;
	case 'Z':return 3; break;
	case 'T':return 4; break;
	case 'F':return 5; break;
	case 'E':return 6; break;
	case 'U':return 7; break;
	case 'P':return 8; break;
	case '1':return 9; break;
	case 'R':return 10; break;
	case 'M':return 11; break;
	case 'A':return 12; break;
	default: return -1; break;
	}
}


