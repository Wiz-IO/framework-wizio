
#include "HardwareSerial.h"

// https://123a321.wordpress.com/2010/02/01/serial-port-with-mingw/
// https://github.com/waynix/SPinGW

HardwareSerial::HardwareSerial() // for console
{
    name = NULL;
    handle = INVALID_HANDLE_VALUE;
}

HardwareSerial::HardwareSerial(const char *portname) // Serial("\\\\.\\COM1")
{
    name = portname;
    handle = INVALID_HANDLE_VALUE;
}

void HardwareSerial::begin(unsigned long brg)
{
    if (brg == 0 || name == NULL)
        return;
    DWORD direction = GENERIC_READ | GENERIC_WRITE;
    handle = CreateFile(name,
                        direction,
                        0,
                        0,
                        OPEN_EXISTING,
                        0,
                        0);
    if (handle == INVALID_HANDLE_VALUE)
    {
        DBG("[ERROR] Open %s, %d\n", name, GetLastError());
        return;
    }
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(handle, &dcbSerialParams))
    {
        DBG("[ERROR] GetState %s\n", name);
        return;
    }
    dcbSerialParams.BaudRate = brg;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(handle, &dcbSerialParams))
    {
        DBG("[ERROR] SetState UART %s\n", name);
        return;
    }
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(handle, &timeouts))
    {
        DBG("[ERROR] SetTimeouts %s\n", name);
    }
    //DBG("[SERIAL] Open %s\n", name);
}

void HardwareSerial::end()
{
    if (handle == INVALID_HANDLE_VALUE)
        return;
    if (handle)
        CloseHandle(handle);
    handle = INVALID_HANDLE_VALUE;
}

int HardwareSerial::read(void)
{
    if (handle == INVALID_HANDLE_VALUE)
        return 0;
    DWORD n = 0;
    uint8_t b;
    if (!ReadFile(handle, &b, 1, &n, NULL))
    {
        DBG("[ERROR] Read %s\n", name);
        return -1;
    }
    return (n == 1) ? b : -1;
}

size_t HardwareSerial::write(uint8_t b)
{
    if (NULL == name)
    {
        log_printf("%c", b);
#if 0
        // VISIAL FEATURE
        char buf[16];
        sprintf(buf, "%c", b);
        extern void appendLogText(LPCTSTR newText);
        appendLogText(buf);
#endif
        return 1;
    }
    if (handle == INVALID_HANDLE_VALUE)
        return 0;
    return TransmitCommChar(handle, b) ? 1 : 0;
}

int HardwareSerial::available(void)
{
    if (handle == INVALID_HANDLE_VALUE)
        return 0;
    DWORD ERR;
    COMSTAT STAT;
    return ClearCommError(handle, &ERR, &STAT) ? STAT.cbInQue : 0;
}

int HardwareSerial::peek(void)
{
    if (handle == INVALID_HANDLE_VALUE)
        return 0;
    //TODO
    return 0;
}

void HardwareSerial::flush(void)
{
    if (handle == INVALID_HANDLE_VALUE)
        return;
    PurgeComm(handle, PURGE_RXCLEAR | PURGE_TXCLEAR);
}