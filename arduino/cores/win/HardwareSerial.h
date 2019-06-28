/*
 *  Created on: 01.01.2019
 *      Author: Georgi Angelov
 */

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include "Stream.h"
#include "interface.h"

#define UART_RECEIVE_SIZE (1024)

class HardwareSerial : public Stream
{
protected:
private:
	const char *name;
	void *handle;

public:
	void setName(const char *aname) { name = aname; } // Serial.setName("\\\\.\\COM1") then Serial.begin( ... )
	HardwareSerial();
	HardwareSerial(const char *name);
	~HardwareSerial(){};
	void begin(unsigned long brg = 0);
	void end(void);
	virtual int available(void);
	virtual int peek(void);
	virtual int read(void);
	virtual void flush(void);
	virtual size_t write(uint8_t);
	using Print::write;
	operator bool() { return true; }
};

#endif
