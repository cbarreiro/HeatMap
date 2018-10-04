#include "Session.h"

CSession::CSession() {	
	
}

CSession::~CSession() {
	EXIT_FLAG = true;
}

void CSession::initSession(void) {	
	std::string connChoice = 0;
	while (connChoice != "Y" || connChoice != "N") {
		std::cout << "Would you like to connect locally? (Y/N)";
		std::cin >> connChoice;
	}

	if (connChoice == "Y") {
		std::cout << "Specify port for local connection:";
		std::cin >> portNumber;
		server = "tcp://127.0.0.1:" + portNumber;

		std::cout << std::endl << "Enter your username:";
		std::cin >> username;

		std::cout << std::endl << "Enter your password:";
		std::cin >> password;
	}
	else if (connChoice == "N") {
		std::cout << "Not yet implemented";
	}
}

void CSession::termSession(void) {

}
