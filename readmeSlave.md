Arduino.h - the header file for the Arduino language and functions
WiFi101.h - a library for the WiFi module used in the project
SPI.h - a library for SPI communication
Wire.h - a library for I2C communication
string - a standard C++ library for string manipulation
Next, some variables are declared:

ssid - a character array containing the name of the WiFi network to connect to
pass - a character array containing the password for the WiFi network
status - an integer variable used to store the status of the WiFi module
server - a WiFiServer object representing the server that will be created
A receiveEvent() function is defined to handle incoming data over I2C.

In the setup() function, the following tasks are performed:

Serial communication is initiated at a baud rate of 9600
The I2C bus is initialized as a slave with the address 9
The receiveEvent() function is set as the function to be called when data is received over I2C
The WiFi module attempts to connect to the specified network
The IP address of the module is printed to the Serial Monitor
The server is started on port 80
In the loop() function, the following tasks are performed:

If there is incoming data over I2C, the first character of the received string is checked to determine which sensor the data is from. The data is then extracted from the string and stored in the appropriate variable.
The server checks for incoming client connections, and if a connection is established, it waits for data from the client.
Once data is received, the server constructs an HTTP response to send back to the client. The response includes an HTML page with the sensor data displayed in a human-readable format.
The connection to the client is then closed, and the loop repeats.
