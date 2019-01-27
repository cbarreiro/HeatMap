#pragma once

#include "stdafx.h"

class CDBSocket {
   private:
    // SQL access pointers
    sql::Driver *dbDriver;
    sql::Connection *dbConn;
    sql::Statement *dbStmt;
    sql::ResultSet *dbRes;

   public:
    CDBSocket();   // Constructor
    ~CDBSocket();  // Destructor

    /** @brief Initailizes database connection
     *
     * @param string server
     * @param string username
     * @param string password
     * @return void
     */
    void initDBConn(string serv, string uname, string pass, string date);

    /** @brief Make table if not existent
     *
     * @param string formatted string of current date (e.g. 21Jan2019)
     * @return int flag to indicate successful SQL operation
     */
    int makeTable(string currString);

    /** @brief Checks if a table exists for the current day
     *
     * @param string formatted string of current date (e.g. 21Jan2019)
     * @return int flag to indicate successful SQL operation
     */
    int checkTable(string dateString);
}