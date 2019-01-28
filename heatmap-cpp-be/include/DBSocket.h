#pragma once

#include "stdafx.h"

#include "mysql_connection.h"

class CDBSocket {
   private:
    // SQL access pointers
    sql::Driver *dbDriver;
    sql::Connection *dbConn;
    sql::Statement *dbStmt;
    sql::ResultSet *dbRes;

   public:
    int test;
    CDBSocket();   // Constructor
    ~CDBSocket();  // Destructor

    /** @brief Initailizes database connection
     *
     * @param std::string server    server IP and port
     * @param std::string username  username
     * @param std::string password  password
     * @param std::string date      date of session
     * @return void
     */
    void initDBConn(std::string serv, std::string uname, std::string pass,
                    std::string date);

    /** @brief Make table if not existent
     *
     * @param std::string formatted std::string of current date (e.g. 21Jan2019)
     * @return int flag to indicate successful SQL operation
     */
    int makeTable(std::string currstd::string);

    /** @brief Checks if a table exists for the current day
     *
     * @param std::string formatted std::string of current date (e.g. 21Jan2019)
     * @return int flag to indicate successful SQL operation
     */
    int checkTable(std::string datestd::string);
};
