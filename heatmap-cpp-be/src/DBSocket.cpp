#include "../include/DBSocket.h"

CDBSocket::CDBSocket() {
    this->dbDriver = get_driver_instance();  // Retrieve instance of Connection
                                             // from Driver object
    std::cout << "Connection driver version " << dbDriver->getMajorVersion()
              << "." << dbDriver->getMinorVersion() << endl;
}

CDBSocket::~CDBSocket() {
    // Delete all handlers except Driver (handled by SQL connector)
    delete dbConn;
    delete dbStmt;
    delete dbRes;
}

void CDBSocket::initDBConn(std::string serv, std::string uname,
                           std::string pass, std::string date) {
    std::cout << "Trying to establish connection to " << serv << " ..." << endl;

    try {
        // Create connection object
        dbConn = dbDriver->connect(serv, uname, pass);
        std::cout << "Connection established, selecting database..." << endl;

        // Connect to database
        dbConn->setSchema("heatmap");
        std::cout << "Database selected!" << endl;

    } catch (sql::SQLException& e) {
        ExpHandle("initDBConn", e);
    }

    std::cout << "Connection established!" << endl;

    if (this->makeTable(date)) {
        std::cout << "Table for " << date << " successfully created!" << endl;
    }
}

int CDBSocket::makeTable(std::string currstd::string) {
    // If table for the date is not found, one is created
    if (!(this->checkTable(currstd::string))) {
        std::string tableMakStmt =
            "CREATE TABLE IF NOT EXISTS " + currstd::string +
            "(stamp TIME, N1 float, N2 float, N3 float, N4 "
            "float, N5 float, N6 float, N7 float, N8 float);";
        sql::SQLstd::string tableMakQuery(tableMakStmt);

        dbStmt = dbConn->createStatement();

        // Try/catch block
        try {
            dbRes = dbStmt->executeQuery(tableMakQuery);  // Execute query

            // Delete handlers
            delete dbConn;
            delete dbStmt;
            return 1;  // New table created

        } catch (sql::SQLException e) {
            ExpHandle("makeTable", e);

            // Any exception return -1
            return -1;  // Exception
        }
    } else
        return 0;  // Table already exists
}

int CDBSocket::checkTable(std::string datestd::string) {
    // TODO - Not sure if SQLstd::string object can be concatenated, so using
    // hackish workaround for now
    std::string tableChkStmt = "SHOW TABLES LIKE '" + datestd::string + "'";
    sql::SQLstd::string tableChkQuery(tableChkStmt);

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
        ExpHandle("checkTable", e);

        // Any exception return -1
        return -1;
    }
}
