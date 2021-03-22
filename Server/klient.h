#ifndef KLIENT_H
#define KLIENT_H

#include <netdb.h>
#include <iostream>
#include <string>

class Klient
    {
    private:
        int m_id;
        sockaddr_in m_address;
    public:
        Klient(sockaddr_in address, int id);
        void printInfo();
        int getId();
    };

#endif // KLIENT_H
