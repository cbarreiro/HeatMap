#include "../include/stdafx.h"

int main() {
    CUart uart_test;  // Test CUart object
    int count = 0;

    while (true) {
        uart_test.uartRx();  // Repeatedly receive from RX
        // count++;    // Uptick counter
    }

    uart_test.~CUart();  // Terminate

    /* Below kept as testing space for mysql
        // Instantiate session object 'test'
        CSession test;

        // Initialize 'test'
        test.initSession();

        while (1) {
        };

        // Destructor
        test.~CSession();
        */
}
