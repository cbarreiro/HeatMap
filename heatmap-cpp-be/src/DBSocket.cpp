#include "../include/DBSocket.h"

CDBSocket::CDBSocket() {
    this->dbDriver = get_driver_instance();  // Retrieve instance of Connection from
                                       // Driver object
    cout << "Connection driver version " << dbDriver->getMajorVersion() << "." << dbDriver->getMinorVersion() << endl;    
}

CDBSocket::~CDBSocket() {
    // Delete all handlers except Driver (handled by SQL connector)
    delete dbConn;
    delete dbStmt;
    delete dbRes;
}

void CDBSocket::initDBConn(string serv, string uname, string pass,
                           string date) {
    cout << "Trying to establish connection to " << serv << " ..." << endl;
    
    try {
        // Create connection object        
        dbConn = dbDriver->connect(serv, uname, pass);
        cout << "Connection established, selecting table..." << endl;              
        
        // Connect to database
        dbConn->setSchema("heatmap");
        cout << "Table selected!" << endl;
        
    } catch (sql::SQLException& e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MYSQL error code :" << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    
    cout << "Connection established!" << endl;

    if (this->makeTable(date)) {
        cout << "Table for " << date << " successfully created!" << endl;
    }
}

int CDBSocket::makeTable(string currString) {
    // If table for the date is not found, one is created
    if (!(this->checkTable(currString))) {
        string tableMakStmt = "CREATE TABLE IF NOT EXISTS " + currString +
                              "(stamp TIME, N1 float, N2 float, N3 float, N4 "
                              "float, N5 float, N6 float, N7 float, N8 float);";
        sql::SQLString tableMakQuery(tableMakStmt);

        dbStmt = dbConn->createStatement();

        // Try/catch block
        try {
            dbRes = dbStmt->executeQuery(tableMakQuery);  // Execute query

            // Delete handlers
            delete dbConn;
            delete dbStmt;
            return 1;  // New table created

        } catch (sql::SQLException e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MYSQL error code :" << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;

            // Any exception return -1
            delete dbConn;
            delete dbStmt;
            return -1;  // Exception
        }
    } else
        return 0;  // Table already exists
}

int CDBSocket::checkTable(string dateString) {
    // TODO - Not sure if SQLString object can be concatenated, so using hackish
    // workaround for now
    string tableChkStmt = "SHOW TABLES LIKE '" + dateString + "'";
    sql::SQLString tableChkQuery(tableChkStmt);

    // Prepare statement
    dbStmt = dbConn->createStatement();

    // Try/catch block
    try {
        dbRes = dbStmt->executeQuery(tableChkQuery);  // Execute query

        // Check to see if the table queried is within the result set (and ONLY
        // that table)
        return (dbRes->next()) ? 1 : 0;

        // Delete handlers
        delete dbConn;
        delete dbStmt;

    } catch (sql::SQLException e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MYSQL error code :" << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        // Any exception return -1
        delete dbConn;
        delete dbStmt;
        return -1;
    }
}
