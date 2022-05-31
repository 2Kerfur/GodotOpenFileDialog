int GetAvaliablePorts(int rows, int cols,
                     char avaliable_devices_var[rows][cols]);

int OpenComPort(char device_name[]);

int CloseComPort(int serial_port);

char* ReadComPort(int serial_port);

int WriteComPort(int serial_port, char message[]);
