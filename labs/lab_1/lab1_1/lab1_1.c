#include <windows.h>
#include <iostream>

HANDLE COM1;
LPCTSTR Port_name_1 = L"COM1";
HANDLE COM2;
LPCTSTR Port_name_2 = L"COM2";

void read_COM2()
{
    DWORD size;
    char received_char;
    ReadFile(COM2, &received_char, 1, &size, 0);
    if (size > 0)
    {
        printf_s("Recieved char - %c", received_char);
    }
}

void close_ports() {
    CloseHandle(COM1);
    CloseHandle(COM2);
}

int main()
{
    char data = '!';
    COM1 = ::CreateFile(Port_name_1, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    COM2 = ::CreateFile(Port_name_2, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (COM1 == INVALID_HANDLE_VALUE || COM2 == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            printf_s("COM-port does not exist!\n");
        }
        else {
            printf_s("Some other error.\n");
        }
        return 0;
    }

    DWORD size = sizeof(data);
    DWORD bytes_written;

    WriteFile(COM1, &data, size, &bytes_written, NULL);

    printf_s("Tryed to send - %d bytes, sended - %d bytes\n", size, bytes_written);

    read_COM2();
    close_ports();
    return 0;
}

