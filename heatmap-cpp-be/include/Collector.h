#pragma once

#include "stdafx.h"

class CUart;  // Forward declare to avoid cross referencing issues

using namespace std;

class CCollector {
   private:
    bool colExitFlag = 0;  // Exit flag

   public:
    CUart *colUart;  // Collector UART connection object

    float colBuf[8];  // Collector buffer to receive valid temp data from UART

    CCollector();   // Constructor
    ~CCollector();  // Destructor

    /** @brief Collect data into local buffer
     *
     * @param void
     * @return void
     */
    void collect(void);
};