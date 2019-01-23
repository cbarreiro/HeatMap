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

    CUart * sessUart = new CUart;  // Initialize new session UART
}

CSession::~CSession() {
    // Delete all handlers except Driver (handled by SQL)
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

    } else if (connChoice == "N" || connChoice == "n")
        std::cout << "Not yet implemented";
}

int CSession::checkTable(void) {
    // TODO - Not sure if SQLString object can be concatenated, so using hackish
    // workaround for now
    int exist = -1;
    
    string tableChkStmt = "SHOW TABLES LIKE '" + dateStr + "'";
    sql::SQLString tableChkQuery(tableChkStmt);    

    // Prepare statement
    sessStmt = sessConn->createStatement();

    // Try to execute query
    try {
        sessRes = sessStmt->executeQuery(tableChkQuery); // Execute query
        
        // Check to see if the table queried is within the result set (and ONLY that table)        
        if (sessRes->next())
            exist = 1;
        else
            exist = 0;
            
        delete sessConn;
        delete sessStmt;
        return exist;
        
    } catch (sql::SQLException e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MYSQL error code :" << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        // Any exception return 0
        delete sessConn;
        delete sessStmt;
    }

    // If no exception...
    
}

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

void CSession::termSession(void) {}
