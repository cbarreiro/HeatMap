/*
 * UART.cpp
 * 
 * Author: Chris Barreiro Stewart
 * 
 */


#include "UART.h"

	//-------------------------
	//----- SETUP USART 0 -----
	//-------------------------
	//At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD respectively
	
UART::UART()
{
	// Initialize Pigpio
	gpioInitialise();
	uart0_filestream = -1;

	// Open UART at desired BAUD rate
	if(uart0_filestream = serOpen("/dev/ttyS0",9600,0) < 0)
	{
		printf("Unable to open UART ");
	}
}

UART::~UART()
{
	//----- CLOSE THE UART -----
	serClose(uart0_filestream);
	gpioTerminate();
}

void UART::RX()
{
	//----- CHECK FOR ANY RX BYTES -----
	if (uart0_filestream != -1)
	{
		
		// Read up to 255 characters from the port if they are there
		rx_length = serRead(uart0_filestream, data, 1);		//Filestream, buffer to store in, number of bytes to read (max)
		
		if (rx_length < 0)
		{
			//An error occured (will occur if there are no bytes)
			printf("UART ERROR");
		}
		else if (rx_length == 0)
		{
			//No data waiting
			//printf("Waiting for DATA ");
			//gpioDelay(1000*10);
		}
		else if (data[0] != 'w' )
		{
			rx_buffer[i] = data[0] ;
			i++;
			
		}
		
				else if (data[0] == 'w' )
		{
			//Bytes received
			//printf("%i bytes read : %s", i, rx_buffer);
			
			// DATA string = Sx Axxxxx D xx x
			
			if (rx_buffer[0] == 'S')
			{
				//cout << "RAW: " << rx_buffer << endl;
				char * pEnd;
				float fdigital1, fdigital2, temperature;
				float x;
				
				slave = string(rx_buffer).substr(0,2);
				analog = string(rx_buffer).substr(4,5);
				
				copy(rx_buffer + 12, rx_buffer + 16, digital + 0);
				fdigital1 = strtol(digital, &pEnd, 16);
				fdigital2 = strtol(pEnd, &pEnd, 16);				
				
				stringstream stream;
				stream << analog;

				stream >> x;

				
				//cout << "digital crap: " << fdigital1 << " "<< fdigital2 << endl;

				x = ((x/10000) - 1.8641)/(-11.71/1000);  // first order
				
				cout << slave << ": " << endl;
				cout << "Analog: " << x << endl;
				
				
				temperature = fdigital1 + fdigital2 * 0.0625;
				//SlaveData.push_back(temperature);
				cout << "Digital: "  << temperature << endl;
				

				memset(rx_buffer, 0, sizeof(rx_buffer));
			}
			
			
			else
			{
				cout << "UART DATA: " << rx_buffer << endl;
			}
			
			i = 0 ;
			
		}
			
	}
}

	
  


void UART::TX()
{
	p_tx_buffer = &tx_buffer[0];
	*p_tx_buffer++ = 'H';
	*p_tx_buffer++ = 'e';
	*p_tx_buffer++ = 'l';
	*p_tx_buffer++ = 'l';
	*p_tx_buffer++ = 'o';
	
	if (uart0_filestream != -1)
	{
		count = serWrite(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));		//Filestream, bytes to write, number of bytes to write
		if (count < 0)
		{
			printf("UART TX error\n");
		}
	}
}

