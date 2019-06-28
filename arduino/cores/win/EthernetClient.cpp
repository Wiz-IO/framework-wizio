#include "EthernetClient.h"

#define DBG_CLIENT //Serial.printf

EthernetClient::EthernetClient() : _sock(-1)
{
	connect_true = false;
	_pCloseServer = NULL;
}

EthernetClient::EthernetClient(uint8_t sock) : _sock(sock)
{
	connect_true = true;
	_pCloseServer = NULL;
}

static int _connect(int sock, struct sockaddr_in *psin, unsigned int len, uint32_t timeout)
{
	extern int errno;
	int ret;
	DBG_CLIENT("[TCP] Connecting: %d.%d.%d.%d : %d\n",
			   (int)((psin->sin_addr.s_addr) & 0xFF),
			   (int)((psin->sin_addr.s_addr >> 8) & 0xFF),
			   (int)((psin->sin_addr.s_addr >> 16) & 0xFF),
			   (int)((psin->sin_addr.s_addr >> 24) & 0xFF),
			   (int)(int)ntohs(psin->sin_port));
	ret = connect(sock, (struct sockaddr *)psin, len);
	if (ret < 0)
	{
		DBG_CLIENT("[ERROR] TCP connect %d errno = %d\n", ret, WSAGetLastError());
		close(sock);
		return ret;
	}
	int enable = 1;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&enable, sizeof(enable));
	setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char *)&enable, sizeof(enable));
	DBG_CLIENT("[TCP] Connected\n");
	return ret;
}

int EthernetClient::connect(const char *host, uint16_t port)
{
	struct hostent *hp;
	int ret = 0;
	extern int errno;
	DBG_CLIENT("[TCP] Connecting: %s : %d\n", host, (int)port);
	if (host == NULL || _sock != -1)
	{
		DBG_CLIENT("[ERROR] TCP socket!\n");
		return 0;
	}
	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sock < 0)
	{
		DBG_CLIENT("[ERROR] TCP unable to open a TCP socket\n");
		return 0;
	}
	hp = gethostbyname(host);
	if (hp == NULL)
	{
		DBG_CLIENT("[ERROR] TCP gethostbyname %s fail\n", host);
		return 0;
	}
	struct sockaddr_in _sin;
	memcpy(&_sin.sin_addr, hp->h_addr, sizeof(_sin.sin_addr));
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	ret = _connect(_sock, &_sin, sizeof(_sin), 20000);
	if (ret < 0)
	{
		DBG_CLIENT("[ERROR] TCP unable to connect to target host %s\n", host);
		return 0;
	}
	if (ret == 0)
		connect_true = true;
	return 1;
}

int EthernetClient::connect(IPAddress ip, uint16_t port)
{
	// Look up the host first
	int ret = 0;
	extern int errno;
	if (_sock != -1)
		return 0;
	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sock < 0)
	{
		DBG_CLIENT("[ERROR] TCP unable to open a TCP socket\n");
		return 0;
	}
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = (uint32_t)ip;
	sin.sin_port = htons(port);
	ret = _connect(_sock, &sin, sizeof(sin), 20000);
	if (ret < 0)
	{
		DBG_CLIENT("[ERROR] TCP unable to connect to target ip\n");
		return 0;
	}
	if (ret == 0)
		connect_true = true;
	return 1;
}

size_t EthernetClient::write(uint8_t b)
{
	return write(&b, 1);
}

size_t EthernetClient::write(const uint8_t *buf, size_t size)
{
	if (_sock < 0)
		return 0;
	if (send(_sock, (char *)buf, size, 0) < 0)
	{
		DBG_CLIENT("[ERROR] TCP write()\n");
		stop();
		size = 0;
	}
	return size;
}

int EthernetClient::available()
{
	if (_sock < 0)
		return 0;
	u_long count;
	int rc = ioctlsocket(_sock, FIONREAD, &count);
	if (rc < 0)
	{
		DBG_CLIENT("[ERROR] TCP available()\n");
		return 0;
	}
	//DBG_CLIENT("[TCP] %d ", count);
	return count;
}

int EthernetClient::read()
{
	char b = 0;
	int rc = recv(_sock, &b, 1, 0);
	//if (WSAGetLastError()) return -1;
	if (rc > 0)
		return b;
	return -1; // No data available
}

int EthernetClient::read(uint8_t *buf, size_t size)
{
	int rc = recv(_sock, (char *)buf, size, 0);
	//if (WSAGetLastError()) return -1;
	if (rc > 0)
		return rc;
	return -1;
}

int EthernetClient::peek()
{
	if (_sock < 0 || !available())
		return -1;
	char b;
	int rc = recv(_sock, &b, 1, MSG_PEEK);
	if (rc > 0)
		return b;
	return -1;
}

void EthernetClient::flush()
{
	if (_sock < 0)
		return;
	while (available())
		read();
}

void EthernetClient::stop()
{
	if (_sock < 0)
		return;
	connect_true = false;
	close(_sock);
	_sock = -1;
	if (_pCloseServer != NULL)
	{
		//TODO
		//_pCloseServer->closeNotify(this->id);
	}
}

uint8_t EthernetClient::connected()
{
	return connect_true == true;
}

uint8_t EthernetClient::status()
{
	return _sock == -1;
}

EthernetClient::operator bool()
{
	return _sock != -1;
}
