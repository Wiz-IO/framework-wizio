#ifndef ethernetclient_h
#define ethernetclient_h

#include <Arduino.h>
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"

class EthernetClient : public Client
{
private:
	int _sock;
	bool connect_true;

public:
	EthernetClient();
	EthernetClient(uint8_t sock);

	int fd() { return _sock; }
	int connect(IPAddress ip, uint16_t port);
	int connect(const char *host, uint16_t port);
	size_t write(uint8_t);
	size_t write(const uint8_t *buf, size_t size);
	int available();
	int read();
	int read(uint8_t *buf, size_t size);
	int peek();
	void flush();
	void stop();
	uint8_t connected();

	operator bool() { return connected(); }
	EthernetClient &operator=(const EthernetClient &other);
	bool operator==(const bool value) { return bool() == value; }
	bool operator!=(const bool value) { return bool() != value; }
	bool operator==(const EthernetClient &);
	bool operator!=(const EthernetClient &rhs) { return !this->operator==(rhs); };

	//friend class EthernetServer;
	using Print::write;

	int setSocketOption(int option, char *value, size_t len);
	int setOption(int option, int *value);
	int getOption(int option, int *value);
	int setTimeout(uint32_t seconds);
	int setNoDelay(bool nodelay);
	bool getNoDelay();
};

#endif
