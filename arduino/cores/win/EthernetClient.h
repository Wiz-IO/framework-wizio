#ifndef ethernetclient_h
#define ethernetclient_h

#include <Arduino.h>
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"

class EthernetClient : public Client
{

#define CLIENT_MAX_INACTIVITY_RETRIES 100000

public:
	EthernetClient();
	EthernetClient(uint8_t sock);

	uint8_t status();
	virtual int connect(IPAddress ip, uint16_t port);
	virtual int connect(const char *host, uint16_t port);
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *buf, size_t size);
	virtual int available();
	virtual int read();
	virtual int read(uint8_t *buf, size_t size);
	virtual int peek();
	virtual void flush();
	virtual void stop();
	virtual uint8_t connected();
	virtual operator bool();
	
	using Print::write;

	friend class EthernetServer;
	class EthernetServer *_pCloseServer;

	int _sock;
	bool connect_true;
	int id;
};

#endif
