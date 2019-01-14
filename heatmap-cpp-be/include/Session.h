#pragma once

#include "stdafx.h"

#include "mysql_connection.h"

#define FAIL 0
#define PASS 1

using namespace std;

class CSession {
   private:
    time_t sessStart;
    time_t sessEnd;

    time_t sessDate;  // Session date

    string dateStr;  // Session date in string form

    // SQL access pointers
    sql::Driver *sessDriver;
    sql::Connection *sessConn;
    sql::Statement *sessStmt;
    sql::ResultSet *sessRes;

    string server, username, password;

    string portNumber;

   public:
    int check = PASS;  // Session init status

    bool EXIT_FLAG;  // The flag used to close main

    CUart *sessUart;  // Session UART connection

    /** @brief Constructor
     *
     * @param void
     * @return void
     */
    CSession();

    /** @brief Destructor
     *
     * NOTE: Make sure to clean up all SQL handlers EXCEPT Driver after
     * completing a session. Refer to:
     * https://dev.mysql.com/doc/connector-cpp/1.1/en/connector-cpp-examples-connecting.html
     *
     * @param void
     * @return void
     */
    ~CSession();

    /** @brief Get/load session start or end
     *
     * @param time
     * @return void
     */
    void loadTime(time_t now);

    /** @brief Initializes database connection
     *
     * @param void
     * @return void
     */
    void initSession(void);

    /** @brief Terminates database connection
     *
     * @param void
     * @return void
     */
    void termSession(void);

    /** @brief Collect data into buffer
     *
     * @param void
     * @return void
     */
    void collect(void);

    /** @brief Make table if not existent
     *
     * @param void
     * @return int flag to indicate successful SQL operation
     */
    int makeTable(void);

    /** @brief Checks if a table exists for the current day
     *
     * @param void
     * @return int flag to indicate successful SQL operation
     */
    int checkTable(void);
};
