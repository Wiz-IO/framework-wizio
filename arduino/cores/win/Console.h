/*
    Created on: 01.01.2019
    Author: Georgi Angelov
 */

#ifndef Console_h
#define Console_h

#include <inttypes.h>
#include "Stream.h"
#include <interface.h>

class Console : public Stream
{
protected:
public:
    Console(uint32_t id) {}
    void begin(unsigned long baud) {}
    void end() {}
    virtual int available(void) {}
    virtual int peek(void) {}
    virtual int read(void) {}
    virtual void flush(void) {}
    virtual size_t write(uint8_t c) { log_printf("%c", c);  return 1;}
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    //size_t write(const char *buf) { log_printf(buf); }
    //size_t write(const uint8_t *buf, size_t size) { log_printf("%.*s", size, buf); }
    using Print::write;
    operator bool() { return true; }
};

#endif
