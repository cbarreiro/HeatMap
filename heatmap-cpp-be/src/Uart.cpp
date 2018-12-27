#include "../include/Uart.h"

CUart::CUart() {
    // Terminate if GPIO incorrectly initiated
    gpioTerminate();
    
    // Initialize GPIO and filestream
    gpioInitialise();
    uart0_filestream = -1;

    // Open channel at uart0
    if (uart0_filestream = serOpen("/dev/ttyUSB0", 9600, 0) < 0)
        printf("Unable to open UART\n");
}

CUart::~CUart() {
    // Close channel at uart0
    serClose(uart0_filestream);

    // Terminate GPIO and set exit flag
    gpioTerminate();
    EXIT_FLAG = true;
}

void CUart::uartRx(void) {
    // If channel is open
    if (uart0_filestream != -1) {
        // Temporary data vector identifier
        int id = -1;

        // Read '1' bytes from 'uart0_filestream' to 'data'
        rx_length = serRead(uart0_filestream, data, 1);

        // Either bad rx_length (-1) or empty (0)
        if (rx_length <= 0) printf("Error reading form UART: %d\n", rx_length);

        // If data in buffer is not yet valid
        else if (data[0] != '.') {
            // Load 'data' into next element in 'rx_buffer'
            rx_buffer[iter] = data[0];
            iter++;  // Increment iterator
        }

        // If data in buffer is valid
        else if (data[0] = '.') {
            if (rx_buffer[0] = 'N') {
                // 2nd element of rx_buffer contains the node number
                // This converts that node number from char to int
                id = rx_buffer[1] - '0';

                // Analog conversion
                analog = string(rx_buffer).substr(4, 5);
                stringstream stream;
                stream << analog;

                // Digital conversion
                char* pEnd;
                copy(rx_buffer + 12, rx_buffer + 16,
                     digital + 0);  // Copy digital data into 'digital' string
                f_digital_1 = strtol(digital, &pEnd,
                                     16);  // digital data to nearest degree
                                           // from string to long int
                f_digital_2 = strtol(pEnd, &pEnd,
                                     16);  // digital data to nearest 0.0625 of
                                           // a degree from string to long int

                // Consolidate digital temperature
                digi_temp = f_digital_1 + f_digital_2 * 0.0625;

                // Reference temp_data's 'id'th element, and loads analog
                // into first of the pair, and digital into second of the pair
                stream >> temp_data[id].first;
                temp_data[id].second = digi_temp;

                // Reset rx_buffer
                memset(rx_buffer, 0, sizeof(rx_buffer));
            }
        }

        // Otherwise, unhandled error
        else {
            printf("Unhandled error.\n");
        }
    }
}
