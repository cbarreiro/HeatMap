#pragma once

#include "stdafx.h"

using namespace std;

class CUart {
   private:
    char uart0_filestream;

    int rxLen,     // Receiving buffer length
        iter = 0;  // Buffer iterator

    char rxBuf[256],   // Receiver buffer
        txBuf[20],     // Transmit buffer
        *pTxBuf,       // Transmit buffer pointer
        digital[256],  // Digital buffer
        data[1];       // Data buffer

    string analog;  // Analog data string

    float fDigi1,  // Digital data to nearest degree
        fDigi2,    // Digital data to nearest 0.0625 of a degree
        digiTemp,  // Digital temperature
        anaProc,   // Analog processed to be stored
        digiProc;  // Digital processed to be stored

    int EXIT_FLAG = false;  // Process exit flag

   public:
    CUart();   // Constructor
    ~CUart();  // Destructor

    vector<pair<float, float>> tempData = vector<pair<float, float>>(
        36);  // Temperature data vector, each node represented by vector
              // element and each element has a pair of values (analog and
              // digital)

    /* @brief Receive from UART
     *
     * @param void
     * @return void
     */
    void uartRx(void);

    /* @brief Transmit to UART
     *
     * @param void
     * @return void
     */
    void uartTx(void);

    /* @brief Terminates current UART instance
     *
     * @param void
     * @return void
     */
    void termUart(void);

    /* @brief Terminates current UART instance
     *
     * @param void
     * @return void
     */
    void termUart(void);

    /* @brief Wipe and dummify temperature buffer
     *
     * @param void
     * @return void
     */

    void resetTempBuf(void);
};
