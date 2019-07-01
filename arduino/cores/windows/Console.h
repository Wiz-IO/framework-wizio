/*
    Created on: 01.01.2019
    Author: Georgi Angelov
        http://www.wizio.eu/
        https://github.com/Wiz-IO    

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
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
