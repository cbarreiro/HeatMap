#pragma once

#include "stdafx.h"

using namespace std;

class CUart {
   private:
    char uart0_filestream;

    int rx_length,  // Receiving buffer length
        iter = 0;       // Buffer iterator

    char rx_buffer[256],  // Receiver buffer
        tx_buffer[20],    // Transmit buffer
        *p_tx_buffer,     // Transmit buffer pointer
        digital[256],     // Digital buffer
        data[1];          // Data buffer

    string analog;  // Analog data string

    float f_digital_1,  // Digital data to nearest degree
        f_digital_2,    // Digital data to nearest 0.0625 of a degree
        digi_temp,      // Digital temperature
        ana_proc,       // Analog processed to be stored
        digi_proc;      // Digital processed to be stored

    int EXIT_FLAG = false;  // Process exit flag

   public:
    CUart();   // Constructor
    ~CUart();  // Destructor

    vector<pair<float, float>>
        temp_data = vector<pair<float, float>>(36);  // Temperature data vector, each node represented by vector
                    // element and each element has a pair of values (analog and
                    // digital)

    /*
     * Receive from UART
     * @param void
     * @return void
     */
    void uartRx(void);

    /*
     * Transmit to UART
     * @param void
     * @return void
     */
    void uartTx(void);

    /*
     * Terminates current UART instance
     * @param void
     * @return void
     */
    void termUart(void);
};
