#ifndef ethernet_h
#define ethernet_h

#include <interface.h>

class Ethernet
{
public:
    Ethernet()
    {
        begin();
    }

    int begin()
    {
        WSADATA wsaData;
        int rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
        //if (rc != 0) printf("[ERROR] WSAStartup failed with error: %d\n", rc);
        return rc;
    }

    int end() { WSACleanup(); }
};

#endif