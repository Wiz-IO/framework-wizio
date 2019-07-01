/*
 *  Created on: 01.01.2019
 *      Author: Georgi Angelov
 */

#include "HardwareSerial.h"


HardwareSerial::HardwareSerial() // for console
{
    name = NULL;
    handle = NULL;
}

HardwareSerial::HardwareSerial(const char *portname) // Serial("\\\\.\\COM1")
{
    name = portname;
    handle = NULL;
}

void HardwareSerial::begin(unsigned long brg)
{
    if (brg == 0 || name == NULL)
        return;
}

void HardwareSerial::end()
{
    if (handle == NULL)
        return;
    handle = NULL;
}

int HardwareSerial::read(void)
{
    if (handle == NULL)
        return 0;
    return -1;
}

size_t HardwareSerial::write(uint8_t b)
{
    if (NULL == name)
    {
        ::printf("%c", b);
        return 1;
    }
    if (handle == NULL)
        return 0;
    return 0;
}

int HardwareSerial::available(void)
{
    if (handle == NULL)
        return 0;
    return 0;
}

int HardwareSerial::peek(void)
{
    if (handle == NULL)
        return 0;
    //TODO
    return 0;
}

void HardwareSerial::flush(void)
{
    if (handle == NULL)
        return;
}