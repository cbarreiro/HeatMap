#pragma once

#include "stdafx.h"

#include "mysql_connection.h"

#define FAIL 0
#define PASS 1
#define TRUE 1
#define FALSE 0

// Forward declare to avoid cross referencing issues
class CDBSocket;
class CCollector;

using namespace std;

class CSession {
   private:
    time_t sessDate;  // Session date   

   public:
    string server, username, password, portNumber;  // Access credentials
    string dateStr;  // Session date in string form

    int check = PASS;  // Session init status

    bool EXIT_FLAG;  // The flag used to close main

    int nodeCnt;  // Number of active nodes expected in the session

    CDBSocket *sessSock;
    CCollector *sessCol;

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

    /** @brief Get session date
     *
     * @param void
     * @return void
     */
    void getDate(void);
};
