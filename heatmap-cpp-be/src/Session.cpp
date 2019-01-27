/*
 * CSession src
 * - Contains Session class functionalities
 */
#include "../include/Session.h"

CSession::CSession() {
    sessSock = new CDBSocket;
    sessCol = new CCollector;
    this->getDate();
    nodeCnt = 8;  // TODO - dynamic node detection (current node count is 8)
}

CSession::~CSession() {}

void CSession::initSession(void) {
    std::string connChoice = "";

    // Prompt for local connection (so far, only local is implemented)
    while (connChoice != "Y" && connChoice != "N") {
        std::cout << "Would you like to connect locally? (Y/N)";
        std::cin >> connChoice;
    }

    // Make local connection
    if (connChoice == "Y" || connChoice == "y") {
        // Specify port number
        std::cout << "Specify port for local connection:";
        std::cin >> portNumber;
        server = "tcp://127.0.0.1:" + portNumber;

        // Specify credentials
        std::cout << "Enter your username:";
        std::cin >> username;

        std::cout << "Enter your password:";
        std::cin >> password;

        sessSock->initDBConn(server, username, password, dateStr);

    } else if (connChoice == "N" ||
               connChoice == "n")  // TODO - add some exception handling here
        std::cout << "Goodbye!";
}

void CSession::getDate(void) {
    // Get date of session
    time(&sessDate);
    tm* tm;
    char dateArr[10];
    tm = localtime(&sessDate);

    strftime(dateArr, 10, "%d%b%Y", tm);  // Store workable format in dateArr

    dateStr = dateArr;  // String-ify char array
}

// TODO - separate terminate from destructor (?)
void CSession::termSession(void) {}
