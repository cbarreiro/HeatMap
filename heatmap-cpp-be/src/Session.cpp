/*
 * CSession src
 * - Contains Session class functionalities
 */
#include "../include/Session.h"

CSession::CSession() {
    sessDriver = get_driver_instance();  // Retrieve instance of Connection from
                                         // Driver object

    // Get date of session
    time(&sessDate);
    tm* tm;
    char dateArr[10];
    tm = localtime(&sessDate);

    strftime(dateArr, 10, "%d%b%Y", tm);  // Store workable format in dateArr

    dateStr = dateArr;  // String-ify char array

    CUart* sessUart = new CUart;  // Initialize new session UART

    nodeCnt = 8;  // TODO - dynamic node detection (current node count is 8)
}

CSession::~CSession() {
    // Delete all handlers except Driver (handled by SQL connector)
    delete sessConn;
    delete sessStmt;
    delete sessRes;

    EXIT_FLAG = true;
}

void CSession::initSession(void) {
    std::string connChoice = "";

    // Prompt for local connection (so far, only local is implemented)
    while (connChoice != "Y" && connChoice != "N") {
        std::cout << "Would you like to connect locally? (Y/N)";
        std::cin >> connChoice;
    }

    // Make local connection
    if (connChoice == "Y" || connChoice == "y") {
        try {
            // Specify port number
            std::cout << "Specify port for local connection:";
            std::cin >> portNumber;
            server = "tcp://127.0.0.1:" + portNumber;

            // Specify credentials
            std::cout << std::endl << "Enter your username:";
            std::cin >> username;

            std::cout << std::endl << "Enter your password:";
            std::cin >> password;

            // Create connection object
            sessConn = sessDriver->connect(server, username, password);

            // Connect to database
            sessConn->setSchema("heatmap");

        } catch (sql::SQLException& e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MYSQL error code :" << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }

    } else if (connChoice == "N" ||
               connChoice == "n")  // TODO - add some exception handling here
        std::cout << "Goodbye!";
}

int CSession::makeTable(void) {
    // If table for the date is not found, one is created
    if (!(this->checkTable())) {
        string tableMakStmt = "CREATE TABLE IF NOT EXISTS " + dateStr +
                              "(stamp TIME, N1 float, N2 float, N3 float, N4 "
                              "float, N5 float, N6 float, N7 float, N8 float);";
        sql::SQLString tableMakQuery(tableMakStmt);

        sessStmt = sessConn->createStatement();

        // Try/catch block
        try {
            sessRes = sessStmt->executeQuery(tableMakQuery);  // Execute query

            // Delete handlers
            delete sessConn;
            delete sessStmt;
            return 1;

        } catch (sql::SQLException e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MYSQL error code :" << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;

            // Any exception return -1
            delete sessConn;
            delete sessStmt;
            return -1;
        }
    } else
        return 0;
}

int CSession::checkTable(void) {
    // TODO - Not sure if SQLString object can be concatenated, so using hackish
    // workaround for now
    string tableChkStmt = "SHOW TABLES LIKE '" + dateStr + "'";
    sql::SQLString tableChkQuery(tableChkStmt);

    // Prepare statement
    sessStmt = sessConn->createStatement();

    // Try/catch block
    try {
        sessRes = sessStmt->executeQuery(tableChkQuery);  // Execute query

        // Check to see if the table queried is within the result set (and ONLY
        // that table)
        return (sessRes->next()) ? 1 : 0;

        // Delete handlers
        delete sessConn;
        delete sessStmt;
        return exist;

    } catch (sql::SQLException e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MYSQL error code :" << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        // Any exception return -1
        delete sessConn;
        delete sessStmt;
        return -1;
    }
}

// TODO - test this shit out
void CSession::collect(void) {
    // Initialize vector with dummy data
    sessUart->resetTempBuf();

    // First instance of collection requires a true collector flag
    bool collectorFlag = TRUE;

    while (collectorFlag) {
        // Collect some data from UART
        sessUart->uartRx();

        // Clone a flattened vector from tempData and check if all the values
        // are non-dummy, if so end the collection
        vector<float> flatTemp;

        transform(sessUart->tempData.begin(),
                  sessUart->tempData.end(),  // Flatten vector
                  back_inserter(flatTemp),
                  [&flatTemp](const pair<float, float>& p) {
                      flatTemp.push_back(p.first);
                      return p.second;
                  });

        if (std::none_of(flatTemp.begin(),
                         flatTemp.end(),  // Check for non-dummy values
                         [](float i) { return i != -300.0; }))
            collectorFlag = FALSE;
    }
}

// TODO - separate terminate from destructor (?)
void CSession::termSession(void) {}
