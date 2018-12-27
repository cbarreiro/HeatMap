#include "../include/stdafx.h"

int main() {
    CUart uart_test;  // Test CUart object

    while (uart_test.EXIT_FLAG == false) {
        uart_test.uartRx();  // Repeatedly receive from RX
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
