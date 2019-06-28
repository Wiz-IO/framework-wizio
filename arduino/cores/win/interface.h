#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif

//#include <_ansi.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include <windows.h>
#include <winsock.h>

    void printDateTime();
    uint32_t utc();
    
    unsigned int seconds(void);
    unsigned int millis(void);
    unsigned int micros(void);
    void delay(unsigned int);

    int isascii(int c);
    int toascii(int c);
    long atol(const char *s);
    char *itoa(int value, char *result, int base);
    char *ltoa(long value, char *result, int base);
    char *utoa(unsigned value, char *result, int base);
    char *ultoa(unsigned long value, char *result, int base);

    uint32_t clockCyclesPerMicrosecond(void);
    uint32_t clockCyclesToMicroseconds(uint32_t a);
    uint32_t microsecondsToClockCycles(uint32_t a);

#ifndef SERIAL_BUFFER_SIZE
#define SERIAL_BUFFER_SIZE 1024
#endif

    int log_printf(const char *frm, ...);
    void log_buf(const char *text, const unsigned char *buf, unsigned int len);
#define DBG(FORMAT, ...) log_printf(FORMAT, ##__VA_ARGS__)
#define DMP(TEXT, BUFFER, LEN) log_buf(TEXT, (unsigned char *)BUFFER, LEN)



//extern HWND hwnd;
//extern HWND hEdit;


#ifdef __cplusplus
} // extern "C"
#endif //__cplusplus

#endif /* INTERFACE_H_ */